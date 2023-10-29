 /******************************************************************************
 *
 * Module: delay
 *
 * File Name: delay.h
 *
 * Description: Header file for the delay driver
 *
 * Author: Hesham Hesham
 *
 *******************************************************************************/

#ifndef DELAY_H_
#define DELAY_H_


#include "common_macros.h"
#include "std_types.h"
#include "systick_timer.h"


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
 
/*
 * Description : Initialize the timer to allow the delay function to work
 *
 */
void DELAY_init(void);



/*
 * Description : Delay for specific number of seconds
 *
 */
void DELAY_seconds(uint8 seconds);



/*
 * Description : Delay for specific number of minutes
 *
 */
void DELAY_minutes(uint8 minutes);

#endif