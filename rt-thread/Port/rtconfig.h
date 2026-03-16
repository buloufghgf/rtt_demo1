#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* RT-Thread内核相关配置 */
#define RT_NAME_MAX 				16		// 内核对象名称最大长度
#define RT_ALIGN_SIZE 				4		// 内存对齐字节数
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 		32		// 线程优先级梳
#define RT_TICK_PER_SECOND 			1000	// 系统时钟节拍tick/s
#define RT_USING_OVERFLOW_CHECK				// 开启栈溢出检查
#define RT_USING_HOOK						// 开启钩子函数
#define RT_USING_IDLE_HOOK					// 开启空闲线程钩子函数
#define RT_IDLE_HOOK_LIST_SIZE 		4		// 空闲线程钩子函数数量
#define IDLE_THREAD_STACK_SIZE 		256		// 空闲线程栈大小
#define RT_DEBUG							// 开启调试
#define RT_DEBUG_COLOR					    // 开启调试调色

/* RT-Thread通讯相关配置 */
#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* RT-Thread内存相关配置 */
#define RT_USING_MEMPOOL
#define RT_USING_MEMHEAP
#define RT_USING_SMALL_MEM
#define RT_USING_HEAP

/* RT-Thread设备相关配置 */
#define RT_USING_DEVICE
// #define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE 			128
#define RT_CONSOLE_DEVICE_NAME 		"uart3"
#define RT_VER_NUM 					0x40000
#define ARCH_ARM
#define ARCH_ARM_CORTEX_M
#define ARCH_ARM_CORTEX_M3

/* RT-Thread组件相关配置 */
#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 	1024
#define RT_MAIN_THREAD_PRIORITY 	10

/* RT-Thread FinSH相关配置 */
#if defined(RT_USING_FINSH)
#define FINSH_THREAD_NAME 			"tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 		5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY 		20
#define FINSH_THREAD_STACK_SIZE 	4096
#define FINSH_CMD_SIZE 				80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 				10
#endif

/* RT-Thread设备驱动相关配置 */
#define RT_USING_DEVICE_IPC
#define RT_PIPE_BUFSZ 				512
#define RT_USING_SERIAL
#define RT_SERIAL_USING_DMA
#define RT_USING_PIN

#endif
