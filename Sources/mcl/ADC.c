/*
 * ADC.c
 *
 *  Created on: Oct 18, 2015
 *      Author: Vallejo
 */
/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        ADC.c
* version:         1.0 
* created_by:      AVR
* date_created:   Oct 18, 2015
*=============================================================================*/
/* DESCRIPTION :                                                              */
/*============================================================================*/
/* FUNCTION COMMENT :                                                         */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |  AUTHOR  | Comment     						  */
/*----------------------------------------------------------------------------*/
//    1.0	    18/10/2015     AVR		add the init functions for adc.
// 	  1.1	    20/10/2015     AVR		add functions to read the pots and IFB. 
// 	  1.2	    05/12/2015     AVR		change the adc bits resolution.                                              							  */
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "ADC.h"
/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */

/*definitions of other ports that can be used for the ADC reading at FRDM-KL25Z*/
#define PTB0 						(8U)
#define PTB1 						(9U)
#define PTC2 						(11U)
#define PTC1 						(15U)

/*definitions of ports used by TFC-SHIELD for the ADC reading at FRDM-KL25Z*/
typedef enum
{
/*		INPUT					CHANNEL	    MCU PORT		*/
 TFC_POT_1_ADC_CHANNEL		=	(13U), 	 /*  PTB3  */
 TFC_POT_2_ADC_CHANNEL		=	(12U),   /*  PTB2  */
 TFC_BAT_SENSE_CHANNEL		=	(4U) ,   /*  PTE29 */
 TFC_LINESCAN0_ADC_CHANNEL	=	(6U) ,   /*  PTD5  */
 TFC_LINESCAN1_ADC_CHANNEL	=	(7U) ,   /*  PTD6  */
 TFC_HBRIDGE_A_IFB_CHANNEL	=	(7U) ,   /*  PTE23 */
 TFC_HBRIDGE_B_IFB_CHANNEL	=	(3U)     /*  PTE22 */
}TFC_SHIELD_ADC_INPUTS;



/* definitions for the configuration of the ADC resolution*/
#define Eight_bits  				(0U)
#define Ten_bits    				(2U)
#define Twelve_bits 				(1U)
#define Sixteen_bits 				(3U)

/* Functions macros */

/*definitions for the configuration of the ADC resolution*/

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 



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
void vfn_init_adc0 (void)								;
volatile uint16_t u10_adc0_readAoutCamera0(void) 		;
volatile uint16_t u10_adc0_readAoutCamera1(void) 		;
volatile uint16_t u10_adc0_readPOT1_shield(void)		;
volatile uint16_t u10_adc0_readPOT2_shield(void)		;
volatile uint16_t u10_adc0_readBatteryVoltage(void)		;
volatile uint16_t u10_adc0_read_HB_AIFB(void)			;
volatile uint16_t u10_adc0_read_HB_BIFB(void)			;
/**************************************************************
 *  Name                 : void vfn_init_adc0 (void)
 *  Description          : Init the ADC0 peripherals
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_init_adc0 (void)
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;	// enable the ADC0 port.
	ADC0_CFG1 |= ADC_CFG1_MODE( Ten_bits ) | ADC_CFG1_ADIV(0U); // ADC set of bits to a certain value and dividing the frequency conversion
	ADC0_CFG2 |= ADC_CFG2_ADHSC_MASK; // High speed conversion.
	ADC0_CFG2 |= ADC_CFG2_ADLSTS_MASK; // 2 extra ASDCK cycles
	ADC0_SC1A  = ADC_SC1_ADCH(31);
}

/**************************************************************
 *  Name                 : void u10_adc0_readAoutCamera0(void)
 *  Description          : function to read the LSC Aout in PTD5
 *  Parameters           : void
 *  Return               : conversion value result of LSC
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u10_adc0_readAoutCamera0(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_MASK; // select channel B ADxxB
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_LINESCAN0_ADC_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
	
	
}

/**************************************************************
 *  Name                 : void u10_adc0_readAoutCamera1(void)
 *  Description          : function to read the LSC Aout in PTD6
 *  Parameters           : void
 *  Return               : conversion value result of LSC
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u10_adc0_readAoutCamera1(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_MASK; // select channel B ADxxB
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_LINESCAN1_ADC_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
}

/**************************************************************
 *  Name                 : void u10_adc0_readPOT2_shield(void)
 *  Description          : function to read the potentiometer 1 Aout in PTB3
 *  Parameters           : void
 *  Return               : conversion value result of POT1
 **************************************************************/
volatile uint16_t u10_adc0_readPOT1_shield(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_SHIFT; // select channel A ADxxA
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_POT_1_ADC_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
}

/**************************************************************
 *  Name                 : void u10_adc0_readPOT2_shield(void)
 *  Description          : function to read the function to read the potentiometer 2 Aout in PTB2
 *  Parameters           : void
 *  Return               : conversion value result of POT2
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u10_adc0_readPOT2_shield(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_SHIFT; // select channel A ADxxA
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_POT_2_ADC_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
}

/**************************************************************
 *  Name                 : void u10_adc0_readBatteryVoltage(void)
 *  Description          : function to read the Battery voltage
 *  Parameters           : void
 *  Return               : conversion value result of voltage
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u10_adc0_readBatteryVoltage(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_MASK; // select channel B ADxxB
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_BAT_SENSE_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
}

/**************************************************************
 *  Name                 : void u10_adc0_read_HB_AIFB(void)
 *  Description          : function to read the function to read 
 *  					   the feedback current of DC motor A 
 *  Parameters           : void
 *  Return               : conversion value result of POT2
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u10_adc0_read_HB_AIFB(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_SHIFT; // select channel A ADxxA
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_HBRIDGE_A_IFB_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
}

/**************************************************************
 *  Name                 : void u10_adc0_read_HB_BIFB(void)
 *  Description          : function to read the function to read 
 *  					   the feedback current of DC motor B
 *  Parameters           : void
 *  Return               : conversion value result of POT2 
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u10_adc0_read_HB_BIFB(void)
{
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_SHIFT; // select channel A ADxxA
	ADC0_SC1A  = ADC_SC1_ADCH(TFC_HBRIDGE_B_IFB_CHANNEL); // select the  reading port.
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  	// while the conversion is process.	
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));// when the conversion ends.		
	return ADC0_RA; // return the conversion value.
}
