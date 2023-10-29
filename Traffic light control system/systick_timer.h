 /******************************************************************************
 *
 * Module: systick_timer
 *
 * File Name: systick_timer.h
 *
 * Description: Header file for the ARM systick_timer driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/


#ifndef SYSTICK_TIMER_H_
#define SYSTICK_TIMER_H_

#include "std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
 
#define SYSTICK_CTRL_REG_ENABLE_BIT		0
#define SYSTICK_CTRL_REG_INTEN_BIT		1
#define SYSTICK_CTRL_REG_CLK_SRC_BIT	2
#define SYSTICK_CTRL_REG_COUNT_BIT		16



/*******************************************************************************
 *								Variables' Externs							   *
 *******************************************************************************/
 
extern volatile uint8 counter;



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

//select clock source for systick
typedef enum{
	
	PIOSC_DIV_BY_4,SYSTEM_CLOCK
	
}SYSTICK_clockSource;


//select interrupt state for systick timer
typedef enum{
	
	INTERRUPT_OFF,INTERRUPT_ON
	
}SYSTICK_interruptEnable;


//select systick timer state
typedef enum{
	
	SYSTICK_DISABLED,SYSTICK_ENABLED
	
}SYSTICK_enableSystick;


//Configuration structure for systick timer
typedef struct{
	
	SYSTICK_clockSource			clockSRC;
	SYSTICK_interruptEnable		interruptState;
	SYSTICK_enableSystick		systickState;
}SYSTICK_ConfigType;




/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/*
 * Description :
 * Function responsible for Initializing the systick timer
 */
void SYSTICK_init(SYSTICK_ConfigType *configPtr, uint32 reloadValue);



/*
 * Description :
 * Function responsible for Deinitializing the systick timer
 */
void SYSTICK_deinit(void);

#endif
