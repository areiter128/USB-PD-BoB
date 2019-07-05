#ifndef _BUCK_CASC_COEFF_DEFINES_H 
#define _BUCK_CASC_COEFF_DEFINES_H 

/* Compensator Coefficient Defines */
// 2P2Z Filter Implementation 
// Kuc                2
// Pole @ origin      12000Hz
// 1st Zero           1500Hz
// 2nd Pole           50000Hz

// Switching Frequency    500000Hz
// Sampling Frequency     250000Hz

/*-----   K1(z)  -----  */ 
#define BUCK_CASC_COEFF_B10 32767
#define BUCK_CASC_COEFF_B11 32767
#define BUCK_CASC_COEFF_A11 7479

/*-----   K2(z)  -----  */ 
#define BUCK_CASC_COEFF_B20 32767
#define BUCK_CASC_COEFF_B21 -31555
#define BUCK_CASC_COEFF_A21 32767

/*----- K3(z) Bypass for 2P2Z ----- */
#define BUCK_CASC_COEFF_B30 32767
#define BUCK_CASC_COEFF_B31 0
#define BUCK_CASC_COEFF_A31 0

/* Scaling Coefficients */
#define BUCK_CASC_POSTSHIFT -3
#define BUCK_CASC_POSTSCALER 25764
#define BUCK_CASC_PRESHIFT 0

/* Compensator Clamp Limits */
#define BUCK_CASC_MIN_CLAMP 0
#define BUCK_CASC_MAX_CLAMP 2500

#endif
