
/* 包含头文件 */
#include <rthw.h>
#include <rtthread.h>
#include "board.h"

/* ROM内存空间 */
#define ROM_START              ((uint32_t)0x08000000)
#define ROM_SIZE               (128 * 1024)
#define ROM_END                ((uint32_t)(ROM_START + ROM_SIZE))
/* ROM内存空间 */
#define RAM_START              (0x20000000)
#define RAM_SIZE               (20 * 1024)
#define RAM_END                (RAM_START + RAM_SIZE)
/* 堆内存空间 */
#if defined(__CC_ARM) || defined(__CLANG_ARM)
extern int Image$$RW_IRAM1$$ZI$$Limit;
#define HEAP_BEGIN      		((void *)&Image$$RW_IRAM1$$ZI$$Limit)
#elif __ICCARM__
#pragma section="CSTACK"
#define HEAP_BEGIN      		(__segment_end("CSTACK"))
#else
extern int __bss_end;
#define HEAP_BEGIN      		((void *)&__bss_end)
#endif

#define HEAP_END                RAM_END

/* 开发板硬件初始化 */
void rt_hw_board_init(void)
{
	/* 中断优先级设置 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/* SysTick初始化 */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
	
	/* 板载驱动初始化 */

    /* 板载组件初始化<INIT_BOARD_EXPORT()> */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
   
	/* 堆内存初始化 */
#if defined(RT_USING_HEAP)
    rt_system_heap_init((void*)HEAP_BEGIN, (void*)HEAP_END);
#endif
}

/* 微秒延时函数 */
void rt_hw_udelay(rt_uint32_t us)
{
  rt_uint32_t start, now, delta, reload, us_tick;
  start = SysTick->VAL;
  reload = SysTick->LOAD;
  us_tick = SystemCoreClock / 1000000UL;//比如系统时钟频率是80M 那么1us 需要80个周期
  do {
    now = SysTick->VAL;
    delta = start > now ? start - now : reload + start - now;//是倒数 还是正数
  } while(delta < us_tick * us);
}

/* 中断服务函数 */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}
