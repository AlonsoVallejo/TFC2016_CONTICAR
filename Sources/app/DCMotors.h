/*
 * DCMotors.h
 *
 *  Created on: Jun 18, 2016
 *      Author: JAVR
 */

#ifndef DCMOTORS_H_
#define DCMOTORS_H_

/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
 * C Include:       DCMotors.h
 * version:         1.0 
 * created_by:      AVR
 * date_created:    Jun 18, 2016 
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
//	  1.0	 	18/06/2016		AVR		first Version
//	  1.1		25/06/2016		AVR		Implmentet algorithm for speed control                                       							  */
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
#include "../mcl/GPIO.h"
#include "../mcl/TPM.h"
#include "../mcl/ADC.h"
#include "../app/LineScanCamera.h"
#include "../app/ServoMotor.h"
#include "../app/PushButtons.h"
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
void vfn_DCmotors_task(void);
void vfn_DCMotorsSetPWM(int8_t i8MotorApwm, int8_t i8MotorBpwm);
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/

#endif /* DCMOTORS_H_ */
