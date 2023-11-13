 /******************************************************************************
 *
 * Module: leds
 *
 * File Name: leds.c
 *
 * Description: Source file for the led driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#include "common_macros.h"
#include "std_types.h"

#include "gpio.h"
#include "leds.h"



/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for Initializing the LEDS
 */
void LEDS_init(void){
	
	//Use the GPIO driver to initialize the leds pins
	GPIO_initDigitalPin(	TRAFFIC_NORTH_PORT_ID,		TRAFFIC_NORTH_RED_PIN_ID,		PIN_OUTPUT);
	GPIO_initDigitalPin(	TRAFFIC_NORTH_PORT_ID,		TRAFFIC_NORTH_YELLOW_PIN_ID,	PIN_OUTPUT);
	GPIO_initDigitalPin(	TRAFFIC_NORTH_PORT_ID,		TRAFFIC_NORTH_GREEN_PIN_ID,		PIN_OUTPUT);

	GPIO_initDigitalPin(	TRAFFIC_EAST_PORT_ID,		TRAFFIC_EAST_RED_PIN_ID,		PIN_OUTPUT);
	GPIO_initDigitalPin(	TRAFFIC_EAST_PORT_ID,		TRAFFIC_EAST_YELLOW_PIN_ID,		PIN_OUTPUT);
	GPIO_initDigitalPin(	TRAFFIC_EAST_PORT_ID,		TRAFFIC_EAST_GREEN_PIN_ID,		PIN_OUTPUT);

	GPIO_initDigitalPin(	PEDESTRIAN_NORTH_PORT_ID,	PEDESTRIAN_NORTH_RED_PIN_ID,	PIN_OUTPUT);
	GPIO_initDigitalPin(	PEDESTRIAN_NORTH_PORT_ID,	PEDESTRIAN_NORTH_GREEN_PIN_ID,	PIN_OUTPUT);

	GPIO_initDigitalPin(	PEDESTRIAN_EAST_PORT_ID,	PEDESTRIAN_EAST_RED_PIN_ID,		PIN_OUTPUT);
	GPIO_initDigitalPin(	PEDESTRIAN_EAST_PORT_ID,	PEDESTRIAN_EAST_GREEN_PIN_ID,	PIN_OUTPUT);
}



/*
 * Description :
 * Function responsible for writing a logic value on a LED
 */
void LEDS_write(uint8 led, bool state){
	
	switch(led){
		//Traffic North
		case TRAFFIC_NORTH_RED:
			GPIO_writePin(TRAFFIC_NORTH_PORT_ID, TRAFFIC_NORTH_RED_PIN_ID, state);
			break;
			
		case TRAFFIC_NORTH_YELLOW:
			GPIO_writePin(TRAFFIC_NORTH_PORT_ID, TRAFFIC_NORTH_YELLOW_PIN_ID, state);
			break;
			
		case TRAFFIC_NORTH_GREEN:
			GPIO_writePin(TRAFFIC_NORTH_PORT_ID, TRAFFIC_NORTH_GREEN_PIN_ID, state);
			break;
		
		 //Traffic East
		case TRAFFIC_EAST_RED:
			GPIO_writePin(TRAFFIC_EAST_PORT_ID, TRAFFIC_EAST_RED_PIN_ID, state);
			break;
		
		case TRAFFIC_EAST_YELLOW:
			GPIO_writePin(TRAFFIC_EAST_PORT_ID, TRAFFIC_EAST_YELLOW_PIN_ID, state);
			break;
			
		case TRAFFIC_EAST_GREEN:
			GPIO_writePin(TRAFFIC_EAST_PORT_ID, TRAFFIC_EAST_GREEN_PIN_ID, state);
			break;
		
		//Pedestrian North
		case PEDESTRIAN_NORTH_RED:
			GPIO_writePin(PEDESTRIAN_NORTH_PORT_ID, PEDESTRIAN_NORTH_RED_PIN_ID, state);
			break;
			
		case PEDESTRIAN_NORTH_GREEN:
			GPIO_writePin(PEDESTRIAN_NORTH_PORT_ID, PEDESTRIAN_NORTH_GREEN_PIN_ID, state);
			break;
		
		//Pedestrian East
		case PEDESTRIAN_EAST_RED:
			GPIO_writePin(PEDESTRIAN_EAST_PORT_ID, PEDESTRIAN_EAST_RED_PIN_ID, state);
			break;
			
		case PEDESTRIAN_EAST_GREEN:
			GPIO_writePin(PEDESTRIAN_EAST_PORT_ID, PEDESTRIAN_EAST_GREEN_PIN_ID, state);
			break;
		
		default:
			break;
		
	}
}



/*
 * Description :
 * Function responsible for reading if the led is turned on or off
 */
bool LEDS_read(uint8 led){
	
	bool state=LED_OFF;
	
	switch(led){
		//Traffic North
		case TRAFFIC_NORTH_RED:
			state=GPIO_readPin(TRAFFIC_NORTH_PORT_ID, TRAFFIC_NORTH_RED_PIN_ID);
			break;
			
		case TRAFFIC_NORTH_YELLOW:
			state=GPIO_readPin(TRAFFIC_NORTH_PORT_ID, TRAFFIC_NORTH_YELLOW_PIN_ID);
			break;
			
		case TRAFFIC_NORTH_GREEN:
			state=GPIO_readPin(TRAFFIC_NORTH_PORT_ID, TRAFFIC_NORTH_GREEN_PIN_ID);
			break;
		
		 //Traffic East
		case TRAFFIC_EAST_RED:
			state=GPIO_readPin(TRAFFIC_EAST_PORT_ID, TRAFFIC_EAST_RED_PIN_ID);
			break;
		
		case TRAFFIC_EAST_YELLOW:
			state=GPIO_readPin(TRAFFIC_EAST_PORT_ID, TRAFFIC_EAST_YELLOW_PIN_ID);
			break;
			
		case TRAFFIC_EAST_GREEN:
			state=GPIO_readPin(TRAFFIC_EAST_PORT_ID, TRAFFIC_EAST_GREEN_PIN_ID);
			break;
		
		//Pedestrian North
		case PEDESTRIAN_NORTH_RED:
			state=GPIO_readPin(PEDESTRIAN_NORTH_PORT_ID, PEDESTRIAN_NORTH_RED_PIN_ID);
			break;
			
		case PEDESTRIAN_NORTH_GREEN:
			state=GPIO_readPin(PEDESTRIAN_NORTH_PORT_ID, PEDESTRIAN_NORTH_GREEN_PIN_ID);
			break;
		
		//Pedestrian East
		case PEDESTRIAN_EAST_RED:
			state=GPIO_readPin(PEDESTRIAN_EAST_PORT_ID, PEDESTRIAN_EAST_RED_PIN_ID);
			break;
			
		case PEDESTRIAN_EAST_GREEN:
			state=GPIO_readPin(PEDESTRIAN_EAST_PORT_ID, PEDESTRIAN_EAST_GREEN_PIN_ID);
			break;
		
		default:
			break;
		
	}
	
	return state;
}



/*
 * Description :
 * Function responsible for reading leds to checks which one is turned on and return the first one that's turned on
 */
uint8 LEDS_readAllTrafficLeds(uint8 traffic_side){
	
	uint8 firstTurnedOnLed=0;
	
	if(traffic_side == NORTH_){
		//Check if the led is on and if so, then return that led
		firstTurnedOnLed=LEDS_read(TRAFFIC_NORTH_RED);
		if(firstTurnedOnLed==LED_ON){
			firstTurnedOnLed=TRAFFIC_NORTH_RED;
			return firstTurnedOnLed;
		}
		
		//Check if the led is on and if so, then return that led
		firstTurnedOnLed=LEDS_read(TRAFFIC_NORTH_YELLOW);
		if(firstTurnedOnLed==LED_ON){
			firstTurnedOnLed=TRAFFIC_NORTH_YELLOW;
			return firstTurnedOnLed;
		}
		
		//Check if the led is on and if so, then return that led
		firstTurnedOnLed=LEDS_read(TRAFFIC_NORTH_GREEN);
		if(firstTurnedOnLed==LED_ON){
			firstTurnedOnLed=TRAFFIC_NORTH_GREEN;
			return firstTurnedOnLed;
		}
	
	}
	
	if(traffic_side == EAST_){
		//Check if the led is on and if so, then return that led
		firstTurnedOnLed=LEDS_read(TRAFFIC_EAST_RED);
		if(firstTurnedOnLed==LED_ON){
			firstTurnedOnLed=TRAFFIC_EAST_RED;
			return firstTurnedOnLed;
		}
		
		//Check if the led is on and if so, then return that led
		firstTurnedOnLed=LEDS_read(TRAFFIC_EAST_YELLOW);
		if(firstTurnedOnLed==LED_ON){
			firstTurnedOnLed=TRAFFIC_EAST_YELLOW;
			return firstTurnedOnLed;
		}
		
		//Check if the led is on and if so, then return that led
		firstTurnedOnLed=LEDS_read(TRAFFIC_EAST_GREEN);
		if(firstTurnedOnLed==LED_ON){
			firstTurnedOnLed=TRAFFIC_EAST_GREEN;
			return firstTurnedOnLed;
		}
	}
	
	
	return firstTurnedOnLed;

}



/*
 * Description :
 * Function responsible for writing LOGIC_HIGH value on a LED
 */
void LEDS_turnOn(uint8 led){
	LEDS_write(led, LOGIC_HIGH);
}



/*
 * Description :
 * Function responsible for writing LOGIC_LOW value on a LED
 */
void LEDS_turnOff(uint8 led){
	LEDS_write(led, LOGIC_LOW);
}



/*
 * Description :
 * Function responsible for turning off all traffic LEDS
 */
void LEDS_turnOffAllTraffic(void){
	
	LEDS_turnOff(TRAFFIC_EAST_GREEN);
	LEDS_turnOff(TRAFFIC_EAST_YELLOW);
	LEDS_turnOff(TRAFFIC_EAST_RED);

	LEDS_turnOff(TRAFFIC_NORTH_GREEN);
	LEDS_turnOff(TRAFFIC_NORTH_YELLOW);
	LEDS_turnOff(TRAFFIC_NORTH_RED);

}


