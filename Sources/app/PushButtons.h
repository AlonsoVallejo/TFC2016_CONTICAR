/*
 * PushButtons.h
 *
 *  Created on: Jun 25, 2016
 *      Author: JAVR
 */

#ifndef PUSHBUTTONS_H_
#define PUSHBUTTONS_H_

/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
 * C Include:       PushButtons.h
 * version:         1.0 
 * created_by:      AVR
 * date_created:    Jun 25, 2016 
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
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
#include "../mcl/GPIO.h"
#include "../app/DCMotors.h"
#include "../app/LineScanCamera.h"
#include "../app/ServoMotor.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */

typedef enum
{
	DCmotorStopInd,
	DCmotorStartInd
}DCmotorIndStat_TYPE;

typedef enum
{
	ServoNotRepose,
	ServoInRopose
}ServoMotorIndStat_TYPE;
/*======================================================*/
/* Declaration of exported constants                    */
/*======================================================*/

/*======================================================*/
/* Definition of RAM variables                          */
/*======================================================*/
uint8_t TempCountButtonA;
uint8_t TempCountButtonB;
/*======================================================*/
/* close variable declaration sections                  */
/*======================================================*/

/* Exported functions prototypes and macros */
/* ---------------------------------------- */
void boolDcMotorStartCondition(void);
void boolServoMotorRepose(void);
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/

#endif /* PUSHBUTTONS_H_ */
