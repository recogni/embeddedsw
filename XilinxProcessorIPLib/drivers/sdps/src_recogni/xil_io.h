/******************************************************************************
* Copyright (c) 2014 - 2020 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xil_io.h
*
* @addtogroup common_io_interfacing_apis Register IO interfacing APIs
*
* The xil_io.h file contains the interface for the general I/O component, which
* encapsulates the Input/Output functions for the processors that do not
* require any special I/O handling.
*
* @{
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who      Date     Changes
* ----- -------- -------- -----------------------------------------------
* 5.00 	pkp  	 05/29/14 First release
* 6.00  mus      08/19/16 Remove checking of __LITTLE_ENDIAN__ flag for
*                         ARM processors
* 7.20  har      01/03/20 Added Xil_SecureOut32 for avoiding blindwrite for
*                         CR-1049218
* </pre>
******************************************************************************/

#ifndef XIL_IO_H           /* prevent circular inclusions */
#define XIL_IO_H           /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xil_printf.h"
#include "xstatus.h"

#include "xpseudo_asm.h"

/************************** Function Prototypes ******************************/
u16 Xil_EndianSwap16(u16 Data);
u32 Xil_EndianSwap32(u32 Data);
#ifdef ENABLE_SAFETY
extern u32 XStl_RegUpdate(u32 RegAddr, u32 RegVal);
#endif

/***************** Macros (Inline Functions) Definitions *********************/
#  define SYNCHRONIZE_IO	dmb()
#  define INST_SYNC		isb()
#  define DATA_SYNC		dsb()

#define INLINE inline

#ifdef HAVE_SD_HW  //No HW yet on ARIANE FPGA
/*****************************************************************************/
/**
*
* @brief    Performs an input operation for a memory location by reading
*           from the specified address and returning the 8 bit Value read from
*            that address.
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 8 bit Value read from the specified input address.

*
******************************************************************************/
static INLINE u8 Xil_In8(UINTPTR Addr)
{
	return *(volatile u8 *) Addr;
}

/*****************************************************************************/
/**
*
* @brief    Performs an input operation for a memory location by reading from
*           the specified address and returning the 16 bit Value read from that
*           address.
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 16 bit Value read from the specified input address.
*
******************************************************************************/
static INLINE u16 Xil_In16(UINTPTR Addr)
{
	return *(volatile u16 *) Addr;
}

/*****************************************************************************/
/**
*
* @brief    Performs an input operation for a memory location by
*           reading from the specified address and returning the 32 bit Value
*           read  from that address.
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 32 bit Value read from the specified input address.
*
******************************************************************************/
static INLINE u32 Xil_In32(UINTPTR Addr)
{
	return *(volatile u32 *) Addr;
}

/*****************************************************************************/
/**
*
* @brief     Performs an input operation for a memory location by reading the
*            64 bit Value read  from that address.
*
*
* @param	Addr: contains the address to perform the input operation
*
* @return	The 64 bit Value read from the specified input address.
*
******************************************************************************/
static INLINE u64 Xil_In64(UINTPTR Addr)
{
	return *(volatile u64 *) Addr;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for an memory location by
*           writing the 8 bit Value to the the specified address.
*
* @param	Addr: contains the address to perform the output operation
* @param	Value: contains the 8 bit Value to be written at the specified
*           address.
*
* @return	None.
*
******************************************************************************/
static INLINE void Xil_Out8(UINTPTR Addr, u8 Value)
{
	volatile u8 *LocalAddr = (volatile u8 *)Addr;
	*LocalAddr = Value;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for a memory location by writing the
*            16 bit Value to the the specified address.
*
* @param	Addr contains the address to perform the output operation
* @param	Value contains the Value to be written at the specified address.
*
* @return	None.
*
******************************************************************************/
static INLINE void Xil_Out16(UINTPTR Addr, u16 Value)
{
	volatile u16 *LocalAddr = (volatile u16 *)Addr;
	*LocalAddr = Value;
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for a memory location by writing the
*           32 bit Value to the the specified address.
*
* @param	Addr contains the address to perform the output operation
* @param	Value contains the 32 bit Value to be written at the specified
*           address.
*
* @return	None.
*
******************************************************************************/
static INLINE void Xil_Out32(UINTPTR Addr, u32 Value)
{
#ifndef ENABLE_SAFETY
	volatile u32 *LocalAddr = (volatile u32 *)Addr;
	*LocalAddr = Value;
#else
	XStl_RegUpdate(Addr, Value);
#endif
}

/*****************************************************************************/
/**
*
* @brief    Performs an output operation for a memory location by writing the
*           64 bit Value to the the specified address.
*
* @param	Addr contains the address to perform the output operation
* @param	Value contains 64 bit Value to be written at the specified address.
*
* @return	None.
*
******************************************************************************/
static INLINE void Xil_Out64(UINTPTR Addr, u64 Value)
{
	volatile u64 *LocalAddr = (volatile u64 *)Addr;
	*LocalAddr = Value;
}

/*****************************************************************************/
/**
 *
 * @brief	Performs an output operation for a memory location by writing the
 *       	32 bit Value to the the specified address and then reading it
 *       	back to verify the value written in the register.
 *
 * @param	Addr contains the address to perform the output operation
 * @param	Value contains 32 bit Value to be written at the specified address
 *
 * @return	Returns Status
 *        	- XST_SUCCESS on success
 *        	- XST_FAILURE on failure
 *
 *****************************************************************************/
static INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 Value)
{
	u32 ReadReg;
	u32 ReadRegTemp;
	u32 Status = (u32)XST_FAILURE;

	Xil_Out32(Addr, Value);

	ReadReg = Xil_In32(Addr);
	ReadRegTemp = Xil_In32(Addr);

	if( (ReadReg == Value) && (ReadRegTemp == Value) ) {
		Status = (u32)XST_SUCCESS;
	}

	return Status;
}
#else //No HW yet
static INLINE u8 Xil_In8(UINTPTR Addr) { return 0; }
static INLINE u16 Xil_In16(UINTPTR Addr) { return 0; }
static INLINE u32 Xil_In32(UINTPTR Addr) { return 0; }
static INLINE u64 Xil_In64(UINTPTR Addr) { return 0; }
static INLINE void Xil_Out8(UINTPTR Addr, u8 Value) { return; }
static INLINE void Xil_Out16(UINTPTR Addr, u16 Value) { return; }
static INLINE void Xil_Out32(UINTPTR Addr, u32 Value) { return; }
static INLINE void Xil_Out64(UINTPTR Addr, u64 Value) { return; }
static INLINE u32 Xil_SecureOut32(UINTPTR Addr, u32 Value) { return 0; }
#endif //HAVE_SD

# define Xil_In16LE	Xil_In16
# define Xil_In32LE	Xil_In32
# define Xil_Out16LE	Xil_Out16
# define Xil_Out32LE	Xil_Out32
# define Xil_Htons	Xil_EndianSwap16
# define Xil_Htonl	Xil_EndianSwap32
# define Xil_Ntohs	Xil_EndianSwap16
# define Xil_Ntohl	Xil_EndianSwap32

static INLINE u16 Xil_In16BE(UINTPTR Addr)
{
	u16 value = Xil_In16(Addr);
	return Xil_EndianSwap16(value);
}

static INLINE u32 Xil_In32BE(UINTPTR Addr)
{
	u32 value = Xil_In32(Addr);
	return Xil_EndianSwap32(value);
}

static INLINE void Xil_Out16BE(UINTPTR Addr, u16 Value)
{
	Value = Xil_EndianSwap16(Value);
	Xil_Out16(Addr, Value);
}

static INLINE void Xil_Out32BE(UINTPTR Addr, u32 Value)
{
	Value = Xil_EndianSwap32(Value);
	Xil_Out32(Addr, Value);
}

#ifdef __cplusplus
}
#endif

#endif /* end of protection macro */
/**
* @} End of "addtogroup common_io_interfacing_apis".
*/
