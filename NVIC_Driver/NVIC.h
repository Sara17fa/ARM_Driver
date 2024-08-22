/*
 * NVIC.h
 *
 *  Created on: Jul 29, 2024
 *      Author: Sara Fayed
 */

#ifndef NVIC_H_
#define NVIC_H_
/* *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                           Preprocessor Definitions                          *
 *******************************************************************************/
#define MEM_MANAGE_FAULT_PRIORITY_BITS_POS        5
#define MEM_MANAGE_FAULT_PRIORITY                 1
#define MEM_MANAGE_FAULT_PRIORITY_MASK        0xFFFFFF1F


#define MEM_FAULT_PRIORITY_MASK              0x000000E0
#define MEM_FAULT_PRIORITY_BITS_POS          5

#define BUS_FAULT_PRIORITY_MASK              0x0000E000
#define BUS_FAULT_PRIORITY_BITS_POS          13

#define USAGE_FAULT_PRIORITY_MASK            0x00E00000
#define USAGE_FAULT_PRIORITY_BITS_POS        21

#define SVC_PRIORITY_MASK                    0xE0000000
#define SVC_PRIORITY_BITS_POS                29

#define DEBUG_MONITOR_PRIORITY_MASK          0x000000E0
#define DEBUG_MONITOR_PRIORITY_BITS_POS      5

#define PENDSV_PRIORITY_MASK                 0x00E00000
#define PENDSV_PRIORITY_BITS_POS             21

#define SYSTICK_PRIORITY_MASK                0xE0000000
#define SYSTICK_PRIORITY_BITS_POS            29

#define MEM_FAULT_ENABLE_MASK                0x00010000
#define BUS_FAULT_ENABLE_MASK                0x00020000
#define USAGE_FAULT_ENABLE_MASK              0x00040000

/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmable Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm(" CPSIE I ")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmable Systems Exceptions and Faults by setting the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm(" CPSID I ")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm(" CPSIE F ")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm(" CPSID F ")

#define Trigger_SVC_Exception() __asm(" SVC #0 ")

/*******************************************************************************
 *                           Data Types Declarations                           *
 *******************************************************************************/
typedef uint8 NVIC_IRQType;

typedef uint8 NVIC_IRQPriorityType;

typedef enum
{
    EXCEPTION_RESET_TYPE,
    EXCEPTION_NMI_TYPE,
    EXCEPTION_HARD_FAULT_TYPE,
    EXCEPTION_MEM_FAULT_TYPE,
    EXCEPTION_BUS_FAULT_TYPE,
    EXCEPTION_USAGE_FAULT_TYPE,
    EXCEPTION_SVC_TYPE,
    EXCEPTION_DEBUG_MONITOR_TYPE,
    EXCEPTION_PEND_SV_TYPE,
    EXCEPTION_SYSTICK_TYPE
}NVIC_ExceptionType;

typedef uint8 NVIC_ExceptionPriorityType;

/************************************************************************************
 *                                 End of File                                      *
 ************************************************************************************/
#define INTA_PRIORITY_MASK       0xFFFFFF1F
#define INTA_PRIORITY_BITS_POS     5

#define INTB_PRIORITY_MASK       0xFFFF1FFF
#define INTB_PRIORITY_BITS_POS     13

#define INTC_PRIORITY_MASK       0xFF1FFFFF
#define INTC_PRIORITY_BITS_POS     21

#define INTD_PRIORITY_MASK       0x1FFFFFFF
#define INTD_PRIORITY_BITS_POS     29

#define pri_BASE 0xE000E400           /*BASE adress for PRIORITY REG*/



void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num) ;
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num) ;
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority) ;

void NVIC_EnableException(NVIC_ExceptionType Exception_Num);
void NVIC_DisableException(NVIC_ExceptionType Exception_Num);
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority) ;


#endif /* NVIC_H_ */
