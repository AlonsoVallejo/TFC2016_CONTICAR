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

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

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
	
	/*TODO: PID controller for the servo*/
	
	if((((sbyError - sbyErrorPrev) > ErrorMax) || ((sbyError - sbyErrorPrev) < ErrorMin))) 
	{
		sbyError = sbyErrorPrev;
	}
	
	sbyServoPosition = sbyError;
	
	//Saturation control
	if(sbyServoPosition > ErrorMax)
	{
		sbyServoPosition = ErrorMax;
	}
	if(sbyServoPosition < ErrorMin)
	{
		sbyServoPosition = ErrorMin;
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



