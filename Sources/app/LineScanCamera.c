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
//    1.2       21/11/2015    AVR		added functions for image processing and function to get the error(not tested).
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "LineScanCamera.h"
/* Functions macros, constants, types and datas         */
/* Local Defines*/
#define LSC_firstPixel					0U
#define LSC_lastPixel					128U
#define TotalCLKrepetitions				260U
#define CurrentPixel					linescancamera.count_pixel
#define MinPixelLSCConsider				15U
#define MaxPixelLSCConsider				115U
#define CentralPixelLSC					64U
#define ErrorMin						-100
#define ErrorMax						100
					
/*Local Types*/
LineScanCamera linescancamera;

/* ---------------------------------------------------- */
/* Functions macros */
#define StoreLSC_Aout(position)			 				linescancamera.adc_get_Aout[position]
#define StoreDerivateAout(position)		 				linescancamera.lsc_Aout_derivate[position]
#define ThresholdCrossingsRange(Reference,Min,Max) 		(Reference >= Min && Reference <= Max)
#define mapValues(value,fromLow,fromHigh,toLow,toHigh)  ((value - fromLow) * (toHigh - toLow + 1) / (fromHigh - fromLow + 1) + toLow)
/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
uint8_t temp; /* Variable only used for Freemaster debug */

/* RAM variables uses for image processing */
uint8_t ubyStoreMaxValReadAdcAout; 
uint8_t ubyStoreMinValReadAdcAout;
uint8_t	ubyLineLocationPoint;
int8_t  sbyGetPromedyDerSignal;

/* RAM variables uses for Control algorithm of LSC */
int8_t sbyError;
int8_t sbyErrorPrev;
/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */
void vfn_ReadAout_LineScanCamera(void);
void vfn_GetDerivateSingal_lscAout(void);
int8_t s8_GetLineLocationValue_DerivateSiganl(uint8_t MinPixelConsider, uint8_t MaxPixelConside);

/* Exported functions prototypes */
/* ----------------------------- */
void vfn_StateMachine_LSC_InSignals(void);
void vfn_LineScanCameraProcessing(void);
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
			switch(linescancamera.CLK_STATE)
			{
			case LSC_CLK_HIGH:
				CAMERA_CLK_HIGH;
				vfn_ReadAout_LineScanCamera();
				linescancamera.quarter_period_count++;
				linescancamera.count_pixel = linescancamera.count_pixel + 1U;
				if(CurrentPixel >= LSC_lastPixel) linescancamera.count_pixel = LSC_lastPixel;
				linescancamera.CLK_STATE = LSC_CLK_LOW;
				break;
			case LSC_CLK_LOW:
				CAMERA_CLK_LOW;
				linescancamera.quarter_period_count++;
				linescancamera.CLK_STATE = LSC_CLK_HIGH;
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
	StoreLSC_Aout(CurrentPixel) = u8_adc0_readAoutCamera0();
	temp = StoreLSC_Aout(CurrentPixel);
}

/**************************************************************
 *  Name                 : vfn_LineScanCameraProcessing
 *  Description          : Process the array of LSC Aout using
 *  					   a derivate processing.
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_LineScanCameraProcessing(void)
{
	vfn_GetDerivateSingal_lscAout();
	
	(void)s8_GetLineLocationValue_DerivateSiganl(MinPixelLSCConsider, MaxPixelLSCConsider);
	
	if(ubyLineLocationPoint <= MinPixelLSCConsider || ubyLineLocationPoint >= MaxPixelLSCConsider)
	{
		sbyError = sbyErrorPrev;
	}
	else if(ubyLineLocationPoint >= CentralPixelLSC)
	{
		sbyError = (MaxPixelLSCConsider - ubyLineLocationPoint) * (ErrorMin/(MaxPixelLSCConsider - CentralPixelLSC));
	}
	else
	{
		sbyError = (ubyLineLocationPoint - MinPixelLSCConsider) * (ErrorMax / (CentralPixelLSC - MinPixelLSCConsider));
	}
	
	if(ThresholdCrossingsRange(ubyLineLocationPoint,-5,5)) 
	{
		sbyError = sbyErrorPrev;
	}
}

/**************************************************************
 *  Name                 : vfn_GetDerivateSingal_lscAout();
 *  Description          : Get the Derivative of Aout LSC
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_GetDerivateSingal_lscAout(void)
{
	uint8_t ubytempCount;
	
	for(ubytempCount = LSC_firstPixel;ubytempCount <= LSC_lastPixel;ubytempCount++)
	{
		StoreDerivateAout(ubytempCount) = linescancamera.adc_get_Aout[ubytempCount + 1U] - linescancamera.adc_get_Aout[ubytempCount - 1U];
		sbyGetPromedyDerSignal = sbyGetPromedyDerSignal + StoreDerivateAout(ubytempCount); 
	}
}

/******************************************************************************************************************
 *  Name                 : s8_GetLineLocationValue_DerivateSiganl(uint8_t MinPixelConsider, uint8_t MaxPixelConsider)
 *  Description          : get the smallest and biggest value on array StoreDerivateAout with the range indacated,
 *  					   also find the pixel in that is located the edge black line(each one time)
 *  Parameters           : MinPixelConsider: First Pixel of the range
 *  					   MaxPixelConsider: Last Pixel of the range
 *  Return               : Pixel in where is located the edge line
 *  Critical/explanation : No
 *******************************************************************************************************************/
int8_t s8_GetLineLocationValue_DerivateSiganl(uint8_t MinPixelConsider, uint8_t MaxPixelConside)
{
	uint8_t ubytempCount;
	ubyStoreMaxValReadAdcAout = MinValueADC;
	ubyStoreMinValReadAdcAout = MaxValueADC;
	
	for(ubytempCount = MinPixelConsider;ubytempCount <= MaxPixelConside;ubytempCount++)
	{
		if(ubyStoreMaxValReadAdcAout < StoreDerivateAout(ubytempCount)) 
		{
			ubyStoreMaxValReadAdcAout = StoreDerivateAout(ubytempCount);
		}
		else if(ubyStoreMinValReadAdcAout > StoreDerivateAout(ubytempCount))
		{
			ubyStoreMinValReadAdcAout = StoreDerivateAout(ubytempCount);
			ubyLineLocationPoint = ubytempCount;
		}
	}
}

