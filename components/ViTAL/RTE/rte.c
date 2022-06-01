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

#include "RTE/rte.h"
#include "stdint.h"
#include <stdbool.h>
#include "BSW/HAL/Buzzer/buzzer.h"
#include "BSW/HAL/Com/com.h"
#include "BSW/HAL/DC_Motor/dc_motor.h"
#include "BSW/HAL/Proximity_Sensor/proximity_sensor.h"
#include "BSW/HAL/Servo_Motor/servo_motor.h"
#include "BSW/HAL/Shift_Register/shift_register.h"
#include "BSW/MCAL/PWM/pwm.h"

static const char *TAG = "RTE";

extern COM_GET_struct g_GET_DataStructure;
extern COM_POST_struct g_POST_DataStructure;
uint8_t u8Data = 0;

void RTE_vSetShiftRegisterOutput(rgb_state_mask_t u8CompMask, _Bool bLevel)
{

    if (bLevel == true)
    {
        u8Data = (u8Data | u8CompMask);
    }
    else
    {
        u8Data = (u8Data & (~u8CompMask));
    }
    SHIFTREG_vOutput8Bits(u8Data);
}

_Bool RTE_bGetTrunkRequest()
{
    return g_POST_DataStructure.bButtonTrunk;
}

void RTE_vSetTrunkState(uint32_t u32State)
{
    SERVO_vChangeAngle(u32State);
}

_Bool RTE_bGetHeadLightsRequest()
{
    return g_POST_DataStructure.bButtonHeadlights;
}

void RTE_vSetHeadLightsState(_Bool bState)
{
    if(bState == true)
        RTE_vSetShiftRegisterOutput(LED_GREEN2,HIGH);
    else
        RTE_vSetShiftRegisterOutput(LED_GREEN2,LOW);

}

uint16_t RTE_u16GetLightLevel()
{
    return g_GET_DataStructure.u16PhotoRes;
}

void RTE_vSetHornStatus(bool status)
{
    if (status == true)
        BUZZER_vChangeDutyCycle(BUZZER_ON);
    else
        BUZZER_vChangeDutyCycle(BUZZER_OFF);
}

void RTE_vSetLightState(_Bool bState)
{
    static rgb_state_t rgbColour = RED1;
    if (bState == true)
    {
        switch (rgbColour)
        {
        case RED1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, LOW);
            RTE_vSetShiftRegisterOutput(RED, HIGH);
            rgbColour = RED_GREEN1;
            break;

        case RED_GREEN1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, LOW);
            RTE_vSetShiftRegisterOutput(RED_GREEN, HIGH);
            rgbColour = GREEN1;
            break;

        case GREEN1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, LOW);
            RTE_vSetShiftRegisterOutput(GREEN, HIGH);
            rgbColour = GREEN_BLUE1;
            break;

        case GREEN_BLUE1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, LOW);
            RTE_vSetShiftRegisterOutput(GREEN_BLUE, HIGH);
            rgbColour = BLUE1;
            break;

        case BLUE1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, LOW);
            RTE_vSetShiftRegisterOutput(BLUE, HIGH);
            rgbColour = BLUE_RED1;
            break;

        case BLUE_RED1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, LOW);
            RTE_vSetShiftRegisterOutput(BLUE_RED, HIGH);
            rgbColour = ALL1;
            break;

        case ALL1:
            RTE_vSetShiftRegisterOutput(ALL_COLOURS, HIGH);
            rgbColour = RED1;
            break;
        }
    }
}

_Bool RTE_bGetAllButton()
{
    return g_POST_DataStructure.bButtonAmbientalLights;
}

void RTE_vSetComfort(uint8_t u8Value)
{
    g_GET_DataStructure.u8Comfort = u8Value;
}

void RTE_vSetLock(_Bool state)
{
    g_GET_DataStructure.bIsLocked = state;
}
_Bool RTE_bGetLock()
{
    return g_GET_DataStructure.bIsLocked;
}