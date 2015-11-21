/*
 * LineScanCamera.c
 *
 *  Created on: Oct 19, 2015
 *      Author: Vallejo
 */
/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        LineScanCamera.c
* version:         1.0 
* created_by:      AVR
* date_created:   Oct 19, 2015
*=============================================================================*/
/* DESCRIPTION :                                                              */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |  AUTHOR  | Comment     						  */
/*----------------------------------------------------------------------------*/
//    1.0       20/10/2015    AVR		Create the state machine for LSC,even not tested.
//    1.1       19/11/2015    AVR		added function to read the adc of Aout.
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "LineScanCamera.h"
/* Functions macros, constants, types and datas         */
/* Local Defines*/
#define LSC_firstPixel			0U
#define LSC_lastPixel			128U
#define TotalCLKrepetitions		260U
#define StoreLSC_Aout			linescancamera.adc_get_Aout[linescancamera.count_pixel]

/*Local Types*/
LineScanCamera linescancamera;

/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
uint8_t temp; /* Variable only used for Freemaster debug */

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */
void vfn_ReadAout_LineScanCamera(void);


/* Exported functions prototypes */
/* ----------------------------- */
void vfn_StateMachine_LSC_InSignals(void);

/* Inline functions */
/* ---------------- */



/**************************************************************
 *  Name                 : vfn_StateMachine_LSC_InSignals
 *  Description          : State Machine for get LSC Aout
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_StateMachine_LSC_InSignals(void) //state machine for generate the CLK and SI TAOS signals.
{
 switch(linescancamera.quarter_period_count)
	{
	case START_SILOW_CLKLOW:
		CAMERA_SI_LOW;
		CAMERA_CLK_LOW;
		linescancamera.quarter_period_count = 1U;
		break;
	case SIHIGH_CLKLOW:
		CAMERA_SI_HIGH;
		CAMERA_CLK_LOW;
		linescancamera.quarter_period_count = 2U;
		break;
	case SIHIGH_CLKHIGH:
		CAMERA_SI_HIGH;
		CAMERA_CLK_HIGH;
		linescancamera.quarter_period_count = 3U;
		break;
	case SILOW_CLKHIGH:
		CAMERA_SI_LOW;
		CAMERA_CLK_HIGH;
		linescancamera.quarter_period_count = 4U;
		break;
	case FINISH_SILOW_CLKLOW:
		CAMERA_SI_LOW;
		CAMERA_CLK_LOW;
		linescancamera.quarter_period_count = 5U;
		linescancamera.count_pixel = LSC_firstPixel;
		break;
	default:
		if((linescancamera.quarter_period_count) <= (TotalCLKrepetitions))
		{
			switch(linescancamera.count_CLK_pulse)
			{
			case LSC_CLK_HIGH:
				CAMERA_CLK_HIGH;
				vfn_ReadAout_LineScanCamera();
				linescancamera.quarter_period_count++;
				linescancamera.count_pixel = linescancamera.count_pixel + 1U;
				if(linescancamera.count_pixel >= LSC_lastPixel) linescancamera.count_pixel = LSC_lastPixel;
				linescancamera.count_CLK_pulse = LSC_CLK_LOW;
				break;
			case LSC_CLK_LOW:
				CAMERA_CLK_LOW;
				linescancamera.quarter_period_count++;
				linescancamera.count_CLK_pulse = LSC_CLK_HIGH;
				break;
			}
		}
		else linescancamera.quarter_period_count = START_SILOW_CLKLOW;
	}
}

/**************************************************************
 *  Name                 : vfn_ReadAout_LineScanCamera
 *  Description          : Read the ADC output of LSC
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_ReadAout_LineScanCamera(void)
{
	StoreLSC_Aout = u8_adc0_readAoutCamera0();
	temp = StoreLSC_Aout;
}

