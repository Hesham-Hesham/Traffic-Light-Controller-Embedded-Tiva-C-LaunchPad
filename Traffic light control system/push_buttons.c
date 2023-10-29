 /******************************************************************************
 *
 * Module: push_buttons
 *
 * File Name: push_buttons.c
 *
 * Description: Source file for the push buttons driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#include "push_buttons.h"

#include "common_macros.h"
#include "std_types.h"

#include "gpio.h"
#include "external_interrupts.h"
#include "systick_timer.h"



/*******************************************************************************
 *								Variable Definitions						   *
 *******************************************************************************/
 
//A variable that holds the current value of the counter before we reset it
volatile uint8 saved_counter;

//A variable that gets changed inside the push button handler for the north button
volatile uint8 north_button=PB_RELEASED;

//A variable that gets changed inside the push button handler for the north button
volatile uint8 east_button=PB_RELEASED;

//A global pointer to function that is used for calling the callback function
static volatile void 	(*PUSH_BUTTONS_g_callBackPtr)(void) = NULL_PTR;




/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initializing the push buttons
 */
void PUSH_BUTTONS_init(void){
	
	//Initialize the push buttons pins using the GPIO driver
	GPIO_initDigitalPin(	PEDESTRIAN_PB_NORTH_PORT_ID,		PEDESTRIAN_PB_NORTH_PIN_ID,		PIN_INPUT);
	GPIO_initDigitalPin(	PEDESTRIAN_PB_EAST_PORT_ID,			PEDESTRIAN_PB_EAST_PIN_ID,		PIN_INPUT);
	
	//Two configuration structures for the external interrupt (each one of the two buttons has a config struct of its own)
	EXTERNAL_INTERRUPTS_ConfigType externalInterruptConfigStruct_1= 	{1, PEDESTRIAN_PB_EAST_PORT_ID, PEDESTRIAN_PB_EAST_PIN_ID, edge, one_edge, falling_edge};
	EXTERNAL_INTERRUPTS_ConfigType externalInterruptConfigStruct_2= 	{1, PEDESTRIAN_PB_NORTH_PORT_ID, PEDESTRIAN_PB_NORTH_PIN_ID, edge, one_edge, falling_edge};

	//Initialize the two buttons as two external interrupts
	EXTERNAL_INTERRUPT_init(&externalInterruptConfigStruct_1);
	EXTERNAL_INTERRUPT_init(&externalInterruptConfigStruct_2);

	//Set the two callback functions for the two push buttons
	EXTERNAL_INTERRUPT_setCallBack_1(PUSH_BUTTONS_handleInterrupt_1);
	EXTERNAL_INTERRUPT_setCallBack_2(PUSH_BUTTONS_handleInterrupt_2);
}



/*
 * Description :
 * Function responsible for reading the push button value
 */
uint8 PUSH_BUTTONS_readValue(uint8 pushButton){
	
	//A variable to hold the return value from the push buttons
	uint8 returnValue=0xFF;
	
	if(pushButton==PEDESTRIAN_PB_NORTH){
		//Read the value from the north pb
		returnValue=GPIO_readPin(PEDESTRIAN_PB_NORTH_PORT_ID,PEDESTRIAN_PB_NORTH_PIN_ID);

	}else if(pushButton==PEDESTRIAN_PB_EAST){
		//Read the value from the east pb
		returnValue=GPIO_readPin(PEDESTRIAN_PB_EAST_PORT_ID,PEDESTRIAN_PB_EAST_PIN_ID);
		
	}else{
		//Do nothing
	}
	
	return returnValue;
}



/*
 * Description :
 * Function responsible for handling the interrupt from button 1 and calling the callback function
 */
void PUSH_BUTTONS_handleInterrupt_1(void){
	
	//Declare that the north buttin was pressed
	north_button=PB_PRESSED;
	PUSH_BUTTONS_saveCounter();
	
	(*PUSH_BUTTONS_g_callBackPtr)();	//Call the callback function that is stored in the pointer

}



/*
 * Description :
 * Function responsible for handling the interrupt from button 2 and calling the callback function
 */
void PUSH_BUTTONS_handleInterrupt_2(void){
	
	//Declare that the east buttin was pressed
	east_button=PB_PRESSED;
	PUSH_BUTTONS_saveCounter();	
	
	(*PUSH_BUTTONS_g_callBackPtr)();	//Call the callback function that is stored in the pointer
}



/*
 * Description :
 * Function responsible for saving the current counter value then resetting current counter
 */
void static PUSH_BUTTONS_saveCounter(void){
	saved_counter=counter;
	counter=0;
}



/*
 * Description :
 * Function responsible for setting the callback function that is called in the app layer
 */
void PUSH_BUTTONS_setCallBack(void(*a_ptr)(void)){
	PUSH_BUTTONS_g_callBackPtr=(volatile void(*) (void)) a_ptr;
}
