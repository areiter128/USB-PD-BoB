/*******************************************************************************
  PD Generic Timer Header

  Company:
    Microchip Technology Inc.

  File Name:
    generic_timer.h

  Summary:
    PD Generic Timer Header

  Description:
    This header file contains the function prototypes and definitions of the
    data types and constants that make up the interface to the Power delivery modules
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************

Copyright © 2017 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
********************************************************************************

*******************************************************************************/
//DOM-IGNORE-END

#ifndef _GENERIC_TIMER_H_
#define _GENERIC_TIMER_H_
// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

/*Macros for Seconds,Milliseconds,Microseconds to PD Hardware timer Ticks conversion*/
#define SECONDS_TO_TICKS(X)			         (1/CONFIG_PDTIMER_INTERRUPT_RATE)*X
#define MILLISECONDS_TO_TICKS(X)			 (1000/CONFIG_PDTIMER_INTERRUPT_RATE)*X
#define MICROSECONDS_TO_TICKS(X)			 (1000000/CONFIG_PDTIMER_INTERRUPT_RATE)*X

#define GENERIC_TIMER_PORT_NUM        (BIT(3) | BIT(2) | BIT(1) | BIT(0))
#define GENERIC_TIMER_STATE               (BIT(4) | BIT(5))
#define GENERIC_TIMER_NON_ACTIVE          0x00
#define GENERIC_TIMER_ACTIVE              0x10
#define GENERIC_TIMER_EXPIRED             0x20

#define PD_SYS_MAX_CONCURRENT_TIMERS        3

/*Maximum Active concurrent timers for a port identified from PD Specification 3.0 */
#if INCLUDE_POWER_FAULT_HANDLING
	#define PD_SYS_POWER_FAULT_TIMER            2
#else
	#define PD_SYS_POWER_FAULT_TIMER		    0
#endif

#if INCLUDE_POWER_MANAGEMENT_CTRL
	#define PD_SYS_PWR_MNGMNT_CTRL              1
#else
	#define PD_SYS_PWR_MNGMNT_CTRL              0
#endif

#define MAX_CONCURRENT_TIMERS_PER_PORT           PD_SYS_MAX_CONCURRENT_TIMERS + \
                                                 PD_SYS_POWER_FAULT_TIMER + \
                                                 PD_SYS_PWR_MNGMNT_CTRL

/* This variable of size MAX_CONCURRENT_TIMERS is the software timer which stores the timeout value, timer state,
 call back function and arguments to be passed to call back function*/
#define MAX_CONCURRENT_TIMERS				 (CONFIG_PD_PORT_COUNT * MAX_CONCURRENT_TIMERS_PER_PORT)

typedef void(*PDTimerCallback) (UINT8,UINT8);

// *****************************************************************************
// *****************************************************************************
// Section: Data Structures
// *****************************************************************************
// *****************************************************************************
/*****************************************************************************
 PD GENERIC TIMER

  Summary:
    Identifies the generic PD timer information.

  Description:
    This type identifies the generic PD Timer information. Each new timer must have these parameters before starting new timer.

  Remarks:
    Need to be packed always based on type of microcontroller.
*/
typedef struct _Timer CONFIG_STRUCT_PACKED_START
{
  
#if defined(CONFIG_16_BIT_PDTIMEOUT)
	
	UINT16 u16Timeout_Tickcnt;			
#else
	
	UINT32 u32Timeout_Tickcnt;			
#endif	
	
	PDTimerCallback pfnTimerCallback;	

	
	volatile UINT8 u8TimerSt_PortNum;		

	
	UINT8 u8PDState;					

} CONFIG_STRUCT_PACKED_END  PDTIMER;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

/**************************************************************************************************
    Function:
        UINT8 PDTimer_Init ()

	Summary:
		Initializes the PD Timer variables and starts the PD Hardware timer

	Devices Supported:
		UPD350 REV A

	Description:
		This API is called in the PD Stack initilization sequence to start the Hardware Timer dedicated for the USB Power delivery. 
		All the software Timers are disabled and the User implemented API which configures the Hardware timer for specified Interrupt rate is called inside this function

	Precondition:
		None.

	Parameters:
		None

	Returns:
		UINT8.

	Remarks:
		CONFIG_HOOK_HW_PDTIMER_INIT() API called inside this function is defined by user which configures and starts the Hardware timer
**************************************************************************************************/
UINT8 PDTimer_Init();
/**************************************************************************************************

    Function:
        UINT8 PDTimer_Start (UINT32 u32Timeout_ticks, PDTimerCallback pfnTimerCallback, UINT8 u8PortNum, UINT8 u8PDState)

	Summary:
		Starts the Software timer for a given timeout

	Devices Supported:
		UPD350 REV A

	Description:
		This API will start the software timer for a given timeout

	Precondition:
		None.

	Parameters:
		u32Timeout_ticks - Timeout value in ticks
		pfnTimerCallback - Address of the Callback function to be executed after the software timer expiration
		u8PortNum - Port Number for which the timeout has to be set
		u8PDState - PD State that will be passed as an argument to the callback function

	Returns:
		UINT8.

	Remarks:
	Callback function address passed as an argument to the API can be NULL if there are no functions to be executed after the timer expiration
**************************************************************************************************/
UINT8 PDTimer_Start(UINT32 u32Timeout_ticks, PDTimerCallback pfnTimerCallback, UINT8 u8PortNum, UINT8 u8PDState);
/**************************************************************************************************
    Function:
		void PDTimer_WaitforTicks (UINT32 u32Timeout_ticks);

	Summary:
		Function used to start a blocking timer
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is called to start a blocking timer.

	Precondition:
		None.

	Parameters:
		u32Timeout_ticks - Timeout for which blocking timer has to be started

	Return:
		None.

	Remarks:
		None.
**************************************************************************************************/
void PDTimer_WaitforTicks (UINT32 u32Timeout_ticks);
/**************************************************************************************************

    Function:
        void PDTimer_Kill (UINT8 u8TimerID)

	Summary:
		Stops the Software timer for a given Timer ID

	Devices Supported:
		UPD350 REV A

	Description:
		This API will stop the software timer with a given timer ID and set the timer state as "NON ACTIVE"

	Precondition:
		None.

	Parameters:
		u8TimerID - Timer ID of the Software Timer to be stopped

	Returns:
		None.

	Remarks:
		None
**************************************************************************************************/
void PDTimer_Kill(UINT8 u8TimerID);
/**************************************************************************************************
	Function:
        void PDTimer_KillPortTimers (UINT8 u8PortNum)

	Summary:
		Stops all the active Software timers for a given Port Number

	Devices Supported:
		UPD350 REV A

	Description:
		This API will stop all the software timer for a given Port and set the timer state as "NON_ACTIVE"

	Precondition:
		None.

	Parameters:
		u8PortNum - Port Number for which all the Software Timer to be stopped

	Return:
		None.

	Remarks:
		None
**************************************************************************************************/
void PDTimer_KillPortTimers(UINT8 u8PortNum);
/*************************************************************************************************
	Function:
		void PDTimer_InterruptHandler();

	Summary:
		Interrupt Handler for the USB Power delivery Hardware Timer
	
	Devices Supported:
		UPD350 REV A

	Description:
		This API is the interrpt service routine for the interrupts generated by PD Hardware timer. 
		All the software timer's timeout values are updated and checked for timeout expiration. If the timeout has expired , then the callback function for the software timer is executed

	Precondition:
		None.

	Parameters:
		None.

	Return:
		None.

	Remarks:
		This API has to be configured by the user as a ISR of PD Hardware timer Interrupts.
**************************************************************************************************/
void PDTimer_InterruptHandler();
/**************************************************************************************************/
#endif