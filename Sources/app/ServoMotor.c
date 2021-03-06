/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        Servo_Motor.c
* version:         1.0 
* created_by:      AVR
* date_created:    Nov 20, 2015
*=============================================================================*/
/* DESCRIPTION :                                                              */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |  AUTHOR  | Comment     						  */
/*----------------------------------------------------------------------------*/
//   1.0       20/10/2015    AVR		First revision.
//	 1.1       21/10/2015    AVR		Test the servo, function good.
//	 1.2       07/12/2015    AVR		Add functions to improve the servo stering.
//   1.3	   25/06/2016	 AVR		implement functions for use the push button to center the servo
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "ServoMotor.h"
/* Functions macros, constants, types and datas         */
/* Local Defines*/

/*Local Types*/

/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
int8_t sbyServoPosition;

/* Private functions prototypes */
/* ---------------------------- */
void vfn_SetPosition_SteeringServo(int8_t i8position);

/* Exported functions prototypes */
/* ----------------------------- */
void vfn_SteeringServoController(void);

/* Inline functions */
/* ---------------- */

/**************************************************************
 *  Name                 : vfn_SteeringServoController
 *  Description          : Function that contains the servo control 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_SteeringServoController(void)
{
	uint8_t ServoRepose;

	boolServoMotorRepose();
	
	ServoRepose = (ServoMotorIndStat_TYPE)TempCountButtonB;
	
	if((((sbyError - sbyErrorPrev) > ERROR_MAX) || ((sbyError - sbyErrorPrev) < ERROR_MIN))) 
	{
		sbyError = sbyErrorPrev;
	}
	
	if(ServoRepose == ServoNotRepose)
	{
		sbyServoPosition = sbyError;
	}
	
	if(ServoRepose == ServoInRopose)
	{
		sbyServoPosition = NO_ERROR;
	}
	
	//Saturation control
	if(sbyServoPosition > ERROR_MAX)
	{
		sbyServoPosition = ERROR_MAX;
	}
	if(sbyServoPosition < ERROR_MIN)
	{
		sbyServoPosition = ERROR_MIN;
	}
	
	vfn_SetPosition_SteeringServo(sbyServoPosition);
}
/**************************************************************
 *  Name                 : vfn_SetPosition_SteeringServo
 *  Description          : Set servo position 
 *  Parameters           : i8position, from -100 (max left) to +100 (max right)
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_SetPosition_SteeringServo(int8_t i8position)
{
	//Set the right value to servo timer
	SERVO_MOTOR_VALUE = ((((i8position+100)/2)*(SERVO_MAX_DUTY_CYCLE - SERVO_MIN_DUTY_CYCLE))/100)+SERVO_MIN_DUTY_CYCLE;
}



