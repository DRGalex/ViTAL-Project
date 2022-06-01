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
#include "RTE/rte.h"
#include "ASW/Ambient_Light/ambient_light.h"
void ASW_vControlAmbientLights()
{
    if(RTE_bGetAllButton())
    {
        RTE_vSetLightState(true);
    }
    else
    {
        RTE_vSetLightState(false);
    }
}