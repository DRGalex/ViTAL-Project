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

#include <stdbool.h>
#include "ASW/Locking_System/locking_system.h"

#include "RTE/rte.h"
#include "BSW/HAL/Com/com.h"
extern COM_POST_struct g_POST_DataStructure;

static const char *TAG = "ASW LOCK";

void ASW_vLockingSys()
{
    if(g_POST_DataStructure.bButtonDoorLock)  // Locked Red / Unlocked Green3
    {
        RTE_vSetShiftRegisterOutput(LED_GREEN3, HIGH);
        RTE_vSetShiftRegisterOutput(LED_GREEN, LOW);
        RTE_vSetLock(true);
    }
    else
    {
        RTE_vSetShiftRegisterOutput(LED_GREEN3, LOW);
        RTE_vSetShiftRegisterOutput(LED_GREEN, HIGH);
        RTE_vSetLock(false);
    }
}