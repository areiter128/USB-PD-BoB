/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     buck_dcdt.h
  Project Name:  buck
  Date:          5/30/2019
  Time:          16:45.42

  Software License Agreement

  Copyright © 2019 Microchip Technology Inc.  All rights reserved.
  Microchip licenses to you the right to use, modify, copy and distribute
  Software only when embedded on a Microchip microcontroller or digital
  signal controller, which is integrated into your product or third party
  product (pursuant to the sublicense terms in the accompanying license
  agreement).

  You should refer to the license agreement accompanying this Software
  for additional information regarding your rights and obligations.

  SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
  OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
  PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
  OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
  BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
  DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
  INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
  COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
  CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
  OR OTHER SIMILAR COSTS.
 **/
#ifndef _BUCK_DCDT_DEFINES_H
#define _BUCK_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 1.2000e+04 Hz
  Pole 2                 5.0000e+04 Hz
  Zero 1                 1.5000e+03 Hz
  Gain(Kdc)              2.000
  Warp                   false
  PWM Frequency          5.0000e+05
  PWM Sampling Ratio     2
  Sampling Frequency     2.5000e+05
  PWM Max Resolution     2.0000e-09
  Computational Delay    5.0000e-07
  Gate Drive Delay       1.5000e-07
  Control Output Min.    0
  Control Output Max.    1900


  PWM Calculations
      Name                Value  
    ---------           ---------
  Bits of Resolution    10.966
  Gain                  5.003e-04


  s-domain transfer function

               Wp0   Wp2(Wz1 + s)
  H(s) = Kdc X --- X ------------
                s    Wz1(Wp2 + s)

                  7.54e+04   3.14e+05(9.42e+03 + s)
  H(s) = 2.000 X -------- X ----------------------
                     s       9.42e+03(3.14e+05 + s)



  Digital Compensator Coefficients

  Name    Value     Normalized    Q15      Hex
  ----    -----     ----------    ---      ---
  a1      1.228     0.195         6397     0x18FD
  a2      -0.228    -0.036        -1188    0xFB5C
  b0      6.290     1.000         32764    0x7FFC
  b1      0.233     0.037         1212     0x04BC
  b2      -6.058    -0.963        -31552   0x84C0


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (6.290) + (0.233)z^(-1) + (-6.058)z^(-2)
  H(z) = ---------------------------------------------
          1 - (1.228)z^(-1) - (-0.228)z^(-2)

**/


// Compensator Coefficient Defines
#define BUCK_COMP_2P2Z_COEFF_A1      0x18FD
#define BUCK_COMP_2P2Z_COEFF_A2      0xFB5C
#define BUCK_COMP_2P2Z_COEFF_B0      0x7FFC
#define BUCK_COMP_2P2Z_COEFF_B1      0x04BC
#define BUCK_COMP_2P2Z_COEFF_B2      0x84C0
#define BUCK_COMP_2P2Z_POSTSCALER    0x64A7
#define BUCK_COMP_2P2Z_POSTSHIFT     0xFFFD
#define BUCK_COMP_2P2Z_PRESHIFT      0x0000


// Compensator Clamp Limits
#define BUCK_COMP_2P2Z_MIN_CLAMP    0x0000
#define BUCK_COMP_2P2Z_MAX_CLAMP    0x076C


#endif
