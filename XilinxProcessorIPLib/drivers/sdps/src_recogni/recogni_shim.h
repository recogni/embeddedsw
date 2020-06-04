
#ifndef __RECOGNI_SHIM_
#define __RECOGNI_SHIM_

#include "FreeRTOS.h"
#include "task.h"
#include "types.h"

typedef unsigned long       uintptr_t;
typedef long                intptr_t;
typedef long                ptrdiff_t;

typedef intptr_t INTPTR;
typedef uintptr_t UINTPTR;
typedef ptrdiff_t PTRDIFF;

#define usleep(x) vTaskDelay(x)

#define Xil_AssertVoid(x)                \
{                                                  \
    if ((x) == 0)                 \
    {                             \
        __asm volatile("ebreak"); \
        for (;;)                  \
            ;                     \
    }                             \
}

#define Xil_AssertNonvoid(x)             \
{                                                  \
    if ((x) == 0)                 \
    {                             \
        __asm volatile("ebreak"); \
        for (;;)                  \
            ;                     \
    }                             \
}

#define Xil_AssertVoidAlways()                   \
{                                                  \
        __asm volatile("ebreak"); \
        for (;;)                  \
            ;                     \
}

#define Xil_AssertNonvoidAlways()                \
{                                                  \
        __asm volatile("ebreak"); \
        for (;;)                  \
            ;                     \
}


/*Return Values from xsdps_init() */
#define SD_CARD_NOT_PRESENT     -1
#define SD_CONTROLLER_INIT_FAIL -2
#define SD_CARD_INIT_FAIL       -3

//XXX
#define Xil_DCacheFlushRange Xil_DCacheInvalidateRange
extern void Xil_DCacheInvalidateRange(INTPTR adr, INTPTR len);


#define XIL_COMPONENT_IS_READY     0x11111111U  
#define XIL_COMPONENT_IS_STARTED   0x22222222U  

/* Definitions for driver SDPS */
#define ARIANE_XSDPS_NUM_INSTANCES 1

/* Definitions from zc702/xparemters.h .. just anything for now */
#define SD_0_BASEADDR ARIANE_SDHCIBase
#define SD_0_DEVICE_ID 0
#define SD_0_SDIO_CLK_FREQ_HZ 50000000
#define SD_0_HAS_CD 1
#define SD_0_HAS_WP 1
#define SD_0_BUS_WIDTH 1
#define SD_0_MIO_BANK 0
#define SD_0_HAS_EMIO 0
#define SD_0_IS_CACHE_COHERENT 0

#endif // __RECOGNI_SHIM_
