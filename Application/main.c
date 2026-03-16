
#include <rtthread.h>
#include "rf_thread.h"
#include "at_thread.h"
#include "sensor_thread.h"
#include "sensor.h"
#include "led.h"

static void sys_param_init(void);

int main(void) {
	sys_param_init();     //ϵͳ������ʼ��
	led_Init();           //LED��ʼ��
	sensor_thread_init(); //�������ɼ������߳�
	rf_thread_init();     //ͨѶ�߳�
	at_thread_init();     //ATָ����߳�
}

static void sys_param_init(void) {
	//��ʼ������ģ�����
	rf_info_init();
}
                                    