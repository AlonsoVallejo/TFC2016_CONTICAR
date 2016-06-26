/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        PushButtons.c
* version:         1.0 
* created_by:      AVR
* date_created:    Jun 25, 2016
*=============================================================================*/
/* DESCRIPTION :                                                              */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
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

#include "PushButtons.h"

/* Functions macros, constants, types and datas         */
/* Local Defines*/

/*Local Types*/
typedef enum
{
	buttonAisNotPressed,
	buttonAisPressed,
	buttonAwasPressed
}StatesButtonA_TYPE;

typedef enum
{
	buttonBisNotPressed,
	buttonBisPressed,
	buttonBwasPressed
}StatesButtonB_TYPE;

/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
uint8_t TempCountButtonA;
uint8_t TempCountButtonB;
/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
void boolDcMotorStartCondition(void);
void boolServoMotorRepose(void);

/**************************************************************
 *  Name                 : boolDcMotorStartCondition
 *  Description          : indicates if dc motors cam be start
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void boolDcMotorStartCondition(void)
{
	static uint8_t StatePushButtonA;
	static uint8_t ButtonAstate;
	
	StatePushButtonA = (StatesButtonA_TYPE)u8_PushButtonA_state();
	
	if(StatePushButtonA == buttonAisPressed)
	{
		ButtonAstate = buttonAwasPressed;
	}
	if(StatePushButtonA == buttonAisNotPressed) 
	{
		if(ButtonAstate == buttonAwasPressed)
		{
			ButtonAstate = buttonAisNotPressed;
			TempCountButtonA = TempCountButtonA + 1;
			if(TempCountButtonA == 2)
			{
				TempCountButtonA = 0;
			}
		}
	}
}

/**************************************************************
 *  Name                 : boolServoMotorRepose
 *  Description          : Put the sevo motor in central position
 *  					   by push button B request
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void boolServoMotorRepose(void)
{
	static uint8_t StatePushButtonB;
	static uint8_t ButtonBstate;
	
	StatePushButtonB = (StatesButtonB_TYPE)u8_PushButtonB_state();
	
	if(StatePushButtonB == buttonBisPressed)
	{
		ButtonBstate = buttonBwasPressed;
	}
	if(StatePushButtonB == buttonBisNotPressed) 
	{
		if(ButtonBstate == buttonBwasPressed)
		{
			ButtonBstate = buttonBisNotPressed;
			TempCountButtonB = TempCountButtonB + 1;
			if(TempCountButtonB == 2)
			{
				TempCountButtonB = 0;
			}
		}
	}
}

