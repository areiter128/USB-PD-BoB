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
/*!apl.c
 * ****************************************************************************
 * File:   init_fosc.c
 * Author: M91406
 *
 * Created on October 23, 2017, 5:17 PM
 * ****************************************************************************/

#include "mcal/mcal.h"


/*!MainOscillator_Initialize()
 * ************************************************************************************************
 * Summary:
 * Initializes the CPU main oscillator system
 * 
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 * 
 * Description:
 * Initializes the main oscillator including its PLL and performs the switch-over to the 
 * desired CPU frequency. 
 * 
 * Please Note:
 * 
 * ***********************************************************************************************/

volatile uint16_t MainOscillator_Initialize(void) {
    
    volatile uint16_t fres = 1;

    fres &= init_FRCCLK_Defaults(MAIN_CLOCK_SPEED);

    return(fres);
}

/*!AuxOscillator_Initialize()
 * ************************************************************************************************
 * Summary:
 * Initializes the auxiliary oscillator system
 * 
 * Parameters:
 * (none)
 * 
 * Returns:
 * 0 = FALSE
 * 1 = TRUE
 * 
 * Description:
 * Initializes the auxiliary oscillator including its PLL and verifies that the PLL has locked 
 * in at the desired frequency. The auxiliary oscillator is providing the base clock for 
 * peripheral modules such as PWM, ADC or PDM DAC.
 * 
 * Please Note:
 * 
 * ***********************************************************************************************/

volatile uint16_t AuxOscillator_Initialize(void) {

    volatile uint16_t fres = 1;
    
    fres &= init_AUXCLK_Defaults(AUX_CLOCK_SPEED);
   
    return(fres);
}

