/*
 * systick_prog.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Sara Fayed
 */
#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"



static volatile void(*g_CallBackPtr)(void)=NULL_PTR;


/*********************************************************************
 * Service Name: SysTick_Init
 * Return value: None
 *  Sync/Async: Synchronous
 *  Description:1- Disable the SysTick Timer by Clear the ENABLE Bit
 *              2-Set the Reload value with 15999999 to count 0.2 Second
 *              3-Clear the Current Register value
 *              Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Enable SysTick Interrupt (INTEN = 1)
     * Choose the clock source to be System Clock (CLK_SRC = 1)
     * Assign priority level 3 to the SysTick Interrupt
 *
**********************************************************************/
volatile uint64 count=0;
void SysTick_Init(uint16 a_TimeInMilliSeconds){

        SYSTICK_CTRL_REG  = 0;
        SYSTICK_RELOAD_REG =15999999;
        SYSTICK_CURRENT_REG =0;
        SYSTICK_CTRL_REG   |= 0x07;

        NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (SYSTICK_INTERRUPT_PRIORITY << SYSTICK_PRIORITY_BITS_POS);
        while(count++<( a_TimeInMilliSeconds/1000)){

            while(!(SYSTICK_CTRL_REG&(1<<16)));
        }
        count=0;

}

/*********************************************************************
 * Service Name: SysTick_Init
 * Return value: None
 *  Sync/Async: Synchronous
 *  Description:1- Disable the SysTick Timer by Clear the ENABLE Bit
 *              2-Set the Reload value with 15999999 to count 0.2 Second
 *              3-Clear the Current Register value
 *              Configure the SysTick Control Register
     * Enable the SysTick Timer (ENABLE = 1)
     * Disable SysTick Interrupt (INTEN = 0)  To work by Polling
     * Choose the clock source to be System Clock (CLK_SRC = 1)
 *
**********************************************************************/

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){

    SYSTICK_CTRL_REG  = 0;
    SYSTICK_RELOAD_REG =((a_TimeInMilliSeconds*15999999)/1000);
    SYSTICK_CURRENT_REG =0;
    SYSTICK_CTRL_REG   |= 0x05;
    while(!(SYSTICK_CTRL_REG&(1<<16)));


}

/*
 * check if address stored in global pointer to function
 * if YES: do call back Notification
 * else :DO no thing
 */

void SysTick_Handler(void){

    if(g_CallBackPtr != NULL_PTR){

        (*g_CallBackPtr)();
    }



}

/***********************************************
 * Store address of function in Global Variable
 * TYPE:pointer to function
 **************************************************/

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){

    g_CallBackPtr=Ptr2Func;
}

/**************************************************************
 *
 * clear ENABLE to stop
 **************************************************************/

void SysTick_Stop(void){

    SYSTICK_CTRL_REG &=~(1<<0);
}

/**********************************************
 * set ENABLE to start
************************************************/

void SysTick_Start(void){

    SYSTICK_CTRL_REG |=(1<<0);
}

/***************************************************
  * Disable the SysTick Timer (ENABLE = 0)
  * Disable SysTick Interrupt (INTEN = 0)
  * Choose the clock source to be System Clock (CLK_SRC = 0)
****************************************************/

void SysTick_DeInit(void){

    SYSTICK_CTRL_REG   &= 0x00;
}




