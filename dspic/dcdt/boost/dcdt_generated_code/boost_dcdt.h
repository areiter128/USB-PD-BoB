/**
  Summary:
  This header file was created using Microchip Digital Compensator Design Tool (DCDT)
  and includes system summary and digital compensator coefficients. This file
  should be included in the MPLAB X project directory.

  File Name:     boost_dcdt.h
  Project Name:  boost
  Date:          5/29/2019
  Time:          17:34.48

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
#ifndef _BOOST_DCDT_DEFINES_H
#define _BOOST_DCDT_DEFINES_H

/**
  Compensator Type:  2P2Z
      Entry                Value  
    ---------            ---------
  Pole 0                 2.5000e+04 Hz
  Pole 2                 2.5000e+05 Hz
  Zero 1                 7.0000e+02 Hz
  Gain(Kdc)              1.000
  Warp                   false
  PWM Frequency          5.0000e+05
  PWM Sampling Ratio     2
  Sampling Frequency     2.5000e+05
  PWM Max Resolution     2.0000e-09
  Computational Delay    5.0000e-07
  Control Output Min.    0
  Control Output Max.    3700
  Kuc Gain               8.0000e+00
  Use Kuc Gain           false


  PWM Calculations
      Name                Value  
    ---------           ---------
  Bits of Resolution    10.966
  Gain                  5.003e-04


  s-domain transfer function

               Wp0   Wp2(Wz1 + s)
  H(s) = Kdc X --- X ------------
                s    Wz1(Wp2 + s)

                  1.57e+05   1.57e+06(4.40e+03 + s)
  H(s) = 1.000 X -------- X ----------------------
                     s       4.40e+03(1.57e+06 + s)



  Digital Compensator Coefficients

  Name    Value      Normalized    Q15      Hex
  ----    -----      ----------    ---      ---
  a1      0.483      0.018         578      0x0242
  a2      0.517      0.019         619      0x026B
  b0      27.329     1.000         32764    0x7FFC
  b1      0.477      0.017         571      0x023B
  b2      -26.853    -0.982        -32193   0x823F


  z-domain transfer function

         u(z)  B0 + B1z^(-1) + B2z^(-2)
  H(z) = --- = ------------------------
         e(z)  A0 - A1z^(-1) - A2z^(-2)

          (27.329) + (0.477)z^(-1) + (-26.853)z^(-2)
  H(z) = ---------------------------------------------
          1 - (0.483)z^(-1) - (0.517)z^(-2)

**/

//#define BOOST_CASCADED        // Not supported

#if defined (BOOST_CASCADED)

#else

// Compensator Coefficient Defines
#define BOOST_COMP_2P2Z_COEFF_A1      0x0242
#define BOOST_COMP_2P2Z_COEFF_A2      0x026B
#define BOOST_COMP_2P2Z_COEFF_B0      0x7FFC
#define BOOST_COMP_2P2Z_COEFF_B1      0x023B
#define BOOST_COMP_2P2Z_COEFF_B2      0x823F
#define BOOST_POSTSCALER    0x6D53
#define BOOST_POSTSHIFT     0xFFFB

// Compensator Clamp Limits
#define BOOST_MIN_CLAMP    0x0000
#define BOOST_MAX_CLAMP    0x0E74

#endif

#endif
