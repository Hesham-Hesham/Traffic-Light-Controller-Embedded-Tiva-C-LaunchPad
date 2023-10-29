 /******************************************************************************
 *
 * Module: systick_timer
 *
 * File Name: systick_timer.c
 *
 * Description: Source file for the ARM systick_timer driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#include "systick_timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"

#include "tm4c123gh6pm_registers.h" /* To use the Registers */



/*******************************************************************************
 *								Variable Definitions						   *
 *******************************************************************************/
 
//Global variable to hold the value for the counter that increases with each tick
volatile uint8 counter = 0;



/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initializing the systick timer
 */
void SYSTICK_init(SYSTICK_ConfigType *configPtr, uint32 reloadValue){
	
	SYSTICK_CTRL_REG    = 0;               /* Disable the SysTick Timer by Clear the ENABLE Bit */
	SYSTICK_RELOAD_REG  = reloadValue;        /* Set the Reload value */
	SYSTICK_CURRENT_REG = 0;               /* Clear the Current Register value */
	
	/*Configure the SysTick Control Register*/
	
	//	1) Choose the clock source
	if( (configPtr->clockSRC) == 0){
		CLEAR_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_CLK_SRC_BIT);
		
	}else if((configPtr->clockSRC) == 1){
		SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_CLK_SRC_BIT);

	}else{
		//do nothing
	}
	
	
	//	2) Choose the interrupt state
	if( (configPtr->interruptState) == 0){
		CLEAR_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_INTEN_BIT);
		
	}else if((configPtr->interruptState) == 1){
		SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_INTEN_BIT);

	}else{
		//do nothing
	}
	
	
	//	3) Choose the systick state
	if( (configPtr->systickState) == 0){
		CLEAR_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_ENABLE_BIT);
		
	}else if((configPtr->systickState) == 1){
		SET_BIT(SYSTICK_CTRL_REG,SYSTICK_CTRL_REG_ENABLE_BIT);

	}else{
		//do nothing
	}
	
}


/*
 * Description :
 * Function responsible for Deinitializing the systick timer
 */
void SYSTICK_deinit(void){
	
	SYSTICK_CTRL_REG    = 0;               /* Disable the SysTick Timer by Clear the ENABLE Bit */
	SYSTICK_CURRENT_REG = 0;               /* Clear the Current Register value */	
}






/*
 * Description :
 * Exception handler for the systick timer responsible for increasing the counter value each time the interrupt occurs
 */
void SysTick_Handler(void){
	counter++;
}
