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
 * Created on May 19, 2019, 09:32 AM
 ******************************************************************************/

#include "_root/generic/os_Scheduler.h"

int main(void) {

#if __DEBUG
// In debug mode these NOPs can be used to place a breakpoint before
// the start of the main task scheduler
    Nop();
    Nop();
    Nop();
#endif
    
    /*!OS_Execute()
     * ****************************************************************
     * Description:
     * The OS scheduler can be called directly by setting the 
     * option START_OS_BEFORE_MAIN = 1, effectively bypassing
     * main() completely.
     * 
     * if START_OS_BEFORE_MAIN = 0, the OS scheduler engine needs
     * to be called manually from main() as a single and sole
     * function call placed here in main() of the user project.
     * 
     * From this point forward the code will be executed within the 
     * task-scheduler main loop. When this loop is terminated due to
     * a device restart (e.g. triggered by a catastrophic fault event),
     * the CPU will either be reset by the scheduler directly or
     * the software is stalled at the end of the OS scheduler function.
     * 
     * Please note: The code will NOT return to main().
     * 
     * ***************************************************************/
    OS_Execute();
        
    return(0);
}
