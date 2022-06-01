/*******************************************************************************
 * COPYRIGHT (C) VITESCO TECHNOLOGIES
 * ALL RIGHTS RESERVED.
 *
 * The reproduction, transmission or use of this document or its
 * contents is not permitted without express written authority.
 * Offenders will be liable for damages. All rights, including rights
 * created by patent grant or registration of a utility model or design,
 * are reserved.
 ******************************************************************************/
#include "stdint.h"
#include <stdbool.h>
#include "ASW/Climate_Control_System/climate_control_system.h"
#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "RTE/rte.h"
#include "BSW/HAL/Com/com.h"
static const char *TAG = "ASW CCS";
extern COM_GET_struct g_GET_DataStructure;

void vCalculateTemp()
{
    float HI;
    uint8_t T,R;
    T = g_GET_DataStructure.u8Temperature;
    R = g_GET_DataStructure.u8Humidity;
    const float c1 = -8.78469475556;
    const float c2 = 1.61139411;
    const float c3 = 2.33854883889;
    const float c4 = -0.14611605;
    const float c5 = -0.012308094;
    const float c6 = -0.0164248277778;
    const float c7 = 0.002211732;
    const float c8 = 0.00072546;
    const float c9 = -0.000003582;
    HI = c1 + c2*T + c3*R + c4*T*R + c5*T*T + c6*R*R + c7*T*T*R + c8*T*R*R + c9*T*T*R*R;

    RTE_vSetComfort(HI);
}

void ASW_vClimateControl()
{
    uint8_t T;
    T = g_GET_DataStructure.u8Temperature;
    _Bool flag = false;
    if(T > 30)
    {
        flag = true;
        DCMOT_vChangeSpeed(DC_MOTOR_FULL_SPEED);
    }
    else if(T < 28)
    {
        flag = false;
        DCMOT_vChangeSpeed(DC_MOTOR_STOP);
    }
    else if(T > 28 && T < 30 && flag == false)
    {
        DCMOT_vChangeSpeed(DC_MOTOR_STOP);
    }
    else if(T > 28 && T < 30 && flag ==true)
    {
        flag = true;
        DCMOT_vChangeSpeed(DC_MOTOR_LOW_SPEED);
    }

    if(T > 30)
    {
        flag = true;
        DCMOT_vChangeSpeed(DC_MOTOR_FULL_SPEED);
    }
    else if(T > 28 && flag == true)
    {
        DCMOT_vChangeSpeed(DC_MOTOR_FULL_SPEED);
    }
    else
    {
        DCMOT_vChangeSpeed(DC_MOTOR_STOP);
        flag = false;
    }
}