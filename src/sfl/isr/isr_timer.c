/*LICENSE *****************************************************************************
 * 
 * Software License Agreement
 *
 * Copyright � 2015 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED ìAS ISî WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 **************************************************************************** */
/*
 * File:   isr_timer.c
 * Author: M91406
 *
 * Created on December 19, 2016, 11:12 AM
 **************************************************************************** */


// Device header file
#include <xc.h>
#include <stdint.h>

#include "apl/apl.h"
#include "hal/hal.h"
#include "mcal/mcal.h"
#include "sfl/sfl.h"

/***************************************************************************
ISR: 		T1Interrupt for Timer #1
Description:	
***************************************************************************/
#if defined (T1CON)
void __attribute__((__interrupt__,no_auto_psv)) _T1Interrupt() 
{	

	IFS0bits.T1IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

/***************************************************************************
ISR: 		T2Interrupt for Timer #2
Description:	
***************************************************************************/
#if defined (T2CON)
void __attribute__((__interrupt__,no_auto_psv)) _T2Interrupt() 
{	

	IFS0bits.T2IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

/***************************************************************************
ISR: 		T3Interrupt for Timer #3
Description:	
***************************************************************************/
#if defined (T3CON)
void __attribute__((__interrupt__,no_auto_psv)) _T3Interrupt() 
{	

	IFS0bits.T3IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

/***************************************************************************
ISR: 		T4Interrupt for Timer #4
Description:	
***************************************************************************/
#if defined (T4CON)
void __attribute__((__interrupt__,no_auto_psv)) _T4Interrupt() 
{	

	IFS1bits.T4IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

/***************************************************************************
ISR: 		T5Interrupt for Timer #5
Description:	
***************************************************************************/
#if defined (T5CON)
void __attribute__((__interrupt__,no_auto_psv)) _T5Interrupt() 
{	

	IFS1bits.T5IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

/***************************************************************************
ISR: 		T6Interrupt for Timer #6
Description:	
***************************************************************************/
#if defined (T6CON)
void __attribute__((__interrupt__,no_auto_psv)) _T6Interrupt() 
{	

	IFS1bits.T6IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

/***************************************************************************
ISR: 		T7Interrupt for Timer #7
Description:	
***************************************************************************/
#if defined (T7CON)
void __attribute__((__interrupt__,no_auto_psv)) _T7Interrupt() 
{	

	IFS1bits.T7IF = 0;	// Clear interrupt flag bit
	
	return;

}
#endif
/***************************************************************************
End of ISR
***************************************************************************/

// EOF
