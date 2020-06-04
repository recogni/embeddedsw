/******************************************************************************
* Copyright (C) 2013 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xsdps_g.c
* @addtogroup sdps_v3_9
* @{
*
* This file contains a configuration table that specifies the configuration of
* SD devices in the system.
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who    Date     Changes
* ----- ---    -------- -----------------------------------------------
* 1.00a hk/sg  10/17/13 Initial release
* 3.6   mn     07/06/18 Add initialization macros in sdps
*       mn     07/13/18 Add initializer macro for HasEMIO
*
* </pre>
*
******************************************************************************/



#include "xparameters.h"
#include "xsdps.h"

/*
* The configuration table for devices
*/

XSdPs_Config XSdPs_ConfigTable[] =
{
	{
		SD_0_DEVICE_ID,
		SD_0_BASEADDR,
		SD_0_SDIO_CLK_FREQ_HZ,
		SD_0_HAS_CD,
		SD_0_HAS_WP,
		SD_0_BUS_WIDTH,
		SD_0_MIO_BANK,
		SD_0_HAS_EMIO,
		SD_0_IS_CACHE_COHERENT
	}
};
/** @} */
