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
/*!main.c
 * ****************************************************************************
 * File:   main.c
 * Author: M91406
 *
 * Description:
 * This code example has been created to introduce the functionality of the
 * basic SMPS firmware framework v4. This project uses the basic function call
 * based scheduler to group, align and monitor user tasks. 
 * 
 * The procedure shown in this examples initializes the internal oscillator and 
 * the task scheduler and then immediately launches the scheduler. During the 
 * start-up phase of the controller, configuration of peripherals are also 
 * executed within the active scheduler monitoring & control scheme to be able
 * to respond to errors during the configuration process. This specific aspect
 * is only available if peripheral libraries are used. 
 * If MCC is used to set up the peripherals, the function call SYSTEM_Initialize()
 * will call the MCC generated configuration instead and the operating mode 
 * OP_MODE_BOOT used in this example project needs to be bypassed.
 * 
 * 
 * History:
 * Created on July 03, 2017, 09:32 PM
 ******************************************************************************/

#include "_root/generic/task_scheduler.h"

int main(void) {

    volatile uint16_t fres = 0;
    
#if __DEBUG
// In debug mode these NOPs can be used to place a breakpoint before
// the start of the main task scheduler
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
#endif
    
    fres = exec_scheduler();
    
    return(fres);
}
