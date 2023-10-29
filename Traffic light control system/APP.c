
#include "leds.h"
#include "push_buttons.h"
#include "systick_timer.h"
#include "delay.h"

#include "common_macros.h" /* To use the macros like SET_BIT */
#include "std_types.h"		/* To use the standard types like uint8 */




/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
 
/* Enable Exceptions ... This Macro enable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Enable_Exceptions()    __asm("CPSIE I")

/* Disable Exceptions ... This Macro disable IRQ interrupts, Programmble Systems Exceptions and Faults by clearing the I-bit in the PRIMASK. */
#define Disable_Exceptions()   __asm("CPSID I")

/* Enable Faults ... This Macro enable Faults by clearing the F-bit in the FAULTMASK */
#define Enable_Faults()        __asm("CPSIE F")

/* Disable Faults ... This Macro disable Faults by setting the F-bit in the FAULTMASK */
#define Disable_Faults()       __asm("CPSID F") 

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("WFI")





/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
void init_drivers(void);
void pedestrian_handler(void);
void test_pb(void);
void test_pedestrian_rolling(void);



/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/
 
int main()
{
	
	//Initialize all drivers
	init_drivers();
	
	//Set the callback function for the PUSH_BUTTONS driver
	PUSH_BUTTONS_setCallBack(pedestrian_handler);
	
    /* Enable Interrupts, Exceptions and Faults */
    Enable_Exceptions();
    Enable_Faults();
	
	
	//Start off by turning traffic lights off and pedestrian red lights on
	LEDS_turnOffAllTraffic();
	LEDS_turnOn(PEDESTRIAN_NORTH_RED);
	LEDS_turnOn(PEDESTRIAN_EAST_RED);

	for(;;){
		
		/* Rolling action where :
		-green is on for 5 seconds
		-yellow is on for 2 seconds
		-red is on for 1 */
			
			LEDS_turnOn(TRAFFIC_NORTH_GREEN);
			DELAY_seconds(5);
			LEDS_turnOff(TRAFFIC_NORTH_GREEN);

			LEDS_turnOn(TRAFFIC_NORTH_YELLOW);
			DELAY_seconds(2);
			LEDS_turnOff(TRAFFIC_NORTH_YELLOW);

			LEDS_turnOn(TRAFFIC_NORTH_RED);
			DELAY_seconds(1);
			LEDS_turnOff(TRAFFIC_NORTH_RED);

			
			LEDS_turnOn(TRAFFIC_EAST_GREEN);
			DELAY_seconds(5);
			LEDS_turnOff(TRAFFIC_EAST_GREEN);

			LEDS_turnOn(TRAFFIC_EAST_YELLOW);
			DELAY_seconds(2);
			LEDS_turnOff(TRAFFIC_EAST_YELLOW);

			LEDS_turnOn(TRAFFIC_EAST_RED);
			DELAY_seconds(1);
			LEDS_turnOff(TRAFFIC_EAST_RED);
	}
	return 0;
}



/*
 * Description : Initialize the delay, leds, and push buttons drivers
 *
 */
void init_drivers(void){
	
	DELAY_init();
	LEDS_init();
	PUSH_BUTTONS_init();
}



/*
 * Description : The callback function for the PUSH_BUTTONS layer
 * - It handles the case of a pedestrian pushing either the 
 * north or east button to pass the road 
 *
 */
void pedestrian_handler(void){
	
	//Save the last active light before turning it off
	uint8 lastActiveLED = LEDS_readAllTrafficLeds();
	LEDS_turnOff(lastActiveLED);
	
	// LEDS_turnOffAllTraffic();
	
	if(north_button==PB_PRESSED){
		
		//Stop the green north traffic to allow north pedestrians to pass
		LEDS_turnOn(TRAFFIC_NORTH_RED);

		//Turn of the normally on red pesestrian light
		LEDS_turnOff(PEDESTRIAN_NORTH_RED);
		
		//Turn on the green pesestrian light
		LEDS_turnOn(PEDESTRIAN_NORTH_GREEN);
		DELAY_seconds(2);
		
		//Turn off the green pesestrian light
		LEDS_turnOff(PEDESTRIAN_NORTH_GREEN);
		
		//Turn on the red north traffic
		LEDS_turnOn(PEDESTRIAN_NORTH_RED);
		
		//Assign the previously saved counter to the delay "counter" variable
		counter=saved_counter;
		
		//Reset the saved counter
		saved_counter=0;

		//Reset the north_button state
		north_button=PB_RELEASED;
		
		
	}
	if(east_button==PB_PRESSED){

		//Stop the green east traffic to allow east pedestrians to pass		
		LEDS_turnOn(TRAFFIC_EAST_RED);

		//Turn of the normally on red pesestrian light
		LEDS_turnOff(PEDESTRIAN_EAST_RED);
		
		//Turn on the green pesestrian light
		LEDS_turnOn(PEDESTRIAN_EAST_GREEN);
		DELAY_seconds(2);
		
		//Turn off the green pesestrian light
		LEDS_turnOff(PEDESTRIAN_EAST_GREEN);
		
		//Turn on the red east traffic
		LEDS_turnOn(PEDESTRIAN_EAST_RED);
		
		
		//Assign the previously saved counter to the delay "counter" variable
		counter=saved_counter;
		
		//Reset the saved counter
		saved_counter=0;
		
		//Reset the east_button state
		east_button=PB_RELEASED;

	}
	
	//Turn off all the traffic lights
	LEDS_turnOffAllTraffic();
	
	//Resume the last active light with the saved counter value
	LEDS_turnOn(lastActiveLED);

}



/*
 * Description : Test the two pushbuttons by turning on and off specific leds
 *
 */
void test_pb(void){
	for(;;){
		
		if( (PUSH_BUTTONS_readValue(PEDESTRIAN_PB_NORTH) )== PB_PRESSED){
			
			LEDS_turnOn(TRAFFIC_NORTH_GREEN);
			LEDS_turnOff(TRAFFIC_EAST_GREEN);
		}

		if( (PUSH_BUTTONS_readValue(PEDESTRIAN_PB_EAST) )== PB_PRESSED){
			
			LEDS_turnOn(TRAFFIC_EAST_GREEN);
			LEDS_turnOff(TRAFFIC_NORTH_GREEN);
		}	
		
	}
}



/*
 * Description : Test the pedestrian leds by rolling them in sequence
 *
 */
void test_pedestrian_rolling(void){

	for(;;){
	
			LEDS_turnOn(PEDESTRIAN_EAST_RED);
			DELAY_seconds(2);
			LEDS_turnOff(PEDESTRIAN_EAST_RED);
			
			LEDS_turnOn(PEDESTRIAN_EAST_GREEN);
			DELAY_seconds(2);
			LEDS_turnOff(PEDESTRIAN_EAST_GREEN);
			
			
			LEDS_turnOn(PEDESTRIAN_NORTH_RED);
			DELAY_seconds(2);
			LEDS_turnOff(PEDESTRIAN_NORTH_RED);
			
			
			LEDS_turnOn(PEDESTRIAN_NORTH_GREEN);
			DELAY_seconds(2);
			LEDS_turnOff(PEDESTRIAN_NORTH_GREEN);
	}	

}

