/*!task_FaultHandler.c
 * ****************************************************************************
 * File:   task_FaultHandler.c
 * Author: M91406
 *
 * Description:
 * This source file provides multiple functions to set up and monitor user-
 * defined fault objects as well as routines to handle specific fault cases.
 * 
 * History:
 * Created on June 22, 2018, 01:14 PM
 ******************************************************************************/

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _APPLLICAITON_LAYER_FAULT_HANDLER_H_
#define	_APPLLICAITON_LAYER_FAULT_HANDLER_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "_root/config/globals.h"


/*!FAULT_OBJECT_STATUS_t
 * ***********************************************************************************************
 * Description:
 * FAULT_OBJECT_STATUS_t specifies flags determining the system level on which a fault occurred.
 * The most significant bit (bit 15) determines, if a fault check is executed or skipped and can 
 * be set by software routines.
 * The following structures allow bit- as well as word-wise read/write operations of the fault status 
 * information.
 * ***********************************************************************************************/

typedef enum {
    
    FLTCHK_DISABLED = 0b0000000000000000, // Fault Hander status OFF flag bit-mask
    FLTCHK_ENABLED = 0b1000000000000000, // Fault Hander status ON flag bit-mask

    FAULT_NONE = 0b0000000000000000, // Fault bit indicating NO FAULT 
    FAULT_HW  = 0b0000000000000001, // Fault bit indicating a board level hardware failure 
    FAULT_SW  = 0b0000000000000010, // Fault bit indicating a software failure
    FAULT_SI  = 0b0000000000000100, // Fault bit indicating a silicon level hardware failure
    FAULT_SYS = 0b0000000000001000  // Fault bit indicating a system-level/-parameter failure

} __attribute__((packed))FAULT_OBJECT_STATUS_e;

typedef struct {
	volatile unsigned fltlvlhw  :1;	// Bit #0:  hardware/board level flag bit
	volatile unsigned fltlvlsw  :1;	// Bit #1:  firmware/software level flag bit
	volatile unsigned fltlvlsi  :1;	// Bit #2:  silicon/chip level flag bit
	volatile unsigned fltlvlsys :1;	// Bit #3:  system parameter level Flag bit
	volatile unsigned :1;	// Bit #4:  Reserved
	volatile unsigned :1;	// Bit #5:  Reserved
	volatile unsigned :1;	// Bit #6:  Reserved
	volatile unsigned :1;	// Bit #7:  Reserved
	volatile unsigned :1;	// Bit #8:  Reserved
	volatile unsigned :1;	// Bit #9:  Reserved
	volatile unsigned :1;	// Bit #10: Reserved
	volatile unsigned :1;	// Bit #11: Reserved
	volatile unsigned :1;	// Bit #12: Reserved
	volatile unsigned fltactive :1; // Bit #14: Flag bit indicating temporary fault condition is present
	volatile unsigned fltstat   :1;	// Bit #13: Flag bit indicating that a fault has been tripped (latched until gone)
	volatile unsigned fltchken  :1;	// Bit #15: Fault check enable/disable flag bit
}__attribute__((packed))FAULT_OBJECT_STATUS_BIT_FIELD_t;

typedef union 
{
	volatile uint16_t status;
	volatile FAULT_OBJECT_STATUS_BIT_FIELD_t flags;
}FAULT_OBJECT_STATUS_t;

/*!FAULT_OBJECT_CLASS_t
 * ***********************************************************************************************
 * Description:
 * FAULT_OBJECT_CLASS_t specifies flags determining the fault class level (importance) of a 
 * fault object. This setting will be used by the FAULT_HANDLER to take pre-defined actions 
 * when the fault object related fault condition is detected.
 * These fault class levels will trigger different actions and responses:
 * 
 *     - FLT_CLASS_NONE: 
 *       no action will be taken by the fault handler. The fault condition will be continued 
 *       to be monitored and reset if adequate. Tasks depending on this condition need to poll 
 *       on the related flag bit and take their own action.
 * 
 *     - FLT_CLASS_NOTIFY
 *       The GLOBAL_FAULT_FLAG_BIT will be set but no further action will be taken. 
 * 
 *     - FLT_CLASS_WARNING
 *       The GLOBAL_FLAG_BIT will be set as well as the GLOBAL_WARNING_FLAG_BIT but no further action 
 *       will be taken. 
 * 
 *     - FLT_CLASS_CRITICAL
 *       The GLOBAL_FLAG_BIT as well as the GLOBAL_WARNING_FLAG_BIT will be set.
 *       Critical faults will trigger the FAULT_OP_MODE where the application is automatically shut
 *       down and the main scheduler is switched over into "Fault Condition Monitoring Standby Mode". 
 *       
 *     - FLT_CLASS_CATASTROPHIC
 *       The GLOBAL_FLAG_BIT as well as the GLOBAL_WARNING_FLAG_BIT will be set.
 *       Catastrophic faults will trigger an immediate restart by setting the [run_mail_loop] flag
 *       to zero. Thus the main scheduler will complete the most recent task execution, shut down
 *       the application in a deterministic way and reset the CPU to cause warm system restart.
 * 
 *     - FLT_CLASS_USER_ACTION
 *       The GLOBAL_FLAG_BIT as well as the GLOBAL_WARNING_FLAG_BIT will be set depending on the
 *       default class flag bit specification of the FAULT_DEFAULT_CLASS_BIT_FIELD_t. 
 * 
 * Please note:
 * It's assumed that the GLOBAL_FAULT_FLAG_BIT and GLOBAL_WARNING_FLAG_BIT will also be included in 
 * communication protocols and thus also becomes visible to external systems.
 * Internally this implementation allows multiple instances of the firmware to respond to the defined 
 * condition individually.
 * 
 * A user defined level is 
 * ***********************************************************************************************/

typedef enum {
    FLT_CLASS_NONE         = 0b0000000000000000,    // no fault classification =< user handling required
    FLT_CLASS_NOTIFY       = 0b0000000000000001,    // uncritical fault condition has been detected (notice only)
    FLT_CLASS_WARNING      = 0b0000000000000010,    // warning level (approaching critical level)
    FLT_CLASS_CRITICAL     = 0b0000000000000100,    // critical level 
    FLT_CLASS_CATASTROPHIC = 0b0000000000001000,    // catastrophic level 
    FLT_CLASS_USER_ACTION  = 0b0000000100000000     // user defined level 
} FAULT_OBJECT_CLASS_e;


typedef struct {
	volatile unsigned notify       :1;	// Bit #0:  flag bit indicating a simple, uncritical notice
	volatile unsigned warning      :1;	// Bit #1:  flag bit indicating a condition approaching critical level
	volatile unsigned critical     :1;	// Bit #2:  flag bit indicating a condition has reached critical level
	volatile unsigned catastrophic :1;	// Bit #3:  flag bit indicating a catastrophic failure has occurred
	volatile unsigned :1;	// Bit #4:  Reserved
	volatile unsigned :1;	// Bit #5:  Reserved
	volatile unsigned :1;	// Bit #6:  Reserved
	volatile unsigned :1;	// Bit #7:  Reserved
	volatile unsigned user_class   :1;	// Bit #8:  flag bit indicating a user defined failure has occurred
	volatile unsigned :1;	// Bit #9:  Reserved
	volatile unsigned :1;	// Bit #10: Reserved
	volatile unsigned :1;	// Bit #11: Reserved
	volatile unsigned :1;	// Bit #12: Reserved
	volatile unsigned :1;	// Bit #13: Reserved
	volatile unsigned :1;	// Bit #14: Reserved
	volatile unsigned none         :1;  // Bit #15: flag bit indicating that no failure has occurred
}__attribute__((packed))FAULT_OBJECT_CLASS_BIT_FIELD_t;

typedef union 
{
	volatile uint16_t class; // buffer for 16-bit word read/write operations
	volatile FAULT_OBJECT_CLASS_BIT_FIELD_t flags; // data structure for single bit addressing operations
}FAULT_OBJECT_CLASS_t;

/*!FAULT_CONDITION_SETTINGS_t
 * ***********************************************************************************************
 * Description:
 * FLTOBJ_FAULT_CONDITION_SETTINGS_t holds set point values of fault trip and fault release 
 * thresholds, the periodic counter counting successive fault conditions and the maximum counter
 * threshold at which a fault event is triggered resp. the periodic counter counting successive 
 * OK conditions and the maximum counter threshold at which a fault condition is reset.
 * ***********************************************************************************************/

#define FAULT_OBJECT_BIT_MASK_DEFAULT   0xFFFF

typedef enum
{
    FAULT_LEVEL_GREATER_THAN = 0b0000000000000000, // Flag to perform "greater than" comparison
    FAULT_LEVEL_LESS_THAN    = 0b1111111111111111, // Flag to perform "less than" comparison
    FAULT_LEVEL_EQUAL        = 0b0000000011111111, // Flag to perform "is equal" comparison
    FAULT_LEVEL_NOT_EQUAL    = 0b1111111100000000  // Flag to perform "is not equal than" comparison
}FAULT_OBJECT_CONDITION_LEVEL_e;
    
typedef struct
{
    volatile uint16_t counter; // Fault hit counter
    volatile FAULT_OBJECT_CONDITION_LEVEL_e fault_ratio; // flag to identify if a trip point is greater or less than the value it is compared with
    volatile uint16_t reset_level; // Input signal fault reset level/fault reset point
    volatile uint16_t reset_cnt_threshold; // Fault counter threshold resetting fault exception
    volatile uint16_t trip_level; // Input signal fault trip level/fault trip point
    volatile uint16_t trip_cnt_threshold; // Fault counter threshold triggering fault exception
}__attribute__((packed))FAULT_CONDITION_SETTINGS_t;


/*!FAULT_OBJECT_t
 * ***********************************************************************************************
 * Description:
 * This generic fault object FAULT_OBJECT_t provides a 16-bit address pointer to a variable 
 * or SFR, which is monitored. The fault check response can be set by a TRIP and RELEASE point 
 * threshold as well as a counter based filter, comparing recent successive threshold violations 
 * against a given maximum of tolerable violations before a fault response is triggered.
 * ***********************************************************************************************/

typedef struct
{
    volatile FAULT_OBJECT_STATUS_t status; // status bit field
    volatile FAULT_OBJECT_CLASS_t classes; // fault class bit field
    volatile FAULT_CONDITION_SETTINGS_t criteria; // Fault check settings of the  fault object
    volatile uint32_t error_code; // error code helping to identify source module, system level and importance
    volatile uint16_t id; // identifier of this fault object
    volatile uint16_t* object; // pointer to an object (e.g. variable or SFR) to be monitored
    volatile uint16_t object_bit_mask; // bit mask filter to monitor specific bits within OBJECT
    volatile uint16_t (*user_fault_action)(void); // pointer to a user function called when a defined fault condition is detected
    volatile uint16_t (*user_fault_reset)(void); // pointer to a user function called when a defined fault condition is detected
}__attribute__((packed))FAULT_OBJECT_t;

/*!fault_object_list[]
 * ***********************************************************************************************
 * Description:
 * The fault_object_list[] array is a list of all fault objects defined for this project. It
 * is a list of pointers to DEFAULT_FAULT_OBJECT_t data structures defining fault settings,
 * status information, fault classes and user fault actions.
 * ***********************************************************************************************/

extern FAULT_OBJECT_t *fault_object_list[];
extern uint16_t fltobj_list_size;


/*!CPU Reset Classes
 * ***********************************************************************************************
 * Description:
 * CPU Reset Classes CPU_RESET_CLASS_xxx provides a set of bit filter masks for the 
 * RESET CONFIGURATION REGISTER (RCON),
 * which classify more or less critical root causes of the previous CPU reset. 
 * 
 *     - FLT_CPU_RESET_CLASS_CRITICAL:
 *       This flag is set when a critical reset root cause was detected, such as
 *       firmware initiated FLT_CLASS_CATASTROPHIC events
 * 
 *     - FLT_CPU_RESET_CLASS_WARNING:
 *       This flag is set if a CPU reset was detected which indicates an "involuntary"
 *       reset such as brown-out or external MCLR reset 
 *       
 *     - FLT_CPU_RESET_CLASS_NORMAL:
 *       this flag will be set when a normal CPU startup was detected
 * 
 * ***********************************************************************************************/

#define FLT_CPU_RESET_CLASS_CRITICAL   0b1100001000010000
#define FLT_CPU_RESET_CLASS_WARNING    0b0000000011000000
#define FLT_CPU_RESET_CLASS_NORMAL     0b0000000000001111


/*!Fault Handler Prototypes
 * ***********************************************************************************************
 * Description:
 * The following function prototypes are publicly accessible.
 * ***********************************************************************************************/
extern inline uint16_t CheckCPUResetRootCause(void);

extern inline uint16_t exec_FaultCheckAll(void);
extern inline uint16_t exec_FaultCheckSequential(void);

#endif	/* _APPLLICAITON_LAYER_FAULT_HANDLER_H_ */

