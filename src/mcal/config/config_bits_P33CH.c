/*!config_bits_P33CH.c
 * ****************************************************************************
 * File:   config_bits_P33CH.c
 * Author: M91406
 *
 * Description:
 * Configuration bits are setting essential chip features which determine 
 * startup conditions when the device comes out of RESET and cannot be 
 * changed during runtime.
 * 
 * This file defines the fundamental chip configuration for dsPIC33CH512MP506
 * 
 * History:
 * Created on July 24, 2018, 09:32 PM
 ******************************************************************************/

// Configuration bits for dsPIC33CH Dual Core devices
#if defined (__dsPIC33CH512MP506__)

// FS1ICD
/*!S1ISOLAT
 * *****************************************************************************************************
 * Summary:
 * Config bit setting for slave core RUN command
 * 
 * Description:
 * The config bit S1ISOLAT allows to run the slave core even if the RUN bit is not set. Thus the 
 * slave core starts to execute the slave program independently from the mast core firmware. This 
 * feature is essentially requires to allow debugging of the slave core firmware.
 * 
 * To debug the slave core firmware the following steps have to be done to enable slave core 
 * debugging:
 * 
 * 1) set #pragma config S1ISOLAT = ON // enables independent slave core code execution
 * 2) open the master core firmware project properties, go to "Slaves" and enable the option
 *    check box "Debug" in the lower, right window 
 * 3) make and program the master core firmware first
 * 4) start slave core debug session
 * 
 * Note:
 * please undo these two changes before starting a debug session on the master core firmware 
 * or before building the project in RELEASE mode.
 * 
 * *****************************************************************************************************/
#pragma config S1ISOLAT = OFF    // Isolate the Slave core subsystem from the master subsystem during 
                                 // Debug->The slave can operate (in debug mode) even if the SLVEN bit 
                                 // in the MSI is zero.
/* *************************************************************************************************** */

#pragma config S1ICS = PGD2    //ICD Communication Channel Select bits->Communicate on PGC2 and PGD2
#pragma config S1NOBTSWP = OFF    //BOOTSWP Instruction Enable/Disable bit->BOOTSWP instruction is disabled


// FSEC
#pragma config BWRP = OFF    //Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED    //Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF    //Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF    //General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    //General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    //Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    //Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF    //Alternate Interrupt Vector Table bit->Disabled AIVT

// FBSLIM
#pragma config BSLIM = 8191    //Boot Segment Flash Page Address Limit bits->8191

// FOSCSEL
#pragma config FNOSC = FRC    //Oscillator Source Selection->Internal Fast RC (FRC) Oscillator with postscaler
#pragma config IESO = OFF    //Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC
#pragma config POSCMD = NONE    //Primary Oscillator Mode Select bits->Primary Oscillator disabled
#pragma config OSCIOFNC = ON    //OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config FCKSM = CSECMD    //Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config PLLKEN = PLLKEN_ON    //PLLKEN->PLLKEN_ON
#pragma config XTCFG = G3    //XT Config->24-32 MHz crystals
#pragma config XTBST = ENABLE    //XT Boost->Boost the kick-start

// FWDT
#pragma config RWDTPS = PS1048576    //Run Mode Watchdog Timer Post Scaler select bits->1:1048576
#pragma config RCLKSEL = LPRC    //Watchdog Timer Clock Select bits->Always use LPRC
#pragma config WINDIS = OFF    //Watchdog Timer Window Enable bit->Watchdog Timer in Window mode
#pragma config WDTWIN = WIN25    //Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config SWDTPS = PS1048576    //Sleep Mode Watchdog Timer Post Scaler select bits->1:1048576
#pragma config FWDTEN = ON_SW    //Watchdog Timer Enable bit->WDT controlled via SW, use WDTCON.ON bit

// FICD
#pragma config ICS = PGD2    //ICD Communication Channel Select bits->Communicate on PGC2 and PGD2
#pragma config JTAGEN = OFF    //JTAG Enable bit->JTAG is disabled

// FDMTIVTL
#pragma config DMTIVTL = 0    //Dead Man Timer Interval low word->0

// FDMTIVTH
#pragma config DMTIVTH = 0    //Dead Man Timer Interval high word->0

// FDMTCNTL
#pragma config DMTCNTL = 0    //Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->0

// FDMTCNTH
#pragma config DMTCNTH = 0    //Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->0

// FDMT
#pragma config DMTDIS = OFF    //Dead Man Timer Disable bit->Dead Man Timer is Disabled and can be enabled by software

// FDEVOPT
#pragma config ALTI2C1 = OFF    //Alternate I2C1 Pin bit->I2C1 mapped to SDA1/SCL1 pins
#pragma config ALTI2C2 = OFF    //Alternate I2C2 Pin bit->I2C2 mapped to SDA2/SCL2 pins
#pragma config SMBEN = SMBUS    //SM Bus Enable->SMBus input threshold is enabled
#pragma config SPI2PIN = PPS    //SPI2 Pin Select bit->SPI2 uses I/O remap (PPS) pins

// FALTREG
#pragma config CTXT1 = IPL5    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits->Not Assigned
#pragma config CTXT2 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits->Not Assigned
#pragma config CTXT3 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits->Not Assigned
#pragma config CTXT4 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits->Not Assigned

// FCFGPRA0
#pragma config CPRA0 = MSTR    //Pin RA0 Ownership Bits->Master core owns pin.
#pragma config CPRA1 = MSTR    //Pin RA1 Ownership Bits->Master core owns pin.
#pragma config CPRA2 = MSTR    //Pin RA2 Ownership Bits->Master core owns pin.
#pragma config CPRA3 = MSTR    //Pin RA3 Ownership Bits->Master core owns pin.
#pragma config CPRA4 = SLV1    //Pin RA4 Ownership Bits->Slave 1 core owns pin.

// FCFGPRB0
#pragma config CPRB0 = SLV1    //Pin RB0 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRB1 = SLV1    //Pin RB1 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRB2 = MSTR    //Pin RB2 Ownership Bits->Master core owns pin.
#pragma config CPRB3 = MSTR    //Pin RB3 Ownership Bits->Master core owns pin.
#pragma config CPRB4 = MSTR    //Pin RB4 Ownership Bits->Master core owns pin.
#pragma config CPRB5 = MSTR    //Pin RB5 Ownership Bits->Master core owns pin.
#pragma config CPRB6 = MSTR    //Pin RB6 Ownership Bits->Master core owns pin.
#pragma config CPRB7 = MSTR    //Pin RB7 Ownership Bits->Master core owns pin.
#pragma config CPRB8 = MSTR    //Pin RB8 Ownership Bits->Master core owns pin.
#pragma config CPRB9 = MSTR    //Pin RB9 Ownership Bits->Master core owns pin.
#pragma config CPRB10 = MSTR    //Pin RB10 Ownership Bits->Master core owns pin.
#pragma config CPRB11 = MSTR    //Pin RB11 Ownership Bits->Master core owns pin.
#pragma config CPRB12 = MSTR    //Pin RB12 Ownership Bits->Master core owns pin.
#pragma config CPRB13 = MSTR    //Pin RB13 Ownership Bits->Master core owns pin.
#pragma config CPRB14 = MSTR    //Pin RB14 Ownership Bits->Master core owns pin.
#pragma config CPRB15 = MSTR    //Pin RB15 Ownership Bits->Master core owns pin.

// FCFGPRC0
#pragma config CPRC0 = MSTR    //Pin RC0 Ownership Bits->Master core owns pin.
#pragma config CPRC1 = MSTR    //Pin RC1 Ownership Bits->Master core owns pin.
#pragma config CPRC2 = MSTR    //Pin RC2 Ownership Bits->Master core owns pin.
#pragma config CPRC3 = MSTR    //Pin RC3 Ownership Bits->Master core owns pin.
#pragma config CPRC4 = SLV1    //Pin RC4 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC5 = SLV1    //Pin RC5 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC6 = SLV1    //Pin RC6 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC7 = SLV1    //Pin RC7 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC8 = MSTR    //Pin RC8 Ownership Bits->Master core owns pin.
#pragma config CPRC9 = MSTR    //Pin RC9 Ownership Bits->Master core owns pin.
#pragma config CPRC10 = SLV1    //Pin RC10 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC11 = SLV1    //Pin RC11 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC12 = MSTR    //Pin RC12 Ownership Bits->Master core owns pin.
#pragma config CPRC13 = SLV1    //Pin RC13 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRC14 = MSTR    //Pin RC14 Ownership Bits->Master core owns pin.
#pragma config CPRC15 = MSTR    //Pin RC15 Ownership Bits->Master core owns pin.

// FCFGPRD0
#pragma config CPRD0 = MSTR    //Pin RD0 Ownership Bits->Master core owns pin.
#pragma config CPRD1 = MSTR    //Pin RD1 Ownership Bits->Master core owns pin.
#pragma config CPRD2 = MSTR    //Pin RD2 Ownership Bits->Master core owns pin.
#pragma config CPRD3 = SLV1    //Pin RD3 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRD4 = SLV1    //Pin RD4 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRD5 = MSTR    //Pin RD5 Ownership Bits->Master core owns pin.
#pragma config CPRD6 = SLV1    //Pin RD6 Ownership Bits->Master core owns pin.
#pragma config CPRD7 = MSTR    //Pin RD7 Ownership Bits->Master core owns pin.
#pragma config CPRD8 = MSTR    //Pin RD8 Ownership Bits->Master core owns pin.
#pragma config CPRD9 = MSTR    //Pin RD9 Ownership Bits->Master core owns pin.
#pragma config CPRD10 = SLV1    //Pin RD10 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRD11 = MSTR    //Pin RD11 Ownership Bits->Master core owns pin.
#pragma config CPRD12 = MSTR    //Pin RD12 Ownership Bits->Slave 1 core owns pin.
#pragma config CPRD13 = MSTR    //Pin RD13 Ownership Bits->Master core owns pin.
#pragma config CPRD14 = MSTR    //Pin RD14 Ownership Bits->Master core owns pin.
#pragma config CPRD15 = MSTR    //Pin RD15 Ownership Bits->Master core owns pin.

// FCFGPRE0
#pragma config CPRE0 = MSTR    //Pin RE0 Ownership Bits->Master core owns pin.
#pragma config CPRE1 = MSTR    //Pin RE1 Ownership Bits->Master core owns pin.
#pragma config CPRE2 = MSTR    //Pin RE2 Ownership Bits->Master core owns pin.
#pragma config CPRE3 = MSTR    //Pin RE3 Ownership Bits->Master core owns pin.
#pragma config CPRE4 = MSTR    //Pin RE4 Ownership Bits->Master core owns pin.
#pragma config CPRE5 = MSTR    //Pin RE5 Ownership Bits->Master core owns pin.
#pragma config CPRE6 = MSTR    //Pin RE6 Ownership Bits->Master core owns pin.
#pragma config CPRE7 = MSTR    //Pin RE7 Ownership Bits->Master core owns pin.
#pragma config CPRE8 = MSTR    //Pin RE8 Ownership Bits->Master core owns pin.
#pragma config CPRE9 = MSTR    //Pin RE9 Ownership Bits->Master core owns pin.
#pragma config CPRE10 = MSTR    //Pin RE10 Ownership Bits->Master core owns pin.
#pragma config CPRE11 = MSTR    //Pin RE11 Ownership Bits->Master core owns pin.
#pragma config CPRE12 = MSTR    //Pin RE12 Ownership Bits->Master core owns pin.
#pragma config CPRE13 = MSTR    //Pin RE13 Ownership Bits->Master core owns pin.
#pragma config CPRE14 = MSTR    //Pin RE14 Ownership Bits->Master core owns pin.
#pragma config CPRE15 = MSTR    //Pin RE15 Ownership Bits->Master core owns pin.



/* *****************************************************************************************************
 *  SLAVE CORE SETTINGS 
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

// FMBXM
#pragma config MBXM0 = M2S    //Mailbox 0 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM1 = M2S    //Mailbox 1 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM2 = M2S    //Mailbox 2 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM3 = M2S    //Mailbox 3 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM4 = M2S    //Mailbox 4 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM5 = M2S    //Mailbox 5 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM6 = M2S    //Mailbox 6 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM7 = M2S    //Mailbox 7 data direction->Mailbox register configured for Master data write (Master to Slave data transfer)
#pragma config MBXM8 = S2M    //Mailbox 8 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM9 = S2M    //Mailbox 9 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM10 = S2M    //Mailbox 10 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM11 = S2M    //Mailbox 11 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM12 = S2M    //Mailbox 12 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM13 = S2M    //Mailbox 13 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM14 = S2M    //Mailbox 14 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)
#pragma config MBXM15 = S2M    //Mailbox 15 data direction->Mailbox register configured for Master data read (Slave to Master data transfer)

// FMBXHS1
#pragma config MBXHSA = MBX15    //Mailbox handshake protocol block A register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block A
#pragma config MBXHSB = MBX15    //Mailbox handshake protocol block B register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block B
#pragma config MBXHSC = MBX15    //Mailbox handshake protocol block C register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block C
#pragma config MBXHSD = MBX15    //Mailbox handshake protocol block D register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block D

// FMBXHS2
#pragma config MBXHSE = MBX15    //Mailbox handshake protocol block E register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block E
#pragma config MBXHSF = MBX15    //Mailbox handshake protocol block F register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block F
#pragma config MBXHSG = MBX15    //Mailbox handshake protocol block G register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block G
#pragma config MBXHSH = MBX15    //Mailbox handshake protocol block H register assignment->MSIxMBXD15 assigned to mailbox handshake protocol block H

// FMBXHSEN
#pragma config HSAEN = OFF    //Mailbox A data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSBEN = OFF    //Mailbox B data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSCEN = OFF    //Mailbox C data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSDEN = OFF    //Mailbox D data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSEEN = OFF    //Mailbox E data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSFEN = OFF    //Mailbox F data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSGEN = OFF    //Mailbox G data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.
#pragma config HSHEN = OFF    //Mailbox H data flow control protocol block enable->Mailbox data flow control handshake protocol block disabled.

// FS1DEVOPT
#pragma config S1ALTI2C1 = OFF    //Alternate I2C1 Pin bit->I2C1 mapped to SDA1/SCL1 pins
#pragma config S1SPI1PIN = PPS    //S1 SPI1 Pin Select bit->Slave SPI1 uses I/O remap (PPS) pins
#pragma config S1SSRE = ON    //Slave Slave Reset Enable->Slave generated resets will reset the Slave Enable Bit in the MSI module
#pragma config S1MSRE = ON    //Master Slave Reset Enable->The master software oriented RESET events (RESET Op-Code, Watchdog timeout, TRAP reset, illegalInstruction) will also cause the slave subsystem to reset.

// FS1OSCSEL
#pragma config S1FNOSC = FRC    //Oscillator Source Selection->Internal Fast RC (FRC) Oscillator
#pragma config S1IESO = OFF    //Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FS1OSC
#pragma config S1OSCIOFNC = ON    //Slave OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config S1FCKSM = CSECMD    //Clock Switching Mode bits->Clock switching is enabled,Fail-safe Clock Monitor is disabled
#pragma config S1PLLKEN = S1PLLKEN_ON    //S1PLLKEN->S1PLLKEN_ON

// FS1ALTREG
#pragma config S1CTXT1 = IPL5    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits->Not Assigned
#pragma config S1CTXT2 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits->Not Assigned
#pragma config S1CTXT3 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits->Not Assigned
#pragma config S1CTXT4 = OFF    //Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits->Not Assigned

// FS1WDT
#pragma config S1RWDTPS = PS1048576    //Run Mode Watchdog Timer Post Scaler select bits->1:1048576
#pragma config S1RCLKSEL = LPRC    //Watchdog Timer Clock Select bits->Always use LPRC
#pragma config S1WINDIS = ON    //Watchdog Timer Window Enable bit->Watchdog Timer operates in Non-Window mode
#pragma config S1WDTWIN = WIN25    //Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config S1SWDTPS = PS1048576    //Sleep Mode Watchdog Timer Post Scaler select bits->1:1048576
#pragma config S1FWDTEN = ON_SW    //Watchdog Timer Enable bit->WDT controlled via WDTCON.ON bit


#endif  /* Config bits for dsPIC33CH Dual Core Devices */

/**
 End of File
*/