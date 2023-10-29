 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the ARM GPIO driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/

#include "gpio.h"
#include "common_macros.h" 	/* To use the macros like SET_BIT */
#include "std_types.h"		/* To use the standard types like uint8 */
#include "tm4c123gh6pm_registers.h" /* To use the GPIO Ports Registers */


/*******************************************************************************
 *                                Functions                                    *
 *******************************************************************************/
 
 
 
/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction){
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTA_DIR_REG,pin_num);	//Set the corresponding bit in the direction register
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DIR_REG,pin_num);	//Clear the corresponding bit in the direction register
			}
			break;
			
			
		case PORTB_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTB_DIR_REG,pin_num);	//Set the corresponding bit in the direction register
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DIR_REG,pin_num);	//Clear the corresponding bit in the direction register
			}
			break;
			
			
		case PORTC_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTC_DIR_REG,pin_num);	//Set the corresponding bit in the direction register
			}
			else
			{
				CLEAR_BIT(GPIO_PORTC_DIR_REG,pin_num);	//Clear the corresponding bit in the direction register
			}
			break;
			
			
		case PORTD_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTD_DIR_REG,pin_num);	//Set the corresponding bit in the direction register
			}
			else
			{
				CLEAR_BIT(GPIO_PORTD_DIR_REG,pin_num);	//Clear the corresponding bit in the direction register
			}
			break;
			
		
		case PORTE_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTE_DIR_REG,pin_num);	//Set the corresponding bit in the direction register
			}
			else
			{
				CLEAR_BIT(GPIO_PORTE_DIR_REG,pin_num);	//Clear the corresponding bit in the direction register
			}
			break;
			
			
		case PORTF_ID:
			if(direction == PIN_OUTPUT)
			{
				SET_BIT(GPIO_PORTF_DIR_REG,pin_num);	//Set the corresponding bit in the direction register
			}
			else
			{
				CLEAR_BIT(GPIO_PORTF_DIR_REG,pin_num);	//Clear the corresponding bit in the direction register
			}
			break;
			
		
		}
	}
}



/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Write the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTA_DATA_REG,pin_num);	//Write logical high on the desired pin
			}
			else
			{
				CLEAR_BIT(GPIO_PORTA_DATA_REG,pin_num);	//Write logical low on the desired pin
			}
			break;
			
			
		case PORTB_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTB_DATA_REG,pin_num);	//Write logical high on the desired pin
			}
			else
			{
				CLEAR_BIT(GPIO_PORTB_DATA_REG,pin_num);	//Write logical low on the desired pin
			}
			break;
			
			
		case PORTC_ID:
		
				
#if (ENABLE_JTAG_PINS_PROTECTION == TRUE)
			//AVOID WRITING ON JTAG PINS TO AVOID MAKING THE LAUNCHPAD LOCKED
		
			//JTAG Pins are in PORTC
			if( (pin_num==0) || (pin_num==1) || (pin_num==2) || (pin_num==3) ){
				break;
			}
#endif


			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTC_DATA_REG,pin_num);	//Write logical high on the desired pin
			}
			else
			{
				CLEAR_BIT(GPIO_PORTC_DATA_REG,pin_num);	//Write logical low on the desired pin
			}
			break;
			
			
		case PORTD_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTD_DATA_REG,pin_num);	//Write logical high on the desired pin
			}
			else
			{
				CLEAR_BIT(GPIO_PORTD_DATA_REG,pin_num);	//Write logical low on the desired pin
			}
			break;
			
		
		case PORTE_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTE_DATA_REG,pin_num);	//Write logical high on the desired pin
			}
			else
			{
				CLEAR_BIT(GPIO_PORTE_DATA_REG,pin_num);	//Write logical low on the desired pin
			}
			break;
			
			
		case PORTF_ID:
			if(value == LOGIC_HIGH)
			{
				SET_BIT(GPIO_PORTF_DATA_REG,pin_num);	//Write logical high on the desired pin
			}
			else
			{
				CLEAR_BIT(GPIO_PORTF_DATA_REG,pin_num);	//Write logical low on the desired pin
			}
			break;
			
		
		}
	}
}



/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	uint8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the pin value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(BIT_IS_SET(GPIO_PORTA_DATA_REG,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;



		case PORTB_ID:
			if(BIT_IS_SET(GPIO_PORTB_DATA_REG,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;



		case PORTC_ID:
			if(BIT_IS_SET(GPIO_PORTC_DATA_REG,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;



		case PORTD_ID:
			if(BIT_IS_SET(GPIO_PORTD_DATA_REG,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;


		case PORTE_ID:
			if(BIT_IS_SET(GPIO_PORTE_DATA_REG,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;



		case PORTF_ID:
			if(BIT_IS_SET(GPIO_PORTF_DATA_REG,pin_num))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}



/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Setup the port direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DIR_REG = direction;
			break;
		case PORTB_ID:
			GPIO_PORTB_DIR_REG = direction;
			break;
		case PORTC_ID:
			GPIO_PORTC_DIR_REG = direction;
			break;
		case PORTD_ID:
			GPIO_PORTD_DIR_REG = direction;
			break;
		case PORTE_ID:
			GPIO_PORTE_DIR_REG = direction;
			break;
		case PORTF_ID:
			GPIO_PORTF_DIR_REG = direction;
			break;
		}
	}
}


/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
 
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}else{
		/* Write the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			GPIO_PORTA_DATA_REG = value;
			break;
			
			
		case PORTB_ID:
			GPIO_PORTB_DATA_REG = value;
			break;
			
			
		case PORTC_ID:
				
#if (ENABLE_JTAG_PINS_PROTECTION == TRUE)
			//AVOID WRITING ON JTAG PINS TO AVOID MAKING THE LAUNCHPAD LOCKED
				break;
#endif

			GPIO_PORTC_DATA_REG = value;
			break;
			
			
		case PORTD_ID:
			GPIO_PORTD_DATA_REG = value;
			break;
			
			
		case PORTE_ID:
			GPIO_PORTE_DATA_REG = value;
			break;
			
			
		case PORTF_ID:
			GPIO_PORTF_DATA_REG = value;
			break;
		}
	}
}


/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			value = GPIO_PORTA_DATA_REG;
			break;
			
		case PORTB_ID:
			value = GPIO_PORTB_DATA_REG;
			break;
			
		case PORTC_ID:
			value = GPIO_PORTC_DATA_REG;
			break;
			
		case PORTD_ID:
			value = GPIO_PORTD_DATA_REG;
			break;
			
		case PORTE_ID:
			value = GPIO_PORTE_DATA_REG;
			break;
			
		case PORTF_ID:
			value = GPIO_PORTF_DATA_REG;
			break;
		}
	}

	return value;
}



/*
 * Description :
 * Initialize the pin as a digital GPIO pin with no alternative function
 */
void GPIO_initDigitalPin(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction){
	
	
	/* Enable clock for specific port and allow it to start */
	volatile uint32 dummy = 0;
	SET_BIT(SYSCTL_REGCGC2_REG,port_num);
	//Dummy operation to give enough time for port-clock to be turned on
	dummy = SYSCTL_REGCGC2_REG;


	switch(port_num)
		{
		case PORTA_ID:
		

			
			CLEAR_BIT(GPIO_PORTA_AMSEL_REG,pin_num);				/* Disable Analog on pin */
			
			/* Each pin in the port has corresponding four bits in PCTL Register,
			so to clear these four bits we do logical between them and 0x0=(0000) */
			GPIO_PORTA_PCTL_REG = GPIO_PORTA_PCTL_REG & (0x0<<pin_num*4);
			
			GPIO_setupPinDirection(PORTA_ID, pin_num, direction);	/* Configure pin direction */
			
			CLEAR_BIT(GPIO_PORTA_AFSEL_REG,pin_num);				/* Disable alternative function on pin */
			
			if(direction == PIN_INPUT)								/* Setup pull-up resistor */
			{
				SET_BIT(GPIO_PORTA_PUR_REG,pin_num);
			}
			else
			{
				// CLEAR_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			
			SET_BIT(GPIO_PORTA_DEN_REG,pin_num);					 /* Enable Digital I/O on pin */
			
			break;
			
		case PORTB_ID:
		
			CLEAR_BIT(GPIO_PORTB_AMSEL_REG,pin_num);				/* Disable Analog on pin */
			
			/* Each pin in the port has corresponding four bits in PCTL Register,
			so to clear these four bits we do logical between them and 0x0=(0000) */
			GPIO_PORTB_PCTL_REG = GPIO_PORTB_PCTL_REG & (0x0<<pin_num*4);
			
			GPIO_setupPinDirection(PORTB_ID, pin_num, direction);	/* Configure pin direction */
			
			CLEAR_BIT(GPIO_PORTB_AFSEL_REG,pin_num);				/* Disable alternative function on pin */
			
			if(direction == PIN_INPUT)								/* Setup pull-up resistor */
			{
				SET_BIT(GPIO_PORTB_PUR_REG,pin_num);
			}
			else
			{
				// CLEAR_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			
			SET_BIT(GPIO_PORTB_DEN_REG,pin_num);					 /* Enable Digital I/O on pin */
			break;
			
		case PORTC_ID:

		
#if (ENABLE_SPECIAL_PINS_PROTECTION == FALSE)
// Avoid initializing special pins if protection is enabled


#if (ENABLE_JTAG_PINS_PROTECTION == TRUE)
			//AVOID WRITING ON JTAG PINS TO AVOID MAKING THE LAUNCHPAD LOCKED
		
			//JTAG Pins are 0, 1, 2,and 3 in PORTC pins
			if( (pin_num<=0) && (pin_num>=7)){
				break;
			}
#endif

#endif
			CLEAR_BIT(GPIO_PORTC_AMSEL_REG,pin_num);				/* Disable Analog on pin */
			
			/* Each pin in the port has corresponding four bits in PCTL Register,
			so to clear these four bits we do logical between them and 0x0=(0000) */
			GPIO_PORTC_PCTL_REG = GPIO_PORTC_PCTL_REG & (0x0<<pin_num*4);
			
			GPIO_setupPinDirection(PORTC_ID, pin_num, direction);	/* Configure pin direction */
			
			CLEAR_BIT(GPIO_PORTC_AFSEL_REG,pin_num);				/* Disable alternative function on pin */
			
			if(direction == PIN_INPUT)								/* Setup pull-up resistor */
			{
				SET_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			else
			{
				// CLEAR_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			
			SET_BIT(GPIO_PORTC_DEN_REG,pin_num);					 /* Enable Digital I/O on pin */
			break;
			
		case PORTD_ID:
		
		
/* Avoid initializing pin 7 of PORTD if protection is enabled
(if it's not unlocked or commited it won't be initialized) */
#if (ENABLE_SPECIAL_PINS_PROTECTION == FALSE)

			if(pin_num==7){
				GPIO_PORTD_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTD_CR_REG */
				SET_BIT(GPIO_PORTD_CR_REG,pin_num);
			}
			
#endif


			CLEAR_BIT(GPIO_PORTD_AMSEL_REG,pin_num);				/* Disable Analog on pin */
			
			/* Each pin in the port has corresponding four bits in PCTL Register,
			so to clear these four bits we do logical between them and 0x0=(0000) */
			GPIO_PORTD_PCTL_REG = GPIO_PORTD_PCTL_REG & (0x0<<pin_num*4);
			
			GPIO_setupPinDirection(PORTD_ID, pin_num, direction);	/* Configure pin direction */
			
			CLEAR_BIT(GPIO_PORTD_AFSEL_REG,pin_num);				/* Disable alternative function on pin */
			
			if(direction == PIN_INPUT)								/* Setup pull-up resistor */
			{
				SET_BIT(GPIO_PORTD_PUR_REG,pin_num);
			}
			else
			{
				// CLEAR_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			
			SET_BIT(GPIO_PORTD_DEN_REG,pin_num);					 /* Enable Digital I/O on pin */
			break;
			
		case PORTE_ID:
		
			CLEAR_BIT(GPIO_PORTE_AMSEL_REG,pin_num);				/* Disable Analog on pin */
			
			/* Each pin in the port has corresponding four bits in PCTL Register,
			so to clear these four bits we do logical between them and 0x0=(0000) */
			GPIO_PORTE_PCTL_REG = GPIO_PORTE_PCTL_REG & (0x0<<pin_num*4);
			
			GPIO_setupPinDirection(PORTE_ID, pin_num, direction);	/* Configure pin direction */
			
			CLEAR_BIT(GPIO_PORTE_AFSEL_REG,pin_num);				/* Disable alternative function on pin */
			
			if(direction == PIN_INPUT)								/* Setup pull-up resistor */
			{
				SET_BIT(GPIO_PORTE_PUR_REG,pin_num);
			}
			else
			{
				// CLEAR_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			
			SET_BIT(GPIO_PORTE_DEN_REG,pin_num);					 /* Enable Digital I/O on pin */
			break;
			
		case PORTF_ID:


/* Avoid initializing pin 0 of PORTF if protection is enabled
(if it's not unlocked or commited it won't be initialized) */
#if (ENABLE_SPECIAL_PINS_PROTECTION == FALSE)

			if(pin_num==0){
				GPIO_PORTF_LOCK_REG   = 0x4C4F434B;   /* Unlock the GPIO_PORTF_CR_REG */
				SET_BIT(GPIO_PORTF_CR_REG,pin_num);
			}
			
#endif


			CLEAR_BIT(GPIO_PORTF_AMSEL_REG,pin_num);				/* Disable Analog on pin */
			
			/* Each pin in the port has corresponding four bits in PCTL Register,
			so to clear these four bits we do logical between them and 0x0=(0000) */
			GPIO_PORTF_PCTL_REG = GPIO_PORTF_PCTL_REG & (0x0<<pin_num*4);
			
			GPIO_setupPinDirection(PORTF_ID, pin_num, direction);	/* Configure pin direction */
			
			CLEAR_BIT(GPIO_PORTF_AFSEL_REG,pin_num);				/* Disable alternative function on pin */
			
			if(direction == PIN_INPUT)								/* Setup pull-up resistor */
			{
				SET_BIT(GPIO_PORTF_PUR_REG,pin_num);
			}
			else
			{
				// CLEAR_BIT(GPIO_PORTC_PUR_REG,pin_num);
			}
			
			SET_BIT(GPIO_PORTF_DEN_REG,pin_num);					 /* Enable Digital I/O on pin */
			break;
			
			
		}
	
	
}

