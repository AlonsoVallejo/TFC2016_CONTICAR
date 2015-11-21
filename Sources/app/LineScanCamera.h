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
/*                                               							  */
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
	START_SILOW_CLKLOW,
	SIHIGH_CLKLOW,
	SIHIGH_CLKHIGH,
	SILOW_CLKHIGH,
	FINISH_SILOW_CLKLOW,
} LineScanSyscSignals;

typedef enum {
	LSC_CLK_HIGH, 
	LSC_CLK_LOW,
} LineScanCLKsignals;

typedef struct {
	uint16_t quarter_period_count;
    uint16_t count_CLK_pulse;
	uint16_t count_pixel;
	uint16_t adc_get_Aout[128U];
} LineScanCamera;

/*======================================================*/
/* Declaration of exported constants                    */
/*======================================================*/

/*======================================================*/
/* Definition of RAM variables                          */
/*======================================================*/

/*======================================================*/
/* close variable declaration sections                  */
/*======================================================*/

/* Exported functions prototypes and macros */
/* ---------------------------------------- */
void vfn_StateMachine_LSC_InSignals(void);
/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* LINESCANCAMERA_H_ */
