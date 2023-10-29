 /******************************************************************************
 *
 * Module: external_interrupt
 *
 * File Name: external_interrupt.c
 *
 * Description: Source file for the ARM external interrupt driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#include "external_interrupts.h"
#include "std_types.h"
#include "gpio.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h" /* To use the  Registers */




/*******************************************************************************
 *								Variable Definitions						   *
 *******************************************************************************/
 

//A global pointer to function that is used for calling the callback function
static volatile void (*EXTERNAL_INTERRUPT_g_callBackPtr_1)(void) = NULL_PTR;

//A global pointer to function that is used for calling the callback function
static volatile void (*EXTERNAL_INTERRUPT_g_callBackPtr_2)(void) = NULL_PTR;




/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/
 
 
/*
 * Description : enable external interrupt 0 with falling edge triggering
 *
 */
void EXTERNAL_INTERRUPT_init(EXTERNAL_INTERRUPTS_ConfigType *Config_ptr){
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if( (Config_ptr->port_num) >= NUM_OF_PORTS){
		return;
	}

	if( (Config_ptr->priority) >MAX_PRIORITY_VALUE){
		
		/* If the entered value is larger than the max value 
		then set the external interrupt priority value to the max */
		// interrupt_priority=MAX_PRIORITY_VALUE;
	}
	
	//	1) Set interrupt priority
	EXTERNAL_INTERRUPT_setPriority((Config_ptr->port_num),(Config_ptr->priority));
	
	//	2) Enable the interrupt
	SET_BIT(NVIC_EN0_REG,(Config_ptr->port_num));
	
	// 3) Set interrupt senstivity
	if((Config_ptr->port_num) == edge){
		SET_BIT(GPIO_PORTF_IS_REG,(Config_ptr->port_num));
		
		//if "edge" was selected then start choosing between "both edges" or "one edge"
		// A) Set interrupt edge type
		if((Config_ptr->port_num) == both_edges){
			SET_BIT(GPIO_PORTF_IS_REG,(Config_ptr->port_num));
			
			
		}else if((Config_ptr->port_num) == one_edge){
			CLEAR_BIT(GPIO_PORTF_IS_REG,(Config_ptr->port_num));
			
			//if "one edge" was selected then start choosing between "falling edge" or "rising edge"
			// B) Pick which edge to use as a trigger
			if((Config_ptr->port_num) == rising_edge){
			SET_BIT(GPIO_PORTF_IS_REG,(Config_ptr->port_num));
			
			}else if((Config_ptr->port_num) == falling_edge){
				CLEAR_BIT(GPIO_PORTF_IS_REG,(Config_ptr->port_num));
				
			}else{
				
			}
		
		}
	}else if((Config_ptr->port_num) == level){
		CLEAR_BIT(GPIO_PORTF_IS_REG,(Config_ptr->port_num));
		
	}else{
		
	}
	
	
	// 4) Enable GPIO module interrupt and 5) Clear the flag
	EXTERNAL_INTERRUPT_moduleInterruptMask((Config_ptr->port_num),(Config_ptr->pin_num));
	
}



/*
 * Description : Set module interrupt mask
 *
 */
static void EXTERNAL_INTERRUPT_moduleInterruptMask(const uint8 port_num, const uint8 pin_num){
	
		switch(port_num){
		
			case PORTA_ID:
				SET_BIT(GPIO_PORTA_IM_REG,	pin_num);	//Set the bit corresponding to the pin causing the interrupt
				SET_BIT(GPIO_PORTA_ICR_REG,	pin_num);	//Clear the flag corresponding to the pin causing the interrupt
				break;
				
			case PORTB_ID:
				SET_BIT(GPIO_PORTB_IM_REG,	pin_num);	//Set the bit corresponding to the pin causing the interrupt
				SET_BIT(GPIO_PORTB_ICR_REG,	pin_num);	//Clear the flag corresponding to the pin causing the interrupt
				break;
				
			case PORTC_ID:
				SET_BIT(GPIO_PORTC_IM_REG,	pin_num);	//Set the bit corresponding to the pin causing the interrupt
				SET_BIT(GPIO_PORTC_ICR_REG,	pin_num);	//Clear the flag corresponding to the pin causing the interrupt
				break;
				
			case PORTD_ID:
				SET_BIT(GPIO_PORTD_IM_REG,	pin_num);	//Set the bit corresponding to the pin causing the interrupt
				SET_BIT(GPIO_PORTD_ICR_REG,	pin_num);	//Clear the flag corresponding to the pin causing the interrupt
				break;
			
			case PORTE_ID:
				SET_BIT(GPIO_PORTE_IM_REG,	pin_num);	//Set the bit corresponding to the pin causing the interrupt
				SET_BIT(GPIO_PORTE_ICR_REG,	pin_num);	//Clear the flag corresponding to the pin causing the interrupt
				break;			
				
			case PORTF_ID:
				SET_BIT(GPIO_PORTF_IM_REG,	pin_num);	//Set the bit corresponding to the pin causing the interrupt
				SET_BIT(GPIO_PORTF_ICR_REG,	pin_num);	//Clear the flag corresponding to the pin causing the interrupt
				break;			

		}
}



/*
 * Description : Set callback function 1 for the external interrupts
 *
 */
void EXTERNAL_INTERRUPT_setCallBack_1( void(*a_ptr)(void)){
	EXTERNAL_INTERRUPT_g_callBackPtr_1=(volatile void(*) (void)) a_ptr;
}



/*
 * Description : Set callback function 2 for the external interrupts
 *
 */
void EXTERNAL_INTERRUPT_setCallBack_2( void(*a_ptr)(void)){
	EXTERNAL_INTERRUPT_g_callBackPtr_2=(volatile void(*) (void)) a_ptr;
}



/*
 * Description : Exception handler for GPIO PORTA
 *
 */
void GPIO_PORTA_Handler(void){
	
		if(BIT_IS_SET(GPIO_PORTA_RIS_REG,2)){
			
			// Check if the ptr has been assigned to a function (that will be called)
			if(EXTERNAL_INTERRUPT_g_callBackPtr_1 != NULL_PTR){
				(*EXTERNAL_INTERRUPT_g_callBackPtr_1)();	//Call the callback function that is stored in the pointer
					SET_BIT(GPIO_PORTA_ICR_REG,2); //CLEAR FLAG
			}
			
		}else if(BIT_IS_SET(GPIO_PORTA_RIS_REG,3)){
			
			// Check if the ptr has been assigned to a function (that will be called)
			if(EXTERNAL_INTERRUPT_g_callBackPtr_2 != NULL_PTR){
				(*EXTERNAL_INTERRUPT_g_callBackPtr_2)();	//Call the callback function that is stored in the pointer
					SET_BIT(GPIO_PORTA_ICR_REG,3); //CLEAR FLAG
			}
		}
	
	
}



/*
 * Description : - Set interrupt priority for a specific port
 *				 - The function is set as a static to prevent other modules from using it
 *
 */
static void EXTERNAL_INTERRUPT_setPriority(const uint8 port_num, const uint8 interrupt_priority){
	
		switch(port_num){
		
		case PORTA_ID:
		
			// (GPIO Port A) is numbered 16 in the vector table so it falls within the first 3 bits in register PRI0
			NVIC_PRI0_REG = (NVIC_PRI0_REG & PRIn_INTA_MASK) | (interrupt_priority << PRIn_INTA_PRIORITY_START_BIT);
			break;
			
		case PORTB_ID:

			// (GPIO Port B) is numbered 17 in the vector table so it falls within the second 3 bits in register PRI0
			NVIC_PRI0_REG = (NVIC_PRI0_REG & PRIn_INTB_MASK) | (interrupt_priority << PRIn_INTB_PRIORITY_START_BIT);
			break;
			
		case PORTC_ID:
		
			// (GPIO Port C) is numbered 18 in the vector table so it falls within the third 3 bits in register PRI0
			NVIC_PRI0_REG = (NVIC_PRI0_REG & PRIn_INTC_MASK) | (interrupt_priority << PRIn_INTC_PRIORITY_START_BIT);
			break;
			
		case PORTD_ID:

			// (GPIO Port D) is numbered 19 in the vector table so it falls within the fourth 3 bits in register PRI0
			NVIC_PRI0_REG = (NVIC_PRI0_REG & PRIn_INTD_MASK) | (interrupt_priority << PRIn_INTD_PRIORITY_START_BIT);
			break;
		
		case PORTE_ID:

			// (GPIO Port E) is numbered 20 in the vector table so it falls within the first 3 bits in register PRI1
			NVIC_PRI1_REG = (NVIC_PRI1_REG & PRIn_INTE_MASK) | (interrupt_priority << PRIn_INTE_PRIORITY_START_BIT);
			break;			
			
		case PORTF_ID:

			// (GPIO Port F) is numbered 46 in the vector table so it falls within the third 3 bits in register PRI7
			NVIC_PRI7_REG = (NVIC_PRI7_REG & PRIn_INTF_MASK) | (interrupt_priority << PRIn_INTF_PRIORITY_START_BIT);
			break;			

		}	
}
