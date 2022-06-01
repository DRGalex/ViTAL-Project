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

#ifndef COMPONENTS_VITAL_RTE_H
#define COMPONENTS_VITAL_RTE_H

#include "global.h"
#define LOW 0
#define HIGH 1

typedef enum
{
    LED_GREEN = 1 << 1,
    LED_GREEN2 = 1 << 2,
    LED_GREEN3 = 1 << 3,
    RGB_RED = 1 << 4,
    RGB_GREEN = 1 << 5,
    RGB_BLUE = 1 << 6,
    LED_RED = 1 << 7,
} shift_register_output_t;

typedef enum
{
    RED = RGB_RED,
    GREEN = RGB_GREEN,
    BLUE = RGB_BLUE,
    RED_GREEN = RGB_RED | RGB_GREEN,
    GREEN_BLUE = RGB_GREEN | RGB_BLUE,
    BLUE_RED = RGB_BLUE | RGB_RED,
    ALL_COLOURS = RGB_RED | RGB_GREEN | RGB_BLUE,
} rgb_state_mask_t;

typedef enum
{
    RED1 = 0,
    GREEN1,
    BLUE1,
    RED_GREEN1,
    GREEN_BLUE1,
    BLUE_RED1,
    ALL1
} rgb_state_t;

void RTE_vSetLightState(_Bool state);
_Bool RTE_bGetAllButton();
_Bool RTE_bGetTrunkRequest();
uint16_t RTE_u16GetLightLevel();
void RTE_vSetHeadLightsState(_Bool bState);
void RTE_vSetTrunkState(uint32_t u32State);
void RTE_vSetShiftRegisterOutput(rgb_state_mask_t u8CompMask, _Bool bLevel);
void RTE_vSetHornStatus(_Bool status);
_Bool RTE_bGetHeadLightsRequest();
void RTE_vSetComfort(uint8_t u8Value);
void RTE_vSetLock(_Bool state);
_Bool RTE_bGetLock();

#endif