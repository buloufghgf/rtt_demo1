
/*********************************************************************************************
 * Í·ï¿½Ä¼ï¿½
 *********************************************************************************************/
#include <rtthread.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "math.h"
#include "rf_thread.h"
#include "sensor_thread.h"
#include "sensor.h"

/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Í·ï¿½Ä¼ï¿½ï¿½ï¿½ToDo */
#include "key.h"
#include "dht11.h"
#include "water_sensor.h"
/*********************************************************************************************
 * ï¿½ï¿½ï¿½Í¶ï¿½ï¿½ï¿½
 *********************************************************************************************/
typedef struct{
	/* A0 - A7 */
	float   	A0;
	float   	A1;
	uint8_t 	A2;
	uint8_t 	A3;
	uint8_t 	A4;
	uint8_t 	A5;
	uint8_t 	A6;
	uint8_t 	A7;
	/* D0 - D1 */
	uint8_t		D0;
	uint8_t		D1;
	/* V0 - V7 */
	uint8_t		V0;
	uint8_t		V1;
	uint8_t		V2;
	uint8_t		V3;
	uint8_t		V4;
	uint8_t		V5;
	uint8_t		V6;
	uint8_t		V7;
} SensorData_t;

/*********************************************************************************************
 * ï¿½ê¶¨ï¿½ï¿½
 *********************************************************************************************/

/*********************************************************************************************
 * È«ï¿½Ö±ï¿½ï¿½ï¿½
 *********************************************************************************************/
static SensorData_t g_sensorData ={
	/* A0 - A7 */
	0.0F, 0.0F, 0, 0, 0, 0, 0, 0,
	/* D0 - D1 */
	0xFF, 0,
	/* V0 - V7 */
	30, 0, 0, 0, 0, 0, 0, 0,
};

static struct rt_semaphore sensor_poll_sem;
static struct rt_timer sensor_poll_timer;

static void sensor_poll_timer_cb(void *parameter) {
	/* ï¿½Í·ï¿½ï¿½Åºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý¸ï¿½ï¿½ï¿½ */
	rt_sem_release(&sensor_poll_sem);
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½V0ï¿½ï¿½Öµ
 * @param	v0: V0È¡Öµ
 * @retval	None
 */
static void UpdateV0(uint8_t v0)
{
	/* ï¿½ï¿½ï¿½ï¿½V0Öµ */
	g_sensorData.V0 = v0;
	
	/* ï¿½ï¿½ï¿½Ã¶ï¿½Ê±ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ */
	uint32_t tick = g_sensorData.V0 * 1000;
	rt_timer_control(&sensor_poll_timer, RT_TIMER_CTRL_SET_TIME, (void*)&tick);
	/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ */
	rt_timer_start(&sensor_poll_timer);
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A0ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA0(void)
{
	g_sensorData.A0 = dht11_read_temp();
	if (g_sensorData.A0 < -50.0f) g_sensorData.A0 = 0.0f;  // 通信失败时设为0
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A1ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA1(void)
{
	g_sensorData.A1 = dht11_read_humidity();
	if (g_sensorData.A1 < -50.0f) g_sensorData.A1 = 0.0f;  // 通信失败时设为0
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A2ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA2(void)
{
	g_sensorData.A2 = water_sensor_get_data();
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A3ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA3(void)
{
	g_sensorData.A3 = rand() % 100;
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A4ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA4(void)
{
	g_sensorData.A4 = rand() % 100;
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A4ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA5(void)
{
	g_sensorData.A5 = rand() % 100;
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A6ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA6(void)
{
	if(get_key_status() == 0x01){
		g_sensorData.A6 = 1;
	}
	else{
		g_sensorData.A6 = 0;
	}
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½A7ï¿½ï¿½Öµ
 * @param	None
 * @retval	None
 */
static void UpdateA7(void)
{
	if(get_key_status() == 0x02){
		g_sensorData.A7 = 1;
	}
	else{
		g_sensorData.A7 = 0;
	}
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿½
 * @param	None
 * @param	None
 */
void SensorInit(void){
	/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½ï¿½ï¿½Ê±ï¿½Ï±ï¿½ï¿½ï¿½ï¿½Ý£ï¿½Ê±ï¿½ï¿½ï¿½ï¿½ÎªV0 */
	rt_timer_init(&sensor_poll_timer,
				  "sensor poll tim",
                  sensor_poll_timer_cb,
				  RT_NULL,
				  g_sensorData.V0 * 1000,
				  RT_TIMER_FLAG_PERIODIC);
	
	/* ¶¨ÒåÐÅºÅÁ¿£¬´¥·¢´«¸ÐÆ÷Êý¾ÝÉÏ±¨ */
	rt_sem_init(&sensor_poll_sem, "sensor poll sem", 0, RT_IPC_FLAG_FIFO);

	/* Æô¶¯¶¨Ê±Æ÷ */
	rt_timer_start(&sensor_poll_timer);
	/* Æô¶¯°²·ÅÀàÏß³Ì */
	rt_thread_startup(&sensor_check_thread);

	/* ÏîÄ¿´«¸ÐÆ÷Çý¶¯³õÊ¼»¯£ºToDo */
	key_init();
	water_sensor_init();
	dht11_init();
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É¹ï¿½ï¿½Øµï¿½
 * @param	None
 * @param	None
 */
void SensorLinkOn(void)
{
	/* ï¿½Í·ï¿½ï¿½Åºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý¸ï¿½ï¿½ï¿½ */
	rt_sem_release(&sensor_poll_sem);
}

/**
 * @brief	ï¿½É¼ï¿½ï¿½à´«ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ï±ï¿½
 * @param	None
 * @param	None
 */
void SensorUpdate(void)
{
	/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý»ï¿½ï¿½ï¿½ */
	char sendData[128] = "{";
	char temp[16];
  
	/* ï¿½ï¿½ï¿½ï¿½ï¿½Åºï¿½ï¿½ï¿½ */
	rt_err_t err = rt_sem_take(&sensor_poll_sem, 1000);
	if(err != RT_EOK){
		return;
	}
  
	/* ï¿½ï¿½ï¿½ï¿½D0ï¿½ï¿½Î»×´Ì¬ï¿½Ð¶ï¿½ï¿½ï¿½Òªï¿½ï¿½ï¿½ï¿½ï¿½Ï±ï¿½ï¿½ï¿½ï¿½ï¿½Öµ */
	if((g_sensorData.D0 & 0x01) == 0x01){
		UpdateA0();
		sprintf(temp, "A0=%.2f,", g_sensorData.A0);
		strcat(sendData, temp);
	}
  
	if((g_sensorData.D0 & 0x02) == 0x02){
		UpdateA1();
		sprintf(temp, "A1=%.2f,", g_sensorData.A1);
		strcat(sendData, temp);
	}
	
	if((g_sensorData.D0 & 0x04) == 0x04){
		UpdateA2();
		sprintf(temp, "A2=%d,", g_sensorData.A2);
		strcat(sendData, temp);
	}
	
	if((g_sensorData.D0 & 0x08) == 0x08){
		UpdateA3();
		sprintf(temp, "A3=%d,", g_sensorData.A3);
		strcat(sendData, temp);
	}
	
	if((g_sensorData.D0 & 0x10) == 0x10){
		UpdateA4();
		sprintf(temp, "A4=%d,", g_sensorData.A4);
		strcat(sendData, temp);
	}
	
	if((g_sensorData.D0 & 0x20) == 0x20){
		UpdateA5();
		sprintf(temp, "A5=%d,", g_sensorData.A5);
		strcat(sendData, temp);
	}
	
	if((g_sensorData.D0 & 0x40) == 0x40){
		UpdateA6();
		sprintf(temp, "A6=%d,", g_sensorData.A6);
		strcat(sendData, temp);
	}
	
	if((g_sensorData.D0 & 0x80) == 0x80){
		UpdateA7();
		sprintf(temp, "A7=%d,", g_sensorData.A7);
		strcat(sendData, temp);
	}

	/* ï¿½Ï±ï¿½D1ï¿½ï¿½ï¿½ï¿½ */
	sprintf(temp, "D1=%d,", g_sensorData.D1);
	strcat(sendData, temp);
  
	/* ï¿½ï¿½ï¿½Ý·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ½Ì¨ */
	if(strlen(sendData) > 2) {
		sendData[strlen(sendData)-1] = '}';
		rf_send((uint8_t *)sendData, strlen(sendData), 200);
	}
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½ï¿½à´«ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý¼ï¿½ï¿½
 * @param	None
 * @param	None
 */
void SensorCheck(void)
{
	/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý»ï¿½ï¿½ï¿½ */
	char sendData[128] = "{";
	char temp[16];
 
	/* ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â°ï¿½ï¿½ï¿½×´Ì¬ */
	UpdateA6();
	UpdateA7();
	
	/* ï¿½ï¿½ï¿½Ý°ï¿½ï¿½ï¿½×´Ì¬ï¿½Ð¶ï¿½ï¿½Ï±ï¿½ï¿½ï¿½Öµ */
	if(g_sensorData.A6 > 0){
		sprintf(temp, "A6=%d,", g_sensorData.A6);
		strcat(sendData, temp);
	}
	if(g_sensorData.A7 > 0){
		sprintf(temp, "A7=%d,", g_sensorData.A7);
		strcat(sendData, temp);
	}
 
	/* ï¿½ï¿½ï¿½Ý·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Æ½Ì¨ */
	if(strlen(sendData) > 2) {
		sendData[strlen(sendData)-1] = '}';
		rf_send((uint8_t *)sendData, strlen(sendData), 200);
	}
}

/**
 * @brief	ï¿½ï¿½ï¿½ï¿½ï¿½à´«ï¿½ï¿½ï¿½ï¿½Ö¸ï¿½ï¿½ï¿½ï¿½ï¿½
 * @param	cmd: ï¿½ï¿½ï¿½ï¿½Öµ
 * @param	None
 */
void SensorControl(uint8_t cmd)
{
	/* 风扇控制功能已移除 */
	/* 可根据需要添加其他控制逻辑 */
}

/**
 * @brief	Ó¦ï¿½Ã²ï¿½Ö¸ï¿½î´¦ï¿½ï¿½
 * @param	ptag: ï¿½Èºï¿½ï¿½ï¿½ß¼ï¿½ï¿½ï¿½pval: ï¿½Èºï¿½ï¿½Ò±ï¿½Öµï¿½ï¿½obuf: Ö¸ï¿½î´¦ï¿½ï¿½ï¿½ï¿½ï¿½
 * @param	>0Ö¸ï¿½î´¦ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý³ï¿½ï¿½È£ï¿½0ï¿½ï¿½Ã»ï¿½Ð·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý£ï¿½<0ï¿½ï¿½ï¿½ï¿½Ö§ï¿½ï¿½Ö¸ï¿½ï¿½
 */
int z_process_command_call(char* ptag, char* pval, char* obuf)
{
	int val;
	int ret = 0;	
	char *p = obuf;
  
	/* ï¿½ï¿½ï¿½Ö·ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½pvalï¿½ï¿½ï¿½ï¿½×ªï¿½ï¿½Îªï¿½ï¿½ï¿½Í±ï¿½ï¿½ï¿½ï¿½ï¿½Öµ */
	val = atoi(pval);
	
	/* {A0=?} */
	if (0 == strcmp("A0", ptag)){
		if (0 == strcmp("?", pval)){
			UpdateA0();
			ret = sprintf(p, "%.2f", g_sensorData.A0);     
		}
	}
	
	/* {A1=?} */
	if (0 == strcmp("A1", ptag)){
		if (0 == strcmp("?", pval)){
			UpdateA1();
			ret = sprintf(p, "%.2f", g_sensorData.A1);
		}
    }
	
	/* {A2=?} */
	if (0 == strcmp("A2", ptag)){
		if (0 == strcmp("?", pval)){
			UpdateA2();
			ret = sprintf(p, "%d", g_sensorData.A2);
		}
    }
	
	/* {D0=?} */
	if (0 == strcmp("D0", ptag)){
		if (0 == strcmp("?", pval)){
			ret = sprintf(p, "%d", g_sensorData.D0);
		} 
	}
	
	/* {D1=?} */
	if (0 == strcmp("D1", ptag)){
		if (0 == strcmp("?", pval)){
			ret = sprintf(p, "%d", g_sensorData.D1);
		} 
	}
	
	/* {V0=?} {V0=XXX} */
	if (0 == strcmp("V0", ptag)){
		if (0 == strcmp("?", pval)){
			ret = sprintf(p, "%d", g_sensorData.V0);
		}
		else{
			UpdateV0(val);
		}
	}
	
	/* {OD1=XXX} */
	if (0 == strcmp("OD0", ptag)){
		g_sensorData.D0 |= val;
	}
	
	/* {CD1=XXX} */
	if (0 == strcmp("CD0", ptag)){
		g_sensorData.D0 &= ~val;
	}
	
	/* {OD1=XXX} */
	if (0 == strcmp("OD1", ptag)){
		g_sensorData.D1 |= val;
		SensorControl(g_sensorData.D1);
	}
	
	/* {CD1=XXX} */
	//if (0 == strcmp("CD1", ptag)){
	//	g_sensorData.D1 &= ~val;
	//	SensorControl(g_sensorData.D1);
	/* 风扇控制命令已移除 */

	return ret;
}
