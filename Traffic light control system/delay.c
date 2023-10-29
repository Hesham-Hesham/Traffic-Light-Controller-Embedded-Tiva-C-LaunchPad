 /******************************************************************************
 *
 * Module: delay
 *
 * File Name: delay.c
 *
 * Description: Source file for the delay driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/

#include "delay.h"
#include "push_buttons.h"



/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/
 
/*
 * Description : Initialize the timer to allow the delay function to work
 *
 */
void DELAY_init(void){
	
	//Configuration structure for the systick timer
	SYSTICK_ConfigType systickConfigStruct={SYSTEM_CLOCK, INTERRUPT_ON, SYSTICK_ENABLED};
	
	//Init the systick timer with a reload value of 15999999 and the configuration structure systickConfigStruct
	SYSTICK_init(&systickConfigStruct, 15999999);
}



/*
 * Description : Delay for specific number of seconds
 *
 */
void DELAY_seconds(uint8 seconds){
	
	//Stay stuck in the loop till the counter is the same as the seconds argument which means the desired timer has elapsed
	while(counter != (1*seconds) );
	
	//Reset the counter
	counter=0;
}



/*
 * Description : Delay for specific number of minutes
 *
 */
void DELAY_minutes(uint8 minutes){
	DELAY_seconds(minutes*60);
}
