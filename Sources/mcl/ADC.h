/*
 * ADC.h
 *
 *  Created on: Oct 18, 2015
 *      Author: Vallejo
 */

#ifndef ADC_H_
#define ADC_H_


/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:       ADC.h
* version:         1.0 
* created_by:      AVR
* date_created:    Oct 18, 2015 
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
/*   1.0	    18/10/2015     AVR		add the init functions for adc.
 *   1.1	    20/10/2015     AVR		add functions to read the pots and IFB.
 *   1.2	    05/12/2015     AVR		change the adc bits resolution.                                                							  */
/*============================================================================*/
/*============================================================================*/

/* Includes */
/* -------- */
#include "stdtypedef.h"
#include "derivative.h"
/* Exported types and constants */
/* ---------------------------- */

/* Types definition */



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
void vfn_init_adc0 (void)							;
volatile uint16_t u10_adc0_readAoutCamera0(void) 		;
volatile uint16_t u10_adc0_readAoutCamera1(void) 		;
volatile uint16_t u10_adc0_readPOT1_shield(void)		;
volatile uint16_t u10_adc0_readPOT2_shield(void)		;
volatile uint16_t u10_adc0_readBatteryVoltage(void)	;
volatile uint16_t u10_adc0_read_HB_AIFB(void)			;
volatile uint16_t u10_adc0_read_HB_BIFB(void)			;

/* Functions prototypes */

/**************************************************************
 *  Name                 :
 *  Description          : 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
#endif /* ADC_H_ */
