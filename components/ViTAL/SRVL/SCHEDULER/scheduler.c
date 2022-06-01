/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 *******************************************************************************/

#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "SRVL/SCHEDULER/scheduler.h"
#include"RTE/rte.h"
#include "BSW/MCAL/ADC/adc.h"
#include "BSW/MCAL/GPIO/gpio.h"
#include "BSW/MCAL/PWM/pwm.h"
#include "BSW/MCAL/WIFI/wifi.h"
#include "BSW/HAL/Servo_Motor/servo_motor.h"
 #include "BSW/HAL/Com/com.h" 
#include "BSW/HAL/Buzzer/buzzer.h"
#include "nvs_flash.h"
#include"BSW/HAL/Shift_Register/shift_register.h"
#include "BSW/HAL/Photo_Resistor/photo_resistor.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/HAL/Temp_Sensor/temp_sensor.h"
#include "ASW/Trunk/trunk.h"
#include "ASW/Ambient_Light/ambient_light.h"
#include "ASW/Horn/horn.h"
#include "ASW/Headlights/headlights.h"
#include "ASW/Locking_System/locking_system.h"
static const char *TAG = "SRVL SCHEDULER";

static httpd_handle_t server = NULL;
extern COM_GET_struct g_GET_DataStructure;
extern COM_POST_struct g_POST_DataStructure;
int counter = 0;
void SYSTEM_vInit(void)
{
    /* Call these functions only when specific HW parts are connected */
    /*
	Initialize NVS
	*/
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	ADC_vInit();

	//GPIO_vInit();

	PWM_vInit();
	
	WIFI_vInit(&server);
    
   GPIO_vInit();
}

void vTask500ms(void)
{
	/*static bool flag=false;
	if(flag==false)
	{
		SERVO_vChangeAngle(ANGLE_90);
		flag=true;
	}
	else
	{
		SERVO_vChangeAngle(ANGLE_ZERO);
	}*/
	 //COM_vTaskProcessServer(); 
	 //PWM_vSetDutyCycle(SERVO_MOTOR_PWM_CHANNEL,1500);
	 //BUZZER_vChangeDutyCycle(BUZZER_ON);
	if(g_POST_DataStructure.bButtonFan)
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, 45000);
	}
	else
	{
		PWM_vSetDutyCycle(DC_MOTOR_PWM_CHANNEL, 0);
	}
	if(counter<=16)
	{
		ASW_vHorn();
		ASW_vControlAmbientLights();
		counter++;
	}
	else
	{
		BUZZER_vChangeDutyCycle(BUZZER_OFF);
		g_POST_DataStructure.bButtonFindMyCar = false;
		counter = 0;
	}

	ASW_vControlHeadlights();
	ASW_vLockingSys();
	// ASW_vControlTrunk();

}

void vTask100ms(void)
{
	 COM_vTaskProcessServer(); 

}

void vTask200ms(void)
{
	//  if(PROX_u16Read()<50)
	//  {
	// 	 BUZZER_vChangeDutyCycle(BUZZER_ON);
	//  }
	//  else
	//  {
	// 	 BUZZER_vChangeDutyCycle(BUZZER_OFF);
	//  }


}
void vTask2000ms(void)
{
	//  uint16_t u16PhotoValue;
	//  u16PhotoValue=Photo_u16Read();
	 /*if(u16PhotoValue<200)
	 {
		 DCMOTOR_vSetMotorSpeed(1500);
	 }
	 else
	 {
		 DCMOTOR_vSetMotorSpeed(45000);
	 }*/
}
void vTask1000ms(void)
{
	/* COM_vTaskProcessServer(); */
	//DCMOTOR_vSetMotorSpeed(DC_MOTOR_LOW_SPEED);
	// SHIFTREG_vOutput8Bits(0B10101010);
	// RTE_vSetShiftRegisterOutput(LED_GREEN,HIGH);
	// ets_delay_us(5000);
	// RTE_vShiftRegisterOutput(RGB_RED,LOW);
	ASW_vControlTrunk();
}

void vTask5000ms(void)
{
	DHT11_vTaskTempAndHumCalculate();
}

void vTask800ms(void)
{
	 //COM_vTaskProcessServer(); 
	 if(RTE_bGetLock() == false)
	 	ASW_vControlAmbientLights();
}
void SYSTEM_vTaskScheduler(void)
{
	uint16_t u16TickCount = 0;

	
	while (1)
	{
		if (u16TickCount % TASK_100MS == 0)
		{
			vTask100ms();
		}

		if (u16TickCount % TASK_200MS == 0)
		{
			vTask200ms();
			ESP_LOGI(TAG, "TICK: %d", u16TickCount);
		}

		if (u16TickCount % TASK_500MS == 0)
		{
			vTask500ms();

		}

		if (u16TickCount % TASK_800MS == 0)
		{
			vTask800ms();

		}

		if (u16TickCount % TASK_1000MS == 0)
		{
			vTask1000ms();
			
		}
		if (u16TickCount % TASK_2000MS == 0)
		{
			vTask2000ms();
			
		}
		u16TickCount++;
		if (u16TickCount % TASK_5000MS==0)
		{
			vTask5000ms();
			u16TickCount = 0;
		}
		vTaskDelay(100);
	}
}
