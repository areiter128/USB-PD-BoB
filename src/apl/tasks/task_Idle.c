/*LICENSE ********************************************************************
 * Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 * ***************************************************************************/
/*!task_Idle.c
 * ****************************************************************************
 * File:   task_Idle.c
 * Author: M91406
 *
 * Description:
 * The idle task is an empty function, which does not execute any reasonable 
 * code. This task is added to a task list execution scheme, which requires 
 * more free CPU time or to add reserved time slots within task timing profiles
 * for future use.
 *  * 
 * History:
 * Created on July 27, 2016, 11:32 PM
 ******************************************************************************/


#include "xc.h"
#include <stdint.h>

#include "apl/tasks/task_Idle.h"

/* Private Declarations */

/*!task_Idle
 * ***********************************************************************************************

 * Summary:
 * Source file of idle task
 * 
 * Description:
 * This function is used to register a global function call of the default idle task. The idle task 
 * only executes a single Nop() and is used to keep scheduler tick intervals open.
 * 
 * History:
 * 07/28/2017	File created
 * ***********************************************************************************************/

volatile uint16_t task_Idle(void) {
// Idle tasks might be required to free up additional CPU load for higher
// priority processes. THerefore it's recommended to leave at least 
// one Idle cycle in each task list
    Nop();
    return(1);
}
