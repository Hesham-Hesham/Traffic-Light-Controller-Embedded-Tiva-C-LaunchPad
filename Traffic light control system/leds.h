 /******************************************************************************
 *
 * Module: leds
 *
 * File Name: leds.h
 *
 * Description: Header file for the led driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#ifndef LEDS_H_
#define LEDS_H_


#include "common_macros.h"
#include "std_types.h"

#include "gpio.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
 
/*			TRAFFIC DEFINITIONS			*/

//Traffic LEDS number
#define TRAFFIC_NUMBER_OF_LED			6

//Traffic North
#define TRAFFIC_NORTH_PORT_ID			PORTB_ID

#define TRAFFIC_NORTH_RED_PIN_ID 		PIN5_ID
#define TRAFFIC_NORTH_YELLOW_PIN_ID 	PIN4_ID
#define TRAFFIC_NORTH_GREEN_PIN_ID		PIN6_ID


//Traffic East
#define TRAFFIC_EAST_PORT_ID			PORTE_ID

#define TRAFFIC_EAST_RED_PIN_ID			PIN1_ID
#define TRAFFIC_EAST_YELLOW_PIN_ID		PIN2_ID
#define TRAFFIC_EAST_GREEN_PIN_ID		PIN3_ID





/*			PEDESTRIAN DEFINITIONS			*/

//Pedestrian LEDS number
#define PEDESTRIAN_NUMBER_OF_LED			4

//Pedestrian North
#define PEDESTRIAN_NORTH_PORT_ID		PORTF_ID

#define PEDESTRIAN_NORTH_RED_PIN_ID		PIN2_ID
#define PEDESTRIAN_NORTH_GREEN_PIN_ID	PIN3_ID

//Pedestrian East
#define PEDESTRIAN_EAST_PORT_ID			PORTD_ID

#define PEDESTRIAN_EAST_RED_PIN_ID		PIN3_ID
#define PEDESTRIAN_EAST_GREEN_PIN_ID	PIN2_ID

//Led states
#define LED_ON			LOGIC_HIGH
#define LED_OFF			LOGIC_LOW





/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
//Traffic Sides
typedef enum{
	
	NORTH_,EAST_
	
}LEDS_trafficSides; 
	 
 
//Traffic LEDS
typedef enum{
	
	TRAFFIC_NORTH_RED,TRAFFIC_NORTH_YELLOW,TRAFFIC_NORTH_GREEN,TRAFFIC_EAST_RED,TRAFFIC_EAST_YELLOW,TRAFFIC_EAST_GREEN
	
}LEDS_trafficLed;


//Pedestrian LEDS
typedef enum{
	
	PEDESTRIAN_NORTH_RED=7,PEDESTRIAN_NORTH_GREEN,PEDESTRIAN_EAST_RED,PEDESTRIAN_EAST_GREEN
	
}LEDS_pedestrianLed;



/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initializing the LEDS
 */
void LEDS_init(void);



/*
 * Description :
 * Function responsible for writing a logic value on a LED
 */
void LEDS_write(uint8 led, bool state);



/*
 * Description :
 * Function responsible for reading if the led is turned on or off
 */
bool LEDS_read(uint8 led);



/*
 * Description :
 * Function responsible for writing LOGIC_HIGH value on a LED
 */
void LEDS_turnOn(uint8 led);



/*
 * Description :
 * Function responsible for writing LOGIC_LOW value on a LED
 */
void LEDS_turnOff(uint8 led);



/*
 * Description :
 * Function responsible for turning off all LEDS
 */
void LEDS_turnOffAllTraffic(void);



/*
 * Description :
 * Function responsible for reading leds on a given side to checks which one is turned on and return the first one that's turned on
 */
uint8 LEDS_readAllTrafficLeds(uint8 traffic_side);

#endif
