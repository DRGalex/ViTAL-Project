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

#include "stdint.h"
#include <stdbool.h>
#include "ASW/Horn/horn.h"

#include "RTE/rte.h"
#include "BSW/HAL/Com/com.h"
extern COM_POST_struct g_POST_DataStructure;
static const char *TAG = "ASW HORN";
void ASW_vHorn()
{
    if(g_POST_DataStructure.bButtonFindMyCar) 
    {
        RTE_vSetHornStatus(true);
        RTE_vSetLightState(true);
    }
    else
    {
        RTE_vSetHornStatus(false);
        if(g_POST_DataStructure.bButtonHonk == true)
        {
            RTE_vSetHornStatus(true);
        }
        else
        {
            RTE_vSetHornStatus(false);
        }
    }
}