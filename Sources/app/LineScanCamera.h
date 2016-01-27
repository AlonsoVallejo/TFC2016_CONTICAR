/*
 * LineScanCamera.h
 *
 *  Created on: Oct 19, 2015
 *      Author: Vallejo
 */

#ifndef LINESCANCAMERA_H_
#define LINESCANCAMERA_H_

/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
 * C Include:       LineScanCamera.h
 * version:         1.0 
 * created_by:      AVR
 * date_created:    Oct 19, 2015 
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
//    1.0       20/10/2015    AVR		Create the state machine for LSC,even not tested.
//    1.1       19/11/2015    AVR		added function to read the adc of Aout.
//    1.2       21/11/2015    AVR		added functions for image processing (not tested).
//	  1.3	    05/12/2015    AVR		change the adc bits resolution.   
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
#include "../Sources/mcl/GPIO.h"
#include "../Sources/mcl/ADC.h"
/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
typedef enum {
	START_SYNC_SIGNALS,
	SIHIGH_CLKLOW,
	SIHIGH_CLKHIGH,
	SILOW_CLKHIGH,
	SILOW_CLKLOW,
	FINISH_SYNC_SIGNALS
} LineScanSyscSignals;

typedef enum {
	LSC_CLK_HIGH, 
	LSC_CLK_LOW,
} LineScanCLKsignals;

typedef enum{
	MaxValueADC = 1024U,
	MinValueADC = 0U,
}ADC_Range;

typedef enum{
	MaxDerivativeValue = 1024,
	MinDerivativeValue = -1024,		
}DerivativeSignalRangeValues;

typedef enum {
	NO_LINE_DETECTED,
}NoLineDetected;


typedef struct {
	uint16_t quarter_period_count;
	uint8_t  CLK_STATE;
	uint8_t  count_pixel;
	uint16_t  adc_get_Aout[128U];
	int16_t   lsc_Aout_derivate[128U];
} LineScanCamera;

/*======================================================*/
/* Declaration of exported constants                    */
/*======================================================*/
#define ErrorMin						-100
#define ErrorMax						100
#define	NoError							0
/*======================================================*/
/* Definition of RAM variables                          */
/*======================================================*/
extern int8_t sbyError;
extern int8_t sbyErrorPrev;
/*======================================================*/
/* close variable declaration sections                  */
/*======================================================*/

/* Exported functions prototypes and macros */
/* ---------------------------------------- */
void vfn_StateMachine_LSC_InSignals(void);
void vfn_LineScanCameraProcessing(void);
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* LINESCANCAMERA_H_ */
