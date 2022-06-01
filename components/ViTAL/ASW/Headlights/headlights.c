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
#include "RTE/rte.h"
#include "ASW/Headlights/headlights.h"


void ASW_vControlHeadlights(){
    if(RTE_bGetHeadLightsRequest())
    {
        if(RTE_u16GetLightLevel() < 200)
        {
            RTE_vSetHeadLightsState(HEADLIGHTS_ON);
        }
        else
        {
            RTE_vSetHeadLightsState(HEADLIGHTS_OFF);
        }
    } 
    else{
        RTE_vSetHeadLightsState(HEADLIGHTS_OFF);
    }  
}
