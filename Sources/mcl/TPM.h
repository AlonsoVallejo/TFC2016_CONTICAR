/*
 * TPM.h
 *
 *  Created on: Oct 18, 2015
 *      Author: Vallejo
 */

#ifndef TPM_H_
#define TPM_H_


/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       TPM.h
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
/*   1.0	    18/10/2015     AVR		add the init functions for FTM
 *   1.1	    28/11/2015     AVR		Move functions to servo app source.                                            							  */
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
#include "../mcl/CrystalClock.h"
#include "../mcl/GPIO.h"
#include "../app/DCMotors.h"
/* Exported types and constants */
/* ---------------------------- */

/* definition */
#define TPM_PLLFLL 					1U
#define TPM_OSCERCLK 				2U
#define TPM_MCGIRCLK				3U

#define	TPM_CNT_DIS					0U
#define	TPM_CLK						1U
#define	TPM_EXT_CLK					2U

/*preescaler definitions.*/
#define PS_1						0U
#define PS_2						1U
#define PS_4						2U
#define PS_8						3U
#define PS_16						4U
#define PS_32						5U
#define PS_64						6U
#define PS_128						7U

/*confuralbles bits for the TPM modules.*/
#define TPM_OC_TOGGLE				TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK
#define TPM_OC_CLR					TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_SET					TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTL					TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTH					TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK

#define TPM_PWM_H 					TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK /* PWM  with HIGH TRUE pulse. */
#define TPM_PWM_L					TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK /* PWM  with LOW  TRUE pulse. */

#define EDGE_PWM					(0U) 
#define CENTER_PWM					(1U)

#define RISING_CAPTURE				(TPM_CnSC_ELSA_MASK)		/* TPM2_INPUT_CAPTURE_MODE  */
#define FALLING_CAPTURE				(TPM_CnSC_ELSB_MASK)	    /* TPM2_INPUT_CAPTURE_MODE  */

/*Servo and dc motors to PWM control definitions*/
/*Based in the FRDM-TFC SHIELD 2014 schematics*/

#define SERVO_MOTOR_VALUE 			TPM1_C0V /* PTB0    */
#define LEDS_CAMERA_PWM				TPM1_C1V /* PTB1    */
#define MOTORB1_LEFT_VALUE			TPM0_C0V /* PTC1 B1 */
#define MOTORB2_LEFT_VALUE			TPM0_C1V /* PTC2 B2 */
#define MOTORA1_RIGHT_VALUE			TPM0_C2V /* PTC3 A1 */
#define MOTORA2_RIGHT_VALUE			TPM0_C3V /* PTC4 A2 */

#define TPM0_CLOCK					(CORE_CLOCK/2)
#define TPM0_CLK_PRESCALE           (0)  			// Prescale Selector value
#define TPM0_OVERFLOW_FREQUENCY 	(8000U) 		//Desired Frequency of PWM Signal 
#define TPM0_MODULE					(TPM0_CLOCK/(1<<TPM0_CLK_PRESCALE)/TPM0_OVERFLOW_FREQUENCY)
#define TPM0_PWM_UNIT				(TPM0_MODULE/200U)

#define TPM1_CLOCK					(24000000U)	//48000000/2
#define TPM1_CLK_PRESCALE			(6U) 			//divide by 64
#define TPM1_OVERFLOW_FREQUENCY 	(50U)			//Desired Frequency of PWM Signal - Here 50Hz => 20ms period 

#define SERVO_MIN_DUTY_CYCLE		(SERVO_MIN_us*(TPM1_CLOCK/(1U<<TPM1_CLK_PRESCALE)))/1000000U
#define SERVO_MAX_DUTY_CYCLE		(SERVO_MAX_us*(TPM1_CLOCK/(1U<<TPM1_CLK_PRESCALE)))/1000000U

//Modify these numbers to set the servo limits
#define SERVO_MIN_us				(1100U)
#define SERVO_MAX_us				(1900U)

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
void vfn_Init_SteeringServo_PTB0(void);
void vfn_Init_DCmotors(void);
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* TPM_H_ */
