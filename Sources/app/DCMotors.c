/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        DCMotors.c
* version:         1.0 
* created_by:      AVR
* date_created:    Jun 18, 2016
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
//	  1.1		25/06/2016		AVR		Implmentet algorithm for speed control
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "DCMotors.h"
/* Functions macros, constants, types and datas         */
/* Local Defines*/

/*Local Types*/
typedef enum
{
	SPEED_1,
	SPEED_2,
	SPEED_3,
	SPEED_4
}DipSwitchUsageSpeedSelector_TYPE;

/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
float speedup, speeddown;
uint8_t MaxPWMvalueForCurves;
uint8_t MaxPWMvalueForStraight;
int8_t sbyDCerror;
uint8_t i8SetPointMotorpwm;
uint8_t i8SetPointMotorApwm;
uint8_t i8SetPointMotorBpwm;
uint8_t i8StatStopInd;

uint16_t tempadc;
/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
#define LEDS_VEL_STATE_1_INDICATOR		LEDS_VEL_STATE_1_ON ; \
										LEDS_VEL_STATE_2_OFF; \
										LEDS_VEL_STATE_3_OFF; \
										LEDS_VEL_STATE_4_OFF; 

#define LEDS_VEL_STATE_2_INDICATOR		LEDS_VEL_STATE_1_OFF; \
										LEDS_VEL_STATE_2_ON ; \
										LEDS_VEL_STATE_3_OFF; \
										LEDS_VEL_STATE_4_OFF; 

#define LEDS_VEL_STATE_3_INDICATOR		LEDS_VEL_STATE_1_OFF; \
										LEDS_VEL_STATE_2_OFF; \
										LEDS_VEL_STATE_3_ON ; \
										LEDS_VEL_STATE_4_OFF; 

#define LEDS_VEL_STATE_4_INDICATOR		LEDS_VEL_STATE_1_OFF; \
										LEDS_VEL_STATE_2_OFF; \
										LEDS_VEL_STATE_3_OFF; \
										LEDS_VEL_STATE_4_ON;  

#define MIN_MOTOR_PWM_FORWAR_VALUE		0
#define MAX_MOTOR_PWM_FORWARD_VALUE		100
#define MAX_MOTOR_PWM_BACKWARD_VALUE	-100
#define DCMOTOR_NO_ERROR_VALUE			NO_ERROR
#define DCMOTOR_MAX_ERROR_VALUE			ERROR_MAX

#define KP_PROPORTIONAL_FOR_DCMOTOR_A	0.5
#define	KP_PROPORTIONAL_FOR_DCMOTOR_B	0.5

#define DIPSW_USAGE_SELECTORS_3_4		(u16_DipSW_val() & 0xC) >> 2
/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
void vfn_DCmotors_task(void);
void vfn_DCMotorsSetPWM(int8_t i8MotorApwm, int8_t i8MotorBpwm);
void vfn_ControlAppSpeedAlgorit_DCMotors(void);
void vfn_DipSwitchSetSpeedParameter(void);
void vfn_utilityFnToReadBattVol(void);
/**************************************************************
 *  Name                 : void vfn_DCmotors_task(void)
 *  Description          : Container of all functions that allow 
 *  					   dc motors control.
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_DCmotors_task(void)
{
	/* Select differents speeds using DIP switch buttion 3 and 4 */
	vfn_DipSwitchSetSpeedParameter();
	
	/* Algorithm for speed PWM output application control */
	vfn_ControlAppSpeedAlgorit_DCMotors();
	
	/* Final function for write a PWM output in DC motors*/
	vfn_DCMotorsSetPWM(i8SetPointMotorApwm, i8SetPointMotorBpwm);
	
	/* indicate batt voltage */
	vfn_utilityFnToReadBattVol();
}

/**************************************************************
 *  Name                 : void vfn_DipSwitchSetSpeedParameter(void)
 *  Description          : using DIP sw set the speed parameters
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_DipSwitchSetSpeedParameter(void)
{
    switch ((DipSwitchUsageSpeedSelector_TYPE)DIPSW_USAGE_SELECTORS_3_4) 
     {
     		case SPEED_1:
     			 //LEDS_VEL_STATE_1_INDICATOR
                 MaxPWMvalueForStraight = 10 ;
                 speeddown 				= 0.5;
                 speedup 				= 0.5;
                 break;                                  
             case SPEED_2:
            	//LEDS_VEL_STATE_2_INDICATOR
             	MaxPWMvalueForStraight  = 20 ;
             	speeddown 				= 0.6;
             	speedup 				= 0.6;
             	break;                         
             case SPEED_3:
            	//LEDS_VEL_STATE_3_INDICATOR
             	MaxPWMvalueForStraight	= 30 ;
             	speeddown 				= 0.7;
             	speedup 				= 0.7;
             	break;                        
             case SPEED_4:
            	//LEDS_VEL_STATE_4_INDICATOR
             	MaxPWMvalueForStraight 	= 40 ;
             	speeddown 				= 0.9;
             	speedup 				= 0.9;
             	break;                      
             default:
              	MaxPWMvalueForStraight 	= 0.9;
              	speeddown 				= 0.1;
              	speedup 				= 0.1;
             	break;
     }
}

/**************************************************************************
 *  Name                 : void vfn_ControlAppSpeedAlgorit_DCMotors(void)
 *  Description          : Contains the main algorithm for control
 *  					   the speed of DC motors using application.
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************************/
void vfn_ControlAppSpeedAlgorit_DCMotors(void)
{
	sbyDCerror = sbyError;
	
	boolDcMotorStartCondition();
	
	i8StatStopInd = (DCmotorIndStat_TYPE)TempCountButtonA;
	
	/* Obtain only the absolute value of the error value */
	if(sbyDCerror < NO_ERROR)
	{
		sbyDCerror = sbyDCerror * -1;
	}
	
	/* Convert values for PWM control (0,100) to (100, 0)*/
	i8SetPointMotorpwm = (uint8_t) map(sbyDCerror,DCMOTOR_NO_ERROR_VALUE, DCMOTOR_MAX_ERROR_VALUE, MAX_MOTOR_PWM_FORWARD_VALUE, MIN_MOTOR_PWM_FORWAR_VALUE);
	
	if(i8StatStopInd == DCmotorStartInd)
	{
		/* yes, I know that the condition looks weird, but i dont know a better solution :( */
		if(sbyError <= MIN_MOTOR_PWM_FORWAR_VALUE) /* if the car is turning to right */
		{
			/* Left wheel shall be faster than right wheel */
			/* Set final PWM output for each motor */
			i8SetPointMotorApwm = i8SetPointMotorpwm * speeddown;
			i8SetPointMotorBpwm = i8SetPointMotorpwm * speedup;
		}
		else /* If the car is turning to left */
		{
			/* Right wheel shall be faster than left wheel */
			/* Set final PWM output for each motor */
			i8SetPointMotorApwm = i8SetPointMotorpwm * speedup;
			i8SetPointMotorBpwm = i8SetPointMotorpwm * speeddown;
		}
	}
	
	/* Stop the car using push button A */
	if(i8StatStopInd == DCmotorStopInd)
	{
		i8SetPointMotorApwm = MIN_MOTOR_PWM_FORWAR_VALUE;
		i8SetPointMotorBpwm = MIN_MOTOR_PWM_FORWAR_VALUE;
	}
	
	/* Saturation Control */
	if( i8SetPointMotorApwm > MAX_MOTOR_PWM_FORWARD_VALUE)
	{
		i8SetPointMotorApwm = MAX_MOTOR_PWM_FORWARD_VALUE;
	}
	
	if(i8SetPointMotorBpwm > MAX_MOTOR_PWM_FORWARD_VALUE)
	{
		i8SetPointMotorBpwm = MAX_MOTOR_PWM_FORWARD_VALUE;
	}
}
/*********************************************************************************************
 * Function name: 	vfnMotorsSetPWM
 * Description: 	Set the PWM command of the motors.
 * Parameters: 		i8MotorApwm, motor A PWM from -100 (max backward) and +100 (max forward)
 * 					i8MotorBpwm, motor B PWM from -100 (max backward) and +100 (max forward)
 * Return value:	none
*********************************************************************************************/

void vfn_DCMotorsSetPWM(int8_t i8MotorApwm, int8_t i8MotorBpwm)
{
	//Saturation control
	if( i8MotorApwm > MAX_MOTOR_PWM_FORWARD_VALUE)
	{
		i8MotorApwm = MAX_MOTOR_PWM_FORWARD_VALUE;
	}
	else if(i8MotorApwm < MAX_MOTOR_PWM_BACKWARD_VALUE)
	{
		i8MotorApwm = MAX_MOTOR_PWM_BACKWARD_VALUE;
	}
	
	if(i8MotorBpwm > MAX_MOTOR_PWM_FORWARD_VALUE)
	{
		i8MotorBpwm = MAX_MOTOR_PWM_FORWARD_VALUE;
	}
	else if(i8MotorBpwm < MAX_MOTOR_PWM_BACKWARD_VALUE)
	{
		i8MotorBpwm = MAX_MOTOR_PWM_BACKWARD_VALUE;
	}
	
/*	tempadc = u10_adc0_readPOT1_shield();
	
	if(tempadc >= 100)
	{
		tempadc = 100;
	}
	i8MotorApwm = tempadc;
	i8MotorBpwm = tempadc;*/
	
	//Set the servo timer to the right value
	MOTORA1_RIGHT_VALUE = (uint16_t)(TPM0_PWM_UNIT * (i8MotorApwm + MAX_MOTOR_PWM_FORWARD_VALUE));
	MOTORA2_RIGHT_VALUE = MOTORA1_RIGHT_VALUE;//complimentary output!
	MOTORB1_LEFT_VALUE  = (uint16_t)(TPM0_PWM_UNIT * (i8MotorBpwm + MAX_MOTOR_PWM_FORWARD_VALUE));
	MOTORB2_LEFT_VALUE  = MOTORB1_LEFT_VALUE;//complimentary output!
}

/*********************************************************************************************
 * Function name: 	vfn_utilityFnToReadBattVol
 * Description: 	utility for batt voltage
 * Return value:	none
*********************************************************************************************/
void vfn_utilityFnToReadBattVol(void)
{
	vfn_LEDs_ctrl_BattLevel_LEDs(); /* To read the batt voltage */
}
