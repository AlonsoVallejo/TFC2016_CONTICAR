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
} LineScanSyscSignalsTYPE;

typedef enum {
	LSC_CLK_HIGH, 
	LSC_CLK_LOW,
} LineScanCLKsignalsTYPE;

typedef enum{
	MaxValueADC = 1024U,
	MinValueADC = 0U,
}ADC_RangeTYPE;

typedef enum{
	MaxDerivativeValue = 1024,
	MinDerivativeValue = -1024,		
}DerivativeSignalRangeValuesTYPE;

typedef struct {
	uint16_t quarter_period_count;
	uint8_t  CLK_STATE;
	uint8_t  count_pixel;
	uint16_t adc_get_Aout[128U];
	int16_t  lsc_Aout_derivate[128U];
} LineScanCameraTYPE;

/*======================================================*/
/* Declaration of exported constants                    */
/*======================================================*/
#define ERROR_MIN						-100
#define ERROR_MAX						100
#define	NO_ERROR						0
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
int8_t map(int8_t x, int8_t in_min, int8_t in_max, int8_t out_min, int8_t out_max);
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* LINESCANCAMERA_H_ */
