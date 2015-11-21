/*
 * GPIO.h
 *
 *  Created on: Oct 18, 2015
 *      Author: Vallejo
 */

#ifndef GPIO_H_
#define GPIO_H_


/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       GPIO.h
* version:         1.0 
* created_by:      AVR
* date_created:    Oct 18, 2015 
*=============================================================================*/
/* DESCRIPTION :                                                              */
/*============================================================================*/
/* FUNCTION COMMENT : This header must be placed anywhere scheduler is        */
/* required.                                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |  AUTHOR  | Comment     						  */
/*----------------------------------------------------------------------------*/
/*    1.0	    18/10/2015     AVR		add the init functions for gpios.
 *    1.1	    20/10/2015     AVR		Change the GPIO registers to FGPIO.                                              							  */
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
/* Exported types and constants */
/* ---------------------------- */

/* Types definition */



/*======================================================*/ 
/* Declaration of exported constants                    */
/*======================================================*/ 



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

void vfn_init_userGPIO_LineScanCamera (void)		;
void vfn_init_userGPIO_shield_DCmotors (void)		;
void vfn_init_userGPIO_tfcshield(void)				;
void vfn_init_userGPIO_speedSensors(void)			;
volatile T_BOOLEAN ub_state_SpeedSensor0_PTA1(void) ;
volatile T_BOOLEAN ub_state_SpeedSensor1_PTA2 (void);
volatile uint16_t u16_DipSW_val(void)				;
volatile uint8_t u8_PushButtonA_state(void)			; 
volatile uint8_t u8_PushButtonB_state(void)			;

#define CAMERA_CLK_HIGH  	FGPIOE_PSOR |= GPIO_PIN(1U)	  //pin PTE1 for the HIGH CLK signal to the line scan camera.  
#define CAMERA_CLK_LOW   	FGPIOE_PCOR |= GPIO_PIN(1U)	  //pin PTE1 for the LOW CLK signal to the line scan camera.  
#define CAMERA_SI_HIGH  	FGPIOD_PSOR |= GPIO_PIN(7U)	  //pin PTD7 for the HIGH SI signal to the line scan camera. 
#define CAMERA_SI_LOW    	FGPIOD_PCOR |= GPIO_PIN(7U)   //pin PTD7 for the LOW SI signal to the line scan camera. 
#define ENABLE_H_BRIGDE	    FGPIOE_PSOR |= GPIO_PIN(21U)  // enable H - bridge
#define DISABLE_H_BRIGDE	FGPIOE_PCOR |= GPIO_PIN(21U)  // disable H - bridge

#define PTA12_TEST_HIGH		FGPIOA_PSOR |= GPIO_PIN(12U)
#define PTA12_TEST_LOW		FGPIOA_PCOR |= GPIO_PIN(12U)

#define PTA13_TEST_HIGH		FGPIOA_PSOR |= GPIO_PIN(13U)
#define PTA13_TEST_LOW		FGPIOA_PCOR |= GPIO_PIN(13U)

#define GPIO_PIN(x)		    (1U << x)

#define LED_SENS0_HIGH	 	FGPIOB_PSOR |= GPIO_PIN(8U)
#define LED_SENS0_LOW	  	FGPIOB_PCOR |= GPIO_PIN(8U)
#define LED_SENS1_HIGH	  	FGPIOB_PSOR |= GPIO_PIN(9U)
#define LED_SENS1_LOW	 	FGPIOB_PCOR |= GPIO_PIN(9U)

#define LEDS_VEL_STATE_0  	FGPIOB_PCOR |= (0xC00)
#define LEDS_VEL_STATE_1  	FGPIOB_PDOR |= (0x400)
#define LEDS_VEL_STATE_2  	FGPIOB_PDOR |= (0x800)
#define LEDS_VEL_STATE_3  	FGPIOB_PDOR |= (0xC00)
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* GPIO_H_ */
