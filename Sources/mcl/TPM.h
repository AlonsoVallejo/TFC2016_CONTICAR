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
/*   1.0	    18/10/2015     AVR		add the init functions for FTM                                             							  */
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
#include "CrystalClock.h"
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
void vfn_Init_SteeringServo_PTB0(void);
void vfn_Init_DCmotors(void);
void vfn_SetPosition_SteeringServo(int8_t i8position);
void vfn_Set_RightMotors_PWM(uint8_t u8MotorA1pwm, uint8_t u8MotorA2pwm);
void vfn_Set_LeftMotors_PWM(uint8_t u8MotorB1pwm, uint8_t u8MotorB2pwm);

/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* TPM_H_ */
