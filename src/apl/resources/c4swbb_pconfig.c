/*
 * File:   c4swbb_pconfig.c
 * Author: M91406
 *
 * Created on September 12, 2019, 2:25 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "apl/resources/c4swbb_pconfig.h"   // 4-Switch Buck/Boost Power Control State Machine Header


/*!c4swbb_pwm_module_initialize()
 * *****************************************************************************************************
 * Summary:
 * Initializes the PWM module base register set for 4-switch buck/boost controller operation
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter uses two half-bridges to convert power from input to output.
 * These two half bridges are called 'buck leg' (stepping voltage down) and 'boost leg' (stepping
 * voltage up). Each half-bridge is driven by one individual PWM generator configured in complementary 
 * mode. Both PWM generators need to have precisely synchronized switching periods and therefore have 
 * to operate off the same timebase. 
 * 
 * In this routine the PWM module base register set is configured for high speed, high resolution 
 * operation. All specific settings such as clock source and divider, combinatorial output logic
 * and PWM events are pre-configured in the 'c4swbb_pconfig.h' header file and loaded into the 
 * PWM module base generator registers directly by this routine.
 * 
 * Please note:
 * Any user modification of PWM module base register settings should be down externally AFTER
 * having called this routine.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_pwm_module_initialize(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {

    volatile uint16_t fres = 1;
    volatile HSPWM_C_MODULE_CONFIG_t pmod_cfg;

    // Initialize PWM module
    pmod_cfg.PCLKCON.bits.HRRDY = 0; // Clear HIGH RESOLUTION READY STATUS bit
    pmod_cfg.PCLKCON.bits.HRERR = 0; // Clear HIGH RESOLUTION ERROR STATUS bit
    pmod_cfg.PCLKCON.bits.LOCK = PCLKCON_LOCK_UNLOCKED; // Keep PWM registers unlocked during operation
    pmod_cfg.PCLKCON.bits.MCLKSEL = PCLKCON_MCLKSEL_AFPLLO; // Use auxiliary PLL as clock source
    pmod_cfg.PCLKCON.bits.DIVSEL = PCLKCON_DIVSEL_DIV_2; // Select default 'by 2' divider (minimum)
    
    pmod_cfg.FSCL.value = 0;  // Clear frequency scaling register
    pmod_cfg.FSMINPER.value = 0;  // Clear frequency scaling minimum period register
    pmod_cfg.LFSR.value = 0; // Clear linear feedback shift register
    pmod_cfg.MDC.value = 0; // Clear Master Duty Cycle register
    pmod_cfg.MPER.value = 0; // Clear Master Period register
    pmod_cfg.MPHASE.value = 0; // Clear Master Phase register
    
    pmod_cfg.LOGCONA.value = 0; // Clear combinatorial PWM logic control register A
    pmod_cfg.LOGCONB.value = 0; // Clear combinatorial PWM logic control register B
    pmod_cfg.LOGCONC.value = 0; // Clear combinatorial PWM logic control register C
    pmod_cfg.LOGCOND.value = 0; // Clear combinatorial PWM logic control register D
    pmod_cfg.LOGCONE.value = 0; // Clear combinatorial PWM logic control register E
    pmod_cfg.LOGCONF.value = 0; // Clear combinatorial PWM logic control register F

    pmod_cfg.CMBTRIG.value = 0;  // Disable all Combinatorial Logic PWM triggers

    pmod_cfg.PWMEVTA.value = 0; // Clear PWM event output control register A
    pmod_cfg.PWMEVTB.value = 0; // Clear PWM event output control register A
    pmod_cfg.PWMEVTC.value = 0; // Clear PWM event output control register A
    pmod_cfg.PWMEVTD.value = 0; // Clear PWM event output control register A
    pmod_cfg.PWMEVTE.value = 0; // Clear PWM event output control register A
    pmod_cfg.PWMEVTF.value = 0; // Clear PWM event output control register A
    
    // Set user defined settings
    pmod_cfg.MPER.value = pInstance->buck_leg.period;
    
    // call module configuration function
    fres &= hspwm_init_pwm_module(pmod_cfg);
    
    
    return(fres);
    
}

/*!c4swbb_pwm_generators_initialize()
 * *****************************************************************************************************
 * Summary:
 * Initializes the individual PWM generator register sets for 4-switch buck/boost controller operation
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter uses two half-bridges to convert power from input to output.
 * These two half bridges are called 'buck leg' (stepping voltage down) and 'boost leg' (stepping
 * voltage up). Each half-bridge is driven by one individual PWM generator configured in complementary 
 * mode. Both PWM generators need to have precisely synchronized switching periods and therefore have 
 * to operate off the same timebase. 
 * 
 * Please note:
 * In this routine the individual PWM generator configuration is being loaded into the PWM generator 
 * registers directly. Before calling this routine, all user-specific settings need to be configured  
 * in a C4SWBB_POWER_CONTROLLER_t data structure object. Only settings which are not covered by the
 * pre-configuration will be taken from the C4SWBB_POWER_CONTROLLER_t object, such as dead times and 
 * leading-edge blanking periods. 
 *
 * The PWM module will always remain disabled.
 * 
 * If you need to make user-specific changes to the PWM generator configuration, these should be 
 * done AFTER this routine has been called and before enabling the PWM module.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_pwm_generators_initialize(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {

    volatile uint16_t fres = 1;
    volatile HSPWM_C_GENERATOR_CONFIG_t pg_config;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }
    
    // Initialize PWM generator for buck leg 
    pg_config.PGxCON.value = (((uint32_t)C4SWBB_BUCKLEG_PGxCONH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxCONL));
    pg_config.PGxSTAT.value = C4SWBB_BUCKLEG_PGxSTAT;
    pg_config.PGxIOCON.value = (((uint32_t)C4SWBB_BUCKLEG_PGxIOCONH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxIOCONL));
    pg_config.PGxEVT.value = (((uint32_t)C4SWBB_BUCKLEG_PGxEVTH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxEVTL));
    pg_config.PGxFPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxFPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxFPCIL));
    pg_config.PGxCLPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxCLPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxCLPCIL));
    pg_config.PGxFFPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxFFPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxFFPCIL));
    pg_config.PGxSPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxSPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxSPCIL));
    pg_config.PGxLEBCON.value = (((uint32_t)C4SWBB_BUCKLEG_PGxLEBH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxLEBL));
    
    // PWM timing configuration PWM generator Buck Leg
    pg_config.PGxLEB.value = C4SWBB_BOOSTLEG_PGxLEBL;   // reset LEB period to ZERO
    pg_config.PGxPHASE.value = C4SWBB_BUCKLEG_PGxPHASE; // reset PWM phase shift to ZERO
    pg_config.PGxDC.value = C4SWBB_BUCKLEG_PGxDC;       // reset PWM duty cycle to ZERO
    pg_config.PGxDCA.value = C4SWBB_BUCKLEG_PGxDCA;     // reset PWM duty cycle adjustment to ZERO
    pg_config.PGxPER.value = C4SWBB_BUCKLEG_PGxPER;     // reset PWM period to ZERO
    pg_config.PGxDT.value = (((uint32_t)C4SWBB_BUCKLEG_PGxDTH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxDTL)); // Reset half-bridge dead-times to DEFAULT
    pg_config.PGxTRIGA.value = C4SWBB_BUCKLEG_PGxTRIGA; // reset PWM trigger A compare register
    pg_config.PGxTRIGB.value = C4SWBB_BUCKLEG_PGxTRIGB; // reset PWM trigger B compare register
    pg_config.PGxTRIGC.value = C4SWBB_BUCKLEG_PGxTRIGC; // reset PWM trigger C compare register
    pg_config.PGxCAP.value = C4SWBB_BUCKLEG_PGxCAP;     // reset PWM capture result register

    // Overriding pre-configured settings with user settings
    pg_config.PGxLEB.value = pInstance->buck_leg.leb_period;   // leading edge blanking period
    pg_config.PGxDT.value = (((uint32_t)pInstance->buck_leg.dead_time_rising << 16) | // Rising edge dead time
                             ((uint32_t)pInstance->buck_leg.dead_time_falling));      // Falling edge dead time
    pg_config.PGxDC.value = pInstance->buck_leg.duty_ratio_init;   // initial PWM duty cycle
    pg_config.PGxPHASE.value = pInstance->buck_leg.phase;   // initial PWM phase shift
    pg_config.PGxIOCON.bits.SWAP = (pInstance->buck_leg.pwm_swap & 0x0001); // PWMxH/PWMxL output pin swap setting
    pg_config.PGxIOCON.bits.OVRDAT = (pInstance->buck_leg.pwm_ovrdat & 0x0003); // Override OVR pin-state of PWMxH/PWMxL
    
    // Write PWM generator configuration to PWM module
    fres &= hspwm_init_pwm_generator(pInstance->buck_leg.pwm_instance, pg_config);


    // Initialize PWM generator for Boost leg
    pg_config.PGxCON.value = (((uint32_t)C4SWBB_BUCKLEG_PGxCONH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxCONL));
    pg_config.PGxSTAT.value = C4SWBB_BUCKLEG_PGxSTAT;
    pg_config.PGxIOCON.value = (((uint32_t)C4SWBB_BUCKLEG_PGxIOCONH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxIOCONL));
    pg_config.PGxEVT.value = (((uint32_t)C4SWBB_BUCKLEG_PGxEVTH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxEVTL));
    pg_config.PGxFPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxFPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxFPCIL));
    pg_config.PGxCLPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxCLPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxCLPCIL));
    pg_config.PGxFFPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxFFPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxFFPCIL));
    pg_config.PGxSPCI.value = (((uint32_t)C4SWBB_BUCKLEG_PGxSPCIH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxSPCIL));
    pg_config.PGxLEBCON.value = (((uint32_t)C4SWBB_BUCKLEG_PGxLEBH << 16) | ((uint32_t)C4SWBB_BUCKLEG_PGxLEBL));
    
    // PWM timing configuration PWM generator Boost Leg
    pg_config.PGxLEB.value = C4SWBB_BOOSTLEG_PGxLEBL;
    pg_config.PGxPHASE.value = C4SWBB_BOOSTLEG_PGxPHASE;
    pg_config.PGxDC.value = C4SWBB_BOOSTLEG_PGxDC;
    pg_config.PGxDCA.value = C4SWBB_BOOSTLEG_PGxDCA;
    pg_config.PGxPER.value = C4SWBB_BOOSTLEG_PGxPER;
    pg_config.PGxDT.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxDTH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxDTL));
    pg_config.PGxTRIGA.value = C4SWBB_BOOSTLEG_PGxTRIGA;
    pg_config.PGxTRIGB.value = C4SWBB_BOOSTLEG_PGxTRIGB;
    pg_config.PGxTRIGC.value = C4SWBB_BOOSTLEG_PGxTRIGC;
    pg_config.PGxCAP.value = C4SWBB_BOOSTLEG_PGxCAP;

    // Overriding pre-configured settings with user settings
    pg_config.PGxLEB.value = pInstance->boost_leg.leb_period;   // leading edge blanking period
    pg_config.PGxDT.value = (((uint32_t)pInstance->boost_leg.dead_time_rising << 16) | // Rising edge dead time
                             ((uint32_t)pInstance->boost_leg.dead_time_falling));      // Falling edge dead time
    pg_config.PGxDC.value = pInstance->boost_leg.duty_ratio_init;   // initial PWM duty cycle
    pg_config.PGxPHASE.value = pInstance->boost_leg.phase;   // initial PWM phase shift
    pg_config.PGxIOCON.bits.SWAP = (pInstance->boost_leg.pwm_swap & 0x0001); // PWMxH/PWMxL output pin swap setting
    pg_config.PGxIOCON.bits.OVRDAT = (pInstance->boost_leg.pwm_ovrdat & 0x0003); // Override OVR pin-state of PWMxH/PWMxL
    
    // Write PWM generator configuration to PWM module
    fres &= hspwm_init_pwm_generator(pInstance->boost_leg.pwm_instance, pg_config);

    return(fres);
    
}

volatile uint16_t c4swbb_pwm_enable(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {

    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Enable PWM channels of buck and boost leg
    fres &= hspwm_enable_pwm(pInstance->buck_leg.pwm_instance, true);
    fres &= hspwm_enable_pwm(pInstance->boost_leg.pwm_instance, true);
    
    return(fres); // return failure/success or error code
    
}

volatile uint16_t c4swbb_pwm_disable(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Disable PWM channels of buck and boost leg
    fres &= hspwm_disable_pwm(pInstance->buck_leg.pwm_instance);
    fres &= hspwm_disable_pwm(pInstance->boost_leg.pwm_instance);
    
    return(fres); // ToDo: need function execution success validation
    
    
}

volatile uint16_t c4swbb_pwm_hold(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Disable PWM generator outputs of buck and boost leg without disabling the PWM
    fres &= hspwm_ovr_hold(pInstance->buck_leg.pwm_instance);
    fres &= hspwm_ovr_hold(pInstance->boost_leg.pwm_instance);
    
    return(fres); // return failure/success or error code
    
}

volatile uint16_t c4swbb_pwm_release(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Disable PWM generator outputs of buck and boost leg without disabling the PWM
    fres &= hspwm_ovr_release(pInstance->buck_leg.pwm_instance);
    fres &= hspwm_ovr_release(pInstance->boost_leg.pwm_instance);
    
    return(fres); // return failure/success or error code
    
}

volatile uint16_t c4swbb_adc_module_initialize(volatile C4SWBB_POWER_CONTROLLER_t* pInstance) {
    
    volatile uint16_t fres = 1;
    volatile HSADC_MODULE_CONFIG_t adcmod_cfg;
    
    adcmod_cfg.ADCON1.value = (((uint32_t)C4SWBB_ADC_ADCON1H << 16) | ((uint32_t)C4SWBB_ADC_ADCON1L));
    adcmod_cfg.ADCON2.value = (((uint32_t)C4SWBB_ADC_ADCON2H << 16) | ((uint32_t)C4SWBB_ADC_ADCON2L));
    adcmod_cfg.ADCON3.value = (((uint32_t)C4SWBB_ADC_ADCON3H << 16) | ((uint32_t)C4SWBB_ADC_ADCON3L));
    adcmod_cfg.ADCON4.value = (((uint32_t)C4SWBB_ADC_ADCON4H << 16) | ((uint32_t)C4SWBB_ADC_ADCON4L));
    adcmod_cfg.ADCON5.value = (((uint32_t)C4SWBB_ADC_ADCON5H << 16) | ((uint32_t)C4SWBB_ADC_ADCON5L));
    
    fres &= hsadc_init_adc_module(adcmod_cfg);  // Write ADC module configuration to registers
    
    return(fres);
}