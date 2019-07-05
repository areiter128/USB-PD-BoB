
/**********************************************************************
Copyright(c) 2018 Microchip Technology Inc. and its subsidiaries.
Subject to your compliance with these terms, you may use Microchip
software and any derivatives exclusively with Microchip products. It
is your responsibility to comply with third party license terms
applicable to your use of third-party software (including open source
software) that may accompany Microchip software.
THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
FOR A PARTICULAR PURPOSE.
IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL,
PUNITIVE, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF
ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE
FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL
LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO
MICROCHIP FOR THIS SOFTWARE.
**********************************************************************/

#ifndef FAULT_SIM_H
#define	FAULT_SIM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FAULT_SIM 0

#if FAULT_SIM
    #define FaultSimRun()    _FaultSimRun()
    #define FaultSim_BCK_C() _FaultSim_BCK_C()
    #define FaultSim_BCK_V() _FaultSim_BCK_V()
    #define FaultSim_BST_C() _FaultSim_BST_C()
    #define FaultSim_BST_V() _FaultSim_BST_V()
#else  // FAULT_SIM
    #define FaultSimRun()
    #define FaultSim_BCK_C()
    #define FaultSim_BCK_V()
    #define FaultSim_BST_C()
    #define FaultSim_BST_V()
#endif // FAULT_SIM

extern void _FaultSimRun(void);
extern void _FaultSim_BCK_C(void);
extern void _FaultSim_BCK_V(void);
extern void _FaultSim_BST_C(void);
extern void _FaultSim_BST_V(void);

#ifdef	__cplusplus
}
#endif

#endif	/* FAULT_SIM_H */

