/*
 * NVIC_prog.c
 *
 *  Created on: Jul 29, 2024
 *      Author: Sara Fayed
 */

#include "tm4c123gh6pm_registers.h"

#include "NVIC.h"

/*********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to enable Interrupt request for specific IRQ
**********************************************************************/

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num) {

    if( IRQ_Num<=31){
        NVIC_EN0_REG =(NVIC_EN0_REG & 0x00000000)|(1<<IRQ_Num);

   }

    else if(IRQ_Num>32 && IRQ_Num<64){
        NVIC_EN1_REG =(NVIC_EN1_REG & 0x00000000)|(1<<(IRQ_Num-32));

    /*EN1*/
  }
   else if(IRQ_Num>6 && IRQ_Num<=95){
       NVIC_EN2_REG =(NVIC_EN2_REG & 0x00000000)|(1<<(IRQ_Num-64));

    /*EN2*/
  }
    else if(IRQ_Num>95 && IRQ_Num<127){
        NVIC_EN3_REG =(NVIC_EN3_REG & 0x00000000)|(1<<(IRQ_Num-96));

    /*EN3*/
  }
   else if(IRQ_Num>128 && IRQ_Num<=138){
       NVIC_EN4_REG =(NVIC_EN4_REG & 0x00000000)|(1<<(IRQ_Num-128));

    /*EN4*/
  }
   else{
       //do nothing
   }


}

/*********************************************************************
 * Service Name: NVIC_DISableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to disable Interrupt request for specific IRQ
**********************************************************************/

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num) {

    if((IRQ_Num>0) & (IRQ_Num<31)){
        NVIC_DIS0_REG =(NVIC_DIS0_REG & 0x00000000)|(1<<IRQ_Num);

       }
    else if((IRQ_Num>32) & (IRQ_Num<64)){
        NVIC_DIS1_REG =(NVIC_DIS1_REG & 0x00000000)|(1<<(IRQ_Num-32));

      /*DIS1*/
    }
     else if((IRQ_Num>67) & (IRQ_Num<=95)){
         NVIC_DIS2_REG =(NVIC_DIS2_REG & 0x00000000)|(1<<(IRQ_Num-64));

      /*DIS2*/
    }
      else if((IRQ_Num>95) & (IRQ_Num<127)){
          NVIC_DIS3_REG =(NVIC_DIS3_REG & 0x00000000)|(1<<(IRQ_Num-96));

      /*DIS3*/
    }
     else if(IRQ_Num>128& IRQ_Num<=138){
         NVIC_DIS4_REG =(NVIC_DIS4_REG & 0x00000000)|(1<<(IRQ_Num-128));

      /*DIS4*/
    }
     else{
         //do nothing
     }

}

/*********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): IRQ_Num - Number of the IRQ from the target vector table / IRQ_Priority -to set Priority of Interrupt
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to SetPriorityIRQ in Vector table
**********************************************************************/

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority) {

    uint8 shift= IRQ_Num/4;

    uint8 INT_PRIORITY_BITS_POS =((8*(IRQ_Num  % 4))+5);

     volatile uint32 *priority_reg = (uint32*)(pri_BASE +(shift*4));
     *priority_reg &= ~(0x7<<INT_PRIORITY_BITS_POS);

     *priority_reg |=((IRQ_Priority & 0x7)<<INT_PRIORITY_BITS_POS);


}

/*********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the EXception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to Enable Exception interrupt
**********************************************************************/

void NVIC_EnableException(NVIC_ExceptionType Exception_Num) {


switch (Exception_Num) {
       case EXCEPTION_MEM_FAULT_TYPE:

           NVIC_SYSTEM_SYSHNDCTRL |= (1 << 16);
           break;

       case EXCEPTION_USAGE_FAULT_TYPE:

           NVIC_SYSTEM_SYSHNDCTRL |= (1 << 18);
           break;

       case EXCEPTION_BUS_FAULT_TYPE:

           NVIC_SYSTEM_SYSHNDCTRL |= (1 << 17);
           break;

       case EXCEPTION_SVC_TYPE:

           Trigger_SVC_Exception();
           break;

       case EXCEPTION_PEND_SV_TYPE:

           NVIC_SYSTEM_INTCTRL |= (1 << 28);
           break;

       case EXCEPTION_SYSTICK_TYPE:

           SYSTICK_CTRL_REG = 0;

           SYSTICK_RELOAD_REG = 15999999;

           SYSTICK_CURRENT_REG = 0;

           SYSTICK_CTRL_REG |= 0x07;
           break;

       default:
           //do no thing
           break;
   }
}

/*********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the EXception from the target vector table
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to DISable Exception interrupt
**********************************************************************/


void NVIC_DisableException(NVIC_ExceptionType Exception_Num){

    switch (Exception_Num) {
           case EXCEPTION_MEM_FAULT_TYPE:

               NVIC_SYSTEM_SYSHNDCTRL &=~ (1 << 16);
               break;

           case EXCEPTION_USAGE_FAULT_TYPE:

               NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << 18);
               break;

           case EXCEPTION_BUS_FAULT_TYPE:

               NVIC_SYSTEM_SYSHNDCTRL &= ~(1 << 17);
               break;

           case EXCEPTION_SVC_TYPE:

               //do no thing
               break;

           case EXCEPTION_PEND_SV_TYPE:

               NVIC_SYSTEM_INTCTRL &= ~ (1 << 28);
               break;

           case EXCEPTION_SYSTICK_TYPE:

               SYSTICK_CTRL_REG = 0;

               break;

           default:
               //do no thing
               break;
       }



}

/*********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: reentrant
 * Parameters (in): Exception_Num - Number of the Exception from the target vector table / Exception_Priority -to set Priority of Interrupt
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to SetPriority Exception in Vector table
**********************************************************************/

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority) {

    switch (Exception_Num) {
            case EXCEPTION_MEM_FAULT_TYPE:

                NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & MEM_MANAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_MANAGE_FAULT_PRIORITY_BITS_POS);
                break;

            case EXCEPTION_USAGE_FAULT_TYPE:

                NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
                break;

            case EXCEPTION_BUS_FAULT_TYPE:

                NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
                break;

            case EXCEPTION_SVC_TYPE:

                NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
                break;

            case EXCEPTION_PEND_SV_TYPE:

                NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
                break;

            case EXCEPTION_SYSTICK_TYPE:

                NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
                break;

            case EXCEPTION_DEBUG_MONITOR_TYPE:

                           NVIC_SYSTEM_PRI3_REG =  (NVIC_SYSTEM_PRI3_REG & DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
                           break;
            default:
                //do no thing
                break;
        }




}



