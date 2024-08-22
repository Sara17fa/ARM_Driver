/*
 * SysTick.h
 *
 *  Created on: Jul 26, 2024
 *      Author: Sara Fayed
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"
#define SYSTICK_PRIORITY_MASK  0x1FFFFFFF
#define SYSTICK_INTERRUPT_PRIORITY  3
#define SYSTICK_PRIORITY_BITS_POS   29


void SysTick_Init(uint16 a_TimeInMilliSeconds);
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);
void SysTick_Handler(void);
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));
void SysTick_Stop(void);
void SysTick_Start(void);
void SysTick_DeInit(void);





#endif /* SYSTICK_H_ */
