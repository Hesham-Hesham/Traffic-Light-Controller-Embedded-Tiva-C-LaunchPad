 /******************************************************************************
 *
 * Module: external_interrupt
 *
 * File Name: external_interrupt.h
 *
 * Description: Header file for the ARM external interrupt driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/
 
#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_



#include "gpio.h"			/* To use port numbers */
#include "common_macros.h" 	/* To use the macros like SET_BIT */
#include "std_types.h"	



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PRIn_INTA_MASK					0x000000E0
#define PRIn_INTA_PRIORITY_START_BIT	5

#define PRIn_INTB_MASK					0x0000E000
#define PRIn_INTB_PRIORITY_START_BIT	13

#define PRIn_INTC_MASK					0x00E00000
#define PRIn_INTC_PRIORITY_START_BIT	21

#define PRIn_INTD_MASK					0xE0000000
#define PRIn_INTD_PRIORITY_START_BIT	29

#define PRIn_INTE_MASK					0x000000E0
#define PRIn_INTE_PRIORITY_START_BIT	5

#define PRIn_INTF_MASK					0x00E00000
#define PRIn_INTF_PRIORITY_START_BIT	21

#define ICR_FLAG_BIT					5

#define MAX_PRIORITY_VALUE				7



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

//To set the interrupt sense
typedef enum{
	
	edge,level
	
}EXTERNAL_INTERRUPTS_interruptSense;


//To set what activates the trigger
typedef enum{
	
	one_edge,both_edges,no_edges
	
}EXTERNAL_INTERRUPTS_edges;


//To set the edge which activates the trigger
typedef enum{
	
	falling_edge,rising_edge,no_external_edges
	
}EXTERNAL_INTERRUPTS_event;


//A configuration structure to be used in initializing the external interrupts
typedef struct{
	
	uint8 								priority;
	uint8								port_num;
	uint8								pin_num;
	EXTERNAL_INTERRUPTS_interruptSense 	interrupt_senstivity;
	EXTERNAL_INTERRUPTS_edges			edges;		
	EXTERNAL_INTERRUPTS_event			event;
	
}EXTERNAL_INTERRUPTS_ConfigType;



/*******************************************************************************
 *                           Functions Prototypes                              *
 *******************************************************************************/
 
 /*
 * Description : enable external interrupt 0 with falling edge triggering
 *
 */
void EXTERNAL_INTERRUPT_init(EXTERNAL_INTERRUPTS_ConfigType *Config_ptr);



/*
 * Description : - Set interrupt priority for a specific port
 *				 - The function is set as a static to prevent other modules from using it
 *
 */
static void EXTERNAL_INTERRUPT_setPriority(const uint8 port_num, const uint8 interrupt_priority);



/*
 * Description : Set module interrupt mask
 *
 */
static void EXTERNAL_INTERRUPT_moduleInterruptMask(const uint8 port_num, const uint8 pin_num);



/*
 * Description : Set callback function 1 for the external interrupts
 *
 */
void EXTERNAL_INTERRUPT_setCallBack_1(void(*a_ptr)(void));



/*
 * Description : Set callback function 2 for the external interrupts
 *
 */
void EXTERNAL_INTERRUPT_setCallBack_2(void(*a_ptr)(void));


#endif /* EXTERNAL_INTERRUPTS_H_ */
