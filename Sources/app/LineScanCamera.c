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
//    1.2       21/11/2015    AVR		added functions for image processing and function to get the error
//	  1.3	    05/12/2015    AVR		change the adc bits resolution, filtering deriv. signal, add function map
//	  1.4	    06/12/2015    AVR		change to void some functions
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "LineScanCamera.h"
/* Functions macros, constants, types and datas         */
/* Local Defines*/
#define LSC_firstPixel					0U
#define LSC_lastPixel					128U
#define LSC_TotalPixels					128U
#define TotalCLKrepetitions				260U
#define CurrentPixel					linescancamera.count_pixel
#define MinPixelLSCConsider				40U		/* Min pixel number consider for control */
#define MaxPixelLSCConsider				93U	    /* Max pixel number consider for control */
#define MinPixelLSCConsiderDrtv			20U		/* Min pixel number consider for get the derivative signal*/
#define MaxPixelLSCConsiderDrtv			100U	/* Max pixel number consider for get the derivative signal*/
#define MinPixelLSCConsiderAout			0U
#define MaxPixelLSCConsiderAout			128U
#define CentralPixelLSC					64U

/*Local Types*/
LineScanCamera linescancamera;

/* ---------------------------------------------------- */
/* Functions macros */
#define StoreLSC_Aout(position)			 				linescancamera.adc_get_Aout[position]
#define StoreDerivateAout(position)		 				linescancamera.lsc_Aout_derivate[position]
#define FilterDrtvSingal(Reference,Min,Max) 			(Reference >= Min && Reference <= Max)
#define SeparationBetweenMaxMinDrtvPoint(Ref,Separ)		( Ref > Separ)
/* Utility Functions*/

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
uint8_t ubyTempLineScanCameraAoutValue; 		/* Variable only used for Freemaster debug */
uint16_t s16_TempGetCurrentValueDerivativeAout; /* Variable only used for Freemaster debug */

/* RAM variables uses for image processing */
uint16_t  u16StoreMaxValReadAdcAout; 
uint16_t  u16StoreMinValReadAdcAout;
uint8_t	  ubyLineLocationPoint_MinValue;
uint8_t	  ubyLineLocationPoint_MaxValue;
int16_t   s16StoreMaxValReadDertvSignal; 
int16_t   s16StoreMinValReadDertvSignal;
int16_t   i16Differece_MinValDrtv_MaxValDrtv;

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
void vfn_GetLineLocationValue_DerivateSignal(uint8_t MinPixelConsider, uint8_t MaxPixelConside);
void void_GetLineLocationValue_AoutSignal(uint8_t MinPixelConsider, uint8_t MaxPixelConside);
int8_t map(int8_t x, int8_t in_min, int8_t in_max, int8_t out_min, int8_t out_max);

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
void vfn_StateMachine_LSC_InSignals(void)
{
 switch(linescancamera.quarter_period_count)
	{
	case START_SYNC_SIGNALS:
		CAMERA_SI_LOW;
		CAMERA_CLK_LOW;
		linescancamera.quarter_period_count = SIHIGH_CLKLOW;
		break;
	case SIHIGH_CLKLOW:
		CAMERA_SI_HIGH;
		CAMERA_CLK_LOW;
		linescancamera.quarter_period_count = SIHIGH_CLKHIGH;
		break;
	case SIHIGH_CLKHIGH:
		CAMERA_SI_HIGH;
		CAMERA_CLK_HIGH;
		linescancamera.quarter_period_count = SILOW_CLKHIGH;
		break;
	case SILOW_CLKHIGH:
		CAMERA_SI_LOW;
		CAMERA_CLK_HIGH;
		linescancamera.quarter_period_count = SILOW_CLKLOW;
		break;
	case SILOW_CLKLOW:
		CAMERA_SI_LOW;
		CAMERA_CLK_LOW;
		linescancamera.quarter_period_count = FINISH_SYNC_SIGNALS;
		linescancamera.count_pixel = LSC_firstPixel;
		break;
	case FINISH_SYNC_SIGNALS:
		if((linescancamera.quarter_period_count) <= (TotalCLKrepetitions))
		{
			switch(linescancamera.CLK_STATE)
			{
			case LSC_CLK_HIGH:
				CAMERA_CLK_HIGH;
				vfn_ReadAout_LineScanCamera();
				linescancamera.quarter_period_count++;
				linescancamera.count_pixel = linescancamera.count_pixel + 1U;
				if(CurrentPixel == LSC_lastPixel)
				{
					linescancamera.count_pixel = LSC_lastPixel;
				}
				linescancamera.CLK_STATE = LSC_CLK_LOW;
				break;
			case LSC_CLK_LOW:
				CAMERA_CLK_LOW;
				linescancamera.quarter_period_count++;
				linescancamera.CLK_STATE = LSC_CLK_HIGH;
				break;
			}
		}
		else linescancamera.quarter_period_count = START_SYNC_SIGNALS;
	default:
	{
		/* Do nothing */
	}
	
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
	StoreLSC_Aout(CurrentPixel) = u10_adc0_readAoutCamera0();
}

/**************************************************************
 *  Name                 : vfn_LineScanCameraProcessing
 *  Description          : Get a value between (-100,100) depending
 *  					   of the position of black lines and store
 *  					   in sbyError.
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_LineScanCameraProcessing(void)
{
	vfn_GetDerivateSingal_lscAout();
	
	vfn_GetLineLocationValue_DerivateSignal(MinPixelLSCConsiderDrtv, MaxPixelLSCConsiderDrtv);
	
	sbyErrorPrev = sbyError;
	
	if(ubyLineLocationPoint_MaxValue <= MinPixelLSCConsider || ubyLineLocationPoint_MaxValue >= MaxPixelLSCConsider)
	{
		sbyError = sbyErrorPrev;
	}
	else if(ubyLineLocationPoint_MaxValue >= CentralPixelLSC) /* Left turn control algorithm */
	{
		sbyError = map(ubyLineLocationPoint_MinValue,CentralPixelLSC,MaxPixelLSCConsider,ErrorMin,NoError); 
	}
	else /* Right turn control algorithm */
	{
		sbyError = map(ubyLineLocationPoint_MaxValue,MinPixelLSCConsider,CentralPixelLSC,NoError,ErrorMax);
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
		
		/* Filtering process */
		if( FilterDrtvSingal(StoreDerivateAout(ubytempCount),-5,5) )
		{
			StoreDerivateAout(ubytempCount) = 0;
		}
		if( ubytempCount < MinPixelLSCConsiderDrtv || ubytempCount > MaxPixelLSCConsiderDrtv)
		{
			StoreDerivateAout(ubytempCount) = 0;
		}
	}
}

/******************************************************************************************************************
 *  Name                 : vfn_GetLineLocationValue_AoutSignal(uint8_t MinPixelConsider, uint8_t MaxPixelConsider)
 *  Description          : get the smallest and biggest value on array StoreLSC_Aout with the range indacated,
 *  					   also find the pixel in that is located the edge black line.
 *  Parameters           : MinPixelConsider: First Pixel of the range
 *  					   MaxPixelConsider: Last Pixel of the range
 *  Return               : Pixel in where is located the edge line
 *  Critical/explanation : No
 *******************************************************************************************************************/
void vfn_GetLineLocationValue_AoutSignal(uint8_t MinPixelConsider, uint8_t MaxPixelConsider)
{
	uint8_t ubytempCount;
	u16StoreMaxValReadAdcAout = MinValueADC;
	u16StoreMinValReadAdcAout = MaxValueADC;
	
	for(ubytempCount = MinPixelConsider;ubytempCount <= MaxPixelConsider;ubytempCount++)
	{
		if(u16StoreMaxValReadAdcAout < StoreLSC_Aout(ubytempCount)) 
		{
			u16StoreMaxValReadAdcAout = StoreLSC_Aout(ubytempCount);
			ubyLineLocationPoint_MaxValue = ubytempCount;
		}
		else if(u16StoreMinValReadAdcAout > StoreLSC_Aout(ubytempCount))
		{
			u16StoreMinValReadAdcAout = StoreLSC_Aout(ubytempCount);
			ubyLineLocationPoint_MinValue = ubytempCount;
		}
	}
}


/******************************************************************************************************************
 *  Name                 : vfn_GetLineLocationValue_DerivateSignal(uint8_t MinPixelConsider, uint8_t MaxPixelConsider)
 *  Description          : get the smallest and biggest value on array StoreDerivateAout with the range indacated,
 *  					   also find the pixel in that is located the edge black line.
 *  Parameters           : MinPixelConsider: First Pixel of the range
 *  					   MaxPixelConsider: Last Pixel of the range
 *  Return               : Pixel in where is located the edge line
 *  Critical/explanation : No
 *******************************************************************************************************************/
void vfn_GetLineLocationValue_DerivateSignal(uint8_t MinPixelConsiderDer, uint8_t MaxPixelConsideDer)
{
	uint8_t ubytempCount;
	s16StoreMaxValReadDertvSignal = MinDerivativeValue;
	s16StoreMinValReadDertvSignal = MaxDerivativeValue;
	
	for(ubytempCount = MinPixelConsiderDer;ubytempCount <= MaxPixelConsideDer;ubytempCount++)
	{
		if(s16StoreMaxValReadDertvSignal < StoreDerivateAout(ubytempCount)) 
		{
			s16StoreMaxValReadDertvSignal = StoreDerivateAout(ubytempCount);
			ubyLineLocationPoint_MaxValue = ubytempCount;
		}
		else if(s16StoreMinValReadDertvSignal > StoreDerivateAout(ubytempCount))
		{
			s16StoreMinValReadDertvSignal = StoreDerivateAout(ubytempCount);
			ubyLineLocationPoint_MinValue = ubytempCount;
		}
	}
	
	i16Differece_MinValDrtv_MaxValDrtv = ubyLineLocationPoint_MaxValue - ubyLineLocationPoint_MinValue;
	if( SeparationBetweenMaxMinDrtvPoint(i16Differece_MinValDrtv_MaxValDrtv,10) ) 
	{
		ubyLineLocationPoint_MaxValue = NO_LINE_DETECTED;
	}
}

/**********************************************************************************************************
 *  Name                 : map(int8_t x, int8_t in_min, int8_t in_max, int8_t out_min, int8_t out_max)
 *  Description          : map values, Thanks Arduino :D 
 *  Parameters           : int8_t x, int8_t in_min, int8_t in_max, int8_t out_min, int8_t out_max
 *  Return               : value mapped
 *  Critical/explanation : No
 **********************************************************************************************************/
int8_t map(int8_t x, int8_t in_min, int8_t in_max, int8_t out_min, int8_t out_max)
{
  return (x - in_min) * (out_max - out_min + 1) / (in_max - in_min + 1) + out_min;
}
