/*
 * File:   c4swbb_pconfig.c
 * Author: M91406
 *
 * Created on September 12, 2019, 2:25 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "mcal/mcal.h"
#include "apl/resources/power_control/c4swbb_control.h" 
#include "apl/resources/power_control/c4swbb_pconfig.h"   // 4-Switch Buck/Boost Power Control State Machine Header


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

volatile uint16_t c4swbb_pwm_module_initialize(volatile C4SWBB_PWRCTRL_t* pInstance) {

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
    
    // Load PWM configuration defaults from header file
    
    
    // Set user defined settings
    pmod_cfg.MPER.value = pInstance->buck_leg.period;
    
    // call module configuration function
    fres &= smpsHSPWM_Module_Initialize(pmod_cfg);
    
    
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

volatile uint16_t c4swbb_pwm_generators_initialize(volatile C4SWBB_PWRCTRL_t* pInstance) {

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
    pg_config.PGxPER.value = pInstance->boost_leg.period;   // switching period
    pg_config.PGxLEB.value = pInstance->buck_leg.leb_period;   // leading edge blanking period
    pg_config.PGxDT.value = (((uint32_t)pInstance->buck_leg.dead_time_rising << 16) | // Rising edge dead time
                             ((uint32_t)pInstance->buck_leg.dead_time_falling));      // Falling edge dead time
    pg_config.PGxDC.value = pInstance->buck_leg.duty_ratio_init;   // initial PWM duty cycle
    pg_config.PGxPHASE.value = pInstance->buck_leg.phase;   // initial PWM phase shift
    pg_config.PGxIOCON.bits.SWAP = (pInstance->buck_leg.pwm_swap & 0x0001); // PWMxH/PWMxL output pin swap setting
    pg_config.PGxIOCON.bits.OVRDAT = (pInstance->buck_leg.pwm_ovrdat & 0x0003); // Override OVR pin-state of PWMxH/PWMxL
    
    pg_config.PGxEVT.bits.ADTR1EN = (pInstance->buck_leg.adtr1_source & 0x0007); // ADC trigger 1 source is PGxTRIGA/B/C compare event
    pg_config.PGxEVT.bits.ADTR1PS = (pInstance->buck_leg.adtr1_scale & 0x001F); // ADC trigger 1 port-scaler
    pg_config.PGxEVT.bits.ADTR1OFS = (pInstance->buck_leg.adtr1_offset & 0x001F); // ADC trigger 1 port-scaler

    pg_config.PGxEVT.bits.ADTR2EN = (pInstance->buck_leg.adtr2_source & 0x0007); // ADC trigger 2 source is PGxTRIGA/B/C compare event
    
    // ToDo: Complete CUSTOM PWM CONFIGURATION block
    /*
    pg_config.PGxSPCI
    pg_config.PGxFPCI
    pg_config.PGxCLPCI
    pg_config.PGxFFPCI
    */
    
    // Write PWM generator configuration to PWM module
    fres &= smpsHSPWM_Channel_Initialize(pInstance->buck_leg.pwm_instance, pg_config);


    // Initialize PWM generator for Boost leg
    pg_config.PGxCON.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxCONH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxCONL));
    pg_config.PGxSTAT.value = C4SWBB_BOOSTLEG_PGxSTAT;
    pg_config.PGxIOCON.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxIOCONH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxIOCONL));
    pg_config.PGxEVT.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxEVTH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxEVTL));
    pg_config.PGxFPCI.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxFPCIH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxFPCIL));
    pg_config.PGxCLPCI.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxCLPCIH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxCLPCIL));
    pg_config.PGxFFPCI.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxFFPCIH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxFFPCIL));
    pg_config.PGxSPCI.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxSPCIH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxSPCIL));
    pg_config.PGxLEBCON.value = (((uint32_t)C4SWBB_BOOSTLEG_PGxLEBH << 16) | ((uint32_t)C4SWBB_BOOSTLEG_PGxLEBL));
    
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
    pg_config.PGxPER.value = pInstance->boost_leg.period;   // switching period
    pg_config.PGxLEB.value = pInstance->boost_leg.leb_period;   // leading edge blanking period
    pg_config.PGxDT.value = (((uint32_t)pInstance->boost_leg.dead_time_rising << 16) | // Rising edge dead time
                             ((uint32_t)pInstance->boost_leg.dead_time_falling));      // Falling edge dead time
    pg_config.PGxDC.value = pInstance->boost_leg.duty_ratio_init;   // initial PWM duty cycle
    pg_config.PGxPHASE.value = pInstance->boost_leg.phase;   // initial PWM phase shift
    pg_config.PGxIOCON.bits.SWAP = (pInstance->boost_leg.pwm_swap & 0x0001); // PWMxH/PWMxL output pin swap setting
    pg_config.PGxIOCON.bits.OVRDAT = (pInstance->boost_leg.pwm_ovrdat & 0x0003); // Override OVR pin-state of PWMxH/PWMxL

    pg_config.PGxEVT.bits.ADTR1EN = (pInstance->boost_leg.adtr1_source & 0x0007); // ADC trigger 1 source is PGxTRIGA/B/C compare event
    pg_config.PGxEVT.bits.ADTR1PS = (pInstance->boost_leg.adtr1_scale & 0x001F); // ADC trigger 1 port-scaler
    pg_config.PGxEVT.bits.ADTR1OFS = (pInstance->boost_leg.adtr1_offset & 0x001F); // ADC trigger 1 port-scaler

    pg_config.PGxEVT.bits.ADTR2EN = (pInstance->boost_leg.adtr2_source & 0x0007); // ADC trigger 2 source is PGxTRIGA/B/C compare event
    
    // Write PWM generator configuration to PWM module
    fres &= smpsHSPWM_Channel_Initialize(pInstance->boost_leg.pwm_instance, pg_config);

    return(fres);
    
}

/*!c4swbb_pwm_enable()
 * *****************************************************************************************************
 * Summary:
 * Enables both PWM generators of 4-switch buck/boost controller buck and boost leg
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter uses two half-bridges to convert power from input to output.
 * Both PWM generators are enabled by this function while the PWM outputs are kept inactive in 
 * override mode. Please use function c4swbb_pwm_release() to enable the PWM outputs synchronously.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_pwm_enable(volatile C4SWBB_PWRCTRL_t* pInstance) {

    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Enable PWM channels of buck and boost leg
    fres &= c4swbb_pwm_hold(pInstance);
    fres &= smpsHSPWM_Enable(pInstance->buck_leg.pwm_instance, true);
    fres &= smpsHSPWM_Enable(pInstance->boost_leg.pwm_instance, true);
    
    if (fres) { pInstance->status.bits.pwm_active = true; }
    
    return(fres); // return failure/success or error code
    
}

/*!c4swbb_pwm_disable()
 * *****************************************************************************************************
 * Summary:
 * Disables both PWM generators of 4-switch buck/boost controller buck and boost leg
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter uses two half-bridges to convert power from input to output.
 * Both PWM generators are disabled synchronously.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_pwm_disable(volatile C4SWBB_PWRCTRL_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Disable PWM channels of buck and boost leg
    fres &= smpsHSPWM_Disable(pInstance->buck_leg.pwm_instance);
    fres &= smpsHSPWM_Disable(pInstance->boost_leg.pwm_instance);
    
    if (fres) { pInstance->status.bits.pwm_active = false; }
    
    return(fres); // ToDo: need function execution success validation
    
    
}

/*!c4swbb_pwm_hold()
 * *****************************************************************************************************
 * Summary:
 * Disables both PWM generator outputs of 4-switch buck/boost controller buck and boost leg
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter uses two half-bridges to convert power from input to output.
 * Both PWM generator outputs are disabled here synchronously while the PWM generator itself keeps
 * running. The turn-off event occurs at the end of an active switching cycle. The output pins will 
 * be kept in the state defined by the OVRDAT override bits.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_pwm_hold(volatile C4SWBB_PWRCTRL_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Disable PWM generator outputs of buck and boost leg without disabling the PWM
    fres &= smpsHSPWM_OVR_Hold(pInstance->buck_leg.pwm_instance);
    fres &= smpsHSPWM_OVR_Hold(pInstance->boost_leg.pwm_instance);
    
    return(fres); // return failure/success or error code
    
}

/*!c4swbb_pwm_release()
 * *****************************************************************************************************
 * Summary:
 * Enables both PWM generator outputs of 4-switch buck/boost controller buck and boost leg
 *
 * Parameters: 
 *  volatile C4SWBB_POWER_CONTROLLER_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter uses two half-bridges to convert power from input to output.
 * Both PWM generator outputs are enabled here synchronously. As the PWM generator itself keeps
 * running when kept in hold, the turn-on event occurs at the end of an active switching cycle. 
 * The output pins will turn on synchronously. 
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_pwm_release(volatile C4SWBB_PWRCTRL_t* pInstance) {
    
    volatile uint16_t fres = 1;
    
    // If pointer to controller object is not initialized, return error code
    if(pInstance == NULL) { return(0); }

    // Disable PWM generator outputs of buck and boost leg without disabling the PWM
    fres &= smpsHSPWM_OVR_Release(pInstance->buck_leg.pwm_instance);
    fres &= smpsHSPWM_OVR_Release(pInstance->boost_leg.pwm_instance);
    
    return(fres); // return failure/success or error code
    
}

/*!c4swbb_adc_module_initialize()
 * *****************************************************************************************************
 * Summary:
 * Initializes the ADC Module with default settings for maximum performance
 *
 * Parameters: 
 *  (none)
 *
 * Description:
 * The 4-switch buck boost converter power controller supports up to four signals while running: 
 * output voltage, output current, input voltage and temperature. The main control loop is based on 
 * output voltage and output current. Input voltage is incorporated to optimize soft-start and gain,
 * temperature is used for power balancing and protection. All four signals are triggered by the 
 * same PWM source and sampled at different ADC inputs. 
 * 
 * The ADC initialization covers basic configurations like data format, clock sources and dividers
 * as well as specific configurations for ADC cores. These settings are general, basic settings
 * and not related to specific analog inputs. The standard configuration set here sets up the 
 * ADC module and ADC cores for maximum performance.
 * 
 * The basic configuration of the ADC module is initialized here while the individual ADC inputs 
 * are set by function c4swbb_adc_inputs_initialize(),
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_adc_module_initialize(void) {

    volatile uint16_t fres = 1;
    volatile HSADC_ADMODCFG_t admod_cfg;
    
    // Initialize ADC Converter
    // ========================
    // The ADC channels configured here are covering sampling of input voltage, output voltage, 
    // output current and temperature of each converter. All other ADC configurations for other 
    // functions outside the power control scope need to be done elsewhere
    
    // Load default ADC configuration
    admod_cfg.config.adon = ADCON1_ADON_ENABLED;
    admod_cfg.config.adsidl = ADCON1_ADSIDL_RUN;
    admod_cfg.config.form = ADCON1_FORM_INTEGER;
    admod_cfg.config.ptgen = ADCON2_PTGEN_DISABLED;
    admod_cfg.config.eien = ADCON2_EIEN_ENABLED;
    admod_cfg.config.warmtime = ADCON5H_WARMTIME_CLK_32768;
    
    admod_cfg.refcfg.refsel = ADCON3_REFSEL_AVDD_AVSS;
    admod_cfg.refcfg.refcie = ADCON2_REFCIE_DISABLED;
    admod_cfg.refcfg.refercie = ADCON2_REFERCIE_DISABLED;
    
    admod_cfg.swtrig.cnvchsel = ADCON3_CNVCHSEL_AN0;
    admod_cfg.swtrig.suspcie = ADCON3_SUSPCIE_ENABLED;
    admod_cfg.swtrig.suspend = ADCON3_SUSPEND_RUN;

    admod_cfg.cores.clksel = ADCON3_CLKSEL_AFVCODIV;
    admod_cfg.cores.clkdiv = ADCON3_CLKDIV_1;

    admod_cfg.cores.shared_core.adcs = ADCORE_ADCS_DEFAULT;
    admod_cfg.cores.shared_core.eisel = ADCORE_EISEL_8TAD;
    admod_cfg.cores.shared_core.res = ADCORE_RES_12BIT;
    admod_cfg.cores.shared_core.samc = ADCORE_SAMC_0010;
    
    admod_cfg.cores.core0.adcs = ADCORE_ADCS_DEFAULT;
    admod_cfg.cores.core0.eisel = ADCORE_EISEL_8TAD;
    admod_cfg.cores.core0.res = ADCORE_RES_12BIT;
    admod_cfg.cores.core0.samc = ADCORE_SAMC_0002;
    admod_cfg.cores.core0.samc_en = ADCON4_SAMCxEN_DISABLED;

    admod_cfg.cores.core1.adcs = ADCORE_ADCS_DEFAULT;
    admod_cfg.cores.core1.eisel = ADCORE_EISEL_8TAD;
    admod_cfg.cores.core1.res = ADCORE_RES_12BIT;
    admod_cfg.cores.core1.samc = ADCORE_SAMC_0002;
    admod_cfg.cores.core1.samc_en = ADCON4_SAMCxEN_DISABLED;
    
    // Initialize ADC module base registers
    fres &= smpsHSADC_Module_Initialize(admod_cfg);  // Write ADC module configuration to registers

    return(fres);
}

/*!c4swbb_adc_inputs_initialize()
 * *****************************************************************************************************
 * Summary:
 * Initializes the analog inputs for the four required input signals
 *
 * Parameters: 
 *  volatile C4SWBB_PWRCTRL_t* pInstance
 *
 * Description:
 * The 4-switch buck boost converter power controller supports up to four signals while running: 
 * output voltage, output current, input voltage and temperature. The main control loop is based on 
 * output voltage and output current. Input voltage is incorporated to optimize soft-start and gain,
 * temperature is used for power balancing and protection. All four signals are triggered by the 
 * same PWM source and sampled at different ADC inputs. 
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_adc_inputs_initialize(volatile C4SWBB_PWRCTRL_t* pInstance) {
    
    volatile uint16_t fres = 1;
    volatile HSADC_ADCANCFG_t adin_cfg;

    // -------------------------
    // Reset/Load defaults from 'pconfig' header file and override these standards with 
    // the user settings specified in pInstance.
    
    // Initialize ADC input with default values
    adin_cfg.config.early_interrupt_enable = ADEIE_ANx_DISABLED; // Always disable early interrupts
    adin_cfg.config.interrupt_enable = ADIE_ANx_DISABLED; // Always disable interrupt generation
    adin_cfg.config.trigger_mode = ADLVLTRG_ANx_EDGE; // Always set trigger to EDGE TRIGGER mode
    adin_cfg.config.trigger_source = ADTRIGx_TRGSRC_NONE; // Always clear interrupt source
    
    adin_cfg.config.data_mode = ANx_DATA_UNSIGNED; // Always use unsigned numbers
    adin_cfg.config.input_mode = ANx_SINGLE_ENDED; // Always use single ended ADC channels

    // -------------------------
    // Extract/Load VOUT user settings from controller object
    if (pInstance->feedback.ad_vout.enable)
    {
        adin_cfg.ad_input = pInstance->feedback.ad_vout.adin_no;    // Load analog input number from user object
        adin_cfg.config.data_mode = pInstance->feedback.ad_vout.signed_data; // Signed or unsigned ADC conversion result
        adin_cfg.config.input_mode = pInstance->feedback.ad_vout.differential_input; // Single-ended or differential input
        adin_cfg.config.core_index = pInstance->feedback.ad_vout.adc_core; // Capture ADC core connected to this analog input
        
        // Load analog input core assignment
        if (pInstance->feedback.ad_vout.adc_core != (ADC_CORE_COUNT-1)) {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_DEDICATED; // Input is connected to dedicated ADC core
        }
        else {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_SHARED; // Input is connected to shared ADC core
        }

        // Set interrupt configuration
        adin_cfg.config.trigger_source = (volatile uint16_t)(pInstance->feedback.ad_vout.trigger_source);
        adin_cfg.config.early_interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_vout.early_interrupt_enable);
        adin_cfg.config.interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_vout.interrupt_enable);

        // Set output voltage ADC input configuration
        fres &= smpsHSADC_ADInput_Initialize(adin_cfg); 

    }
        
    // -------------------------
    // Extract/Load IOUT user settings from controller object
    if (pInstance->feedback.ad_iout.enable)
    {
        adin_cfg.ad_input = pInstance->feedback.ad_iout.adin_no;    // Load analog input number from user object
        adin_cfg.config.data_mode = pInstance->feedback.ad_iout.signed_data; // Signed or unsigned ADC conversion result
        adin_cfg.config.input_mode = pInstance->feedback.ad_iout.differential_input; // Single-ended or differential input
        adin_cfg.config.core_index = pInstance->feedback.ad_iout.adc_core; // Capture ADC core connected to this analog input

        // Load analog input core assignment
        if (pInstance->feedback.ad_iout.adc_core != (ADC_CORE_COUNT-1)) {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_DEDICATED; // Input is connected to dedicated ADC core
        }
        else {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_SHARED; // Input is connected to shared ADC core
        }

        // Set interrupt configuration
        adin_cfg.config.trigger_source = (volatile uint16_t)(pInstance->feedback.ad_iout.trigger_source);
        adin_cfg.config.early_interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_iout.early_interrupt_enable);
        adin_cfg.config.interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_iout.interrupt_enable);

        // Set output current ADC input configuration
        fres &= smpsHSADC_ADInput_Initialize(adin_cfg); 
    
    }
    
    // -------------------------
    // Extract/Load VIN user settings from controller object
    if (pInstance->feedback.ad_vin.enable)
    {
        adin_cfg.ad_input = pInstance->feedback.ad_vin.adin_no;    // Load analog input number from user object
        adin_cfg.config.data_mode = pInstance->feedback.ad_vin.signed_data; // Signed or unsigned ADC conversion result
        adin_cfg.config.input_mode = pInstance->feedback.ad_vin.differential_input; // Single-ended or differential input
        adin_cfg.config.core_index = pInstance->feedback.ad_vin.adc_core; // Capture ADC core connected to this analog input

        // Load analog input core assignment
        if (pInstance->feedback.ad_vin.adc_core != (ADC_CORE_COUNT-1)) {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_DEDICATED; // Input is connected to dedicated ADC core
        }
        else {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_SHARED; // Input is connected to shared ADC core
        }

        // Set interrupt configuration
        adin_cfg.config.trigger_source = (volatile uint16_t)(pInstance->feedback.ad_vin.trigger_source);
        adin_cfg.config.early_interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_vin.early_interrupt_enable);
        adin_cfg.config.interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_vin.interrupt_enable);

        // Set output voltage ADC input configuration
        fres &= smpsHSADC_ADInput_Initialize(adin_cfg); 
  
    }
    
    // -------------------------
    // Extract/Load TEMP user settings from controller object
    if (pInstance->feedback.ad_temp.enable)
    {
        adin_cfg.ad_input = pInstance->feedback.ad_temp.adin_no;    // Load analog input number from user object
        adin_cfg.config.data_mode = pInstance->feedback.ad_temp.signed_data; // Signed or unsigned ADC conversion result
        adin_cfg.config.input_mode = pInstance->feedback.ad_temp.differential_input; // Single-ended or differential input
        adin_cfg.config.core_index = pInstance->feedback.ad_temp.adc_core; // Capture ADC core connected to this analog input

        // Load analog input core assignment
        if (pInstance->feedback.ad_temp.adc_core != (ADC_CORE_COUNT-1)) {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_DEDICATED; // Input is connected to dedicated ADC core
        }
        else {
            adin_cfg.config.core_assigmnment = ANx_CORE_ASSIGNMENT_SHARED; // Input is connected to shared ADC core
        }

        // Set interrupt configuration
        adin_cfg.config.trigger_source = (volatile uint16_t)(pInstance->feedback.ad_temp.trigger_source);
        adin_cfg.config.early_interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_temp.early_interrupt_enable);
        adin_cfg.config.interrupt_enable = (volatile uint16_t)(pInstance->feedback.ad_temp.interrupt_enable);

        // Set temperature ADC input configuration
        fres &= smpsHSADC_ADInput_Initialize(adin_cfg); 

    }
    
    
    // Return Success/Failure
    return(fres);
}

/*!c4swbb_adc_enable()
 * *****************************************************************************************************
 * Summary:
 * Enables the ADC module, starts the ADC cores analog inputs for the four required input signals
 *
 * Parameters: 
 *  (none)
 *
 * Description:
 * This function enables the ADC module, powers-up and enables the ADC cores used and waits 
 * until all functions are acknowledged by the respective READY bits.
 * 
 * *****************************************************************************************************/

volatile uint16_t c4swbb_adc_enable(void) {
    
    volatile uint16_t fres = 1;

    fres &= smpsHSADC_Module_Enable();
    fres &= smpsHSADC_Cores_CheckReady();
    
    return(fres);
}

// EOF

