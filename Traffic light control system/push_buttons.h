 /******************************************************************************
 *
 * Module: push_buttons
 *
 * File Name: push_buttons.h
 *
 * Description: Header file for the push buttons driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#ifndef PUSH_BUTTONS_H_
#define PUSH_BUTTONS_H_


#include "common_macros.h"
#include "std_types.h"

#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

//Pedestrian North
#define PEDESTRIAN_PB_NORTH_PORT_ID		PORTA_ID
#define PEDESTRIAN_PB_NORTH_PIN_ID		PIN2_ID

//Pedestrian East
#define PEDESTRIAN_PB_EAST_PORT_ID		PORTA_ID
#define PEDESTRIAN_PB_EAST_PIN_ID		PIN3_ID


#define PB_PRESSED			LOGIC_LOW
#define PB_RELEASED			LOGIC_HIGH



/*******************************************************************************
 *								Variables' Externs							   *
 *******************************************************************************/
 
extern volatile uint8 saved_counter;
extern volatile uint8 north_button;
extern volatile uint8 east_button;



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

//Pedestrian LEDS
typedef enum{
	
	PEDESTRIAN_PB_NORTH,PEDESTRIAN_PB_EAST
	
}LEDS_pedestrianPushButtons;




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initializing the push buttons
 */
void PUSH_BUTTONS_init(void);
	

/*
 * Description :
 * Function responsible for reading the push button value
 */
uint8 PUSH_BUTTONS_readValue(uint8 pushButton);



/*
 * Description :
 * Function responsible for saving the current counter value then resetting current counter
 */
void static PUSH_BUTTONS_saveCounter(void);



/*
 * Description :
 * Function responsible for handling the interrupt from button 1 and calling the callback function
 */
void PUSH_BUTTONS_handleInterrupt_1(void);



/*
 * Description :
 * Function responsible for handling the interrupt from button 2 and calling the callback function
 */
void PUSH_BUTTONS_handleInterrupt_2(void);



/*
 * Description :
 * Function responsible for setting the callback function that is called in the app layer
 */
void PUSH_BUTTONS_setCallBack(void(*a_ptr)(void));


#endif PUSH_BUTTONS_H_