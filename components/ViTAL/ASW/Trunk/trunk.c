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
#include "ASW/Trunk/trunk.h"
#include"RTE/rte.h"

void ASW_vControlTrunk()
{
    if(RTE_bGetTrunkRequest())
    {
        RTE_vSetTrunkState(TRUNK_OPEN);
    }
    else
    {
        RTE_vSetTrunkState(TRUNK_CLOSE);
    }
}