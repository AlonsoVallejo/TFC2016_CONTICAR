/*
 * GPIO.c
 *
 *  Created on: Oct 18, 2015
 *      Author: Vallejo
 */
/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        GPIO.c
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
/*   1.0	    18/10/2015     AVR		add the init functions for gpios.
 *   1.1	    20/10/2015     AVR		Change the GPIO registers to FGPIO.                                                  							  */
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "GPIO.h"
/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

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
void vfn_init_userGPIO_LineScanCamera (void)		;
void vfn_init_userGPIO_shield_DCmotors (void)		;
void vfn_init_userGPIO_tfcshield(void)				;
void vfn_init_userGPIO_speedSensors(void)			;
volatile T_BOOLEAN ub_state_SpeedSensor0_PTA1(void) ;
volatile T_BOOLEAN ub_state_SpeedSensor1_PTA2 (void);
volatile uint16_t u16_DipSW_val(void)				;
volatile uint8_t u8_PushButtonA_state(void)			; 
volatile uint8_t u8_PushButtonB_state(void)			;
/**************************************************************
 *  Name                 : vfn_init_userGPIO_LineScanCamera
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the LSC  
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_init_userGPIO_LineScanCamera (void)
{
	SIM_SCGC5 |=  SIM_SCGC5_PORTA_MASK | 
				  SIM_SCGC5_PORTB_MASK | 
				  SIM_SCGC5_PORTC_MASK |
				  SIM_SCGC5_PORTD_MASK |
				  SIM_SCGC5_PORTE_MASK ;  // enable all GPIO ports of mcu.
		
	PORTD_PCR7 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTD3 is GPIO.
	PORTE_PCR1 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTC1 is GPIO.
		
	PORTD_PCR5 = PORT_PCR_MUX(0); //Make sure AO signal goes to an analog input
	PORTD_PCR6 = PORT_PCR_MUX(0); //Make sure AO signal goes to an analog input
	
	FGPIOD_PDDR |= GPIO_PIN(7U); // Make sure the CLK and SI pins are outputs
	FGPIOE_PDDR |= GPIO_PIN(1U); // TAOS clock pin
	
	CAMERA_CLK_LOW;
	CAMERA_SI_LOW;
		
	PORTA_PCR12 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTD3 is GPIO.
	FGPIOA_PDDR |= GPIO_PIN(12U); // Make sure the CLK and SI pins are outputs
		
	PORTA_PCR13 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTD3 is GPIO.
	FGPIOA_PDDR |= GPIO_PIN(13U); // Make sure the CLK and SI pins are outputs
}

/**************************************************************
 *  Name                 : vfn_init_userGPIO_shield_DCmotors
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the DC motors  
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_init_userGPIO_shield_DCmotors (void)
{
	PORTE_PCR21 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTE21 as GPIO (ENABLE)
	FGPIOE_PDDR |= GPIO_PIN(21U); // Enable H - bridge pin
	ENABLE_H_BRIGDE;
}

/**************************************************************
 *  Name                 : vfn_init_userGPIO_tfcshield
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the tfc shield.  
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_init_userGPIO_tfcshield(void)
{
	/*Push buttons Drivers*/
	PORTC_PCR13 = PORT_PCR_MUX(1U); 
	PORTC_PCR17 = PORT_PCR_MUX(1U);
	
	/*DIP Switch Drivers*/
	PORTE_PCR2 = PORT_PCR_MUX(1U); 
	PORTE_PCR3 = PORT_PCR_MUX(1U); 
	PORTE_PCR4 = PORT_PCR_MUX(1U); 
	PORTE_PCR5 = PORT_PCR_MUX(1U); 
	
	//Ports for LEDs
	PORTB_PCR8  = PORT_PCR_MUX(1U)  | PORT_PCR_DSE_MASK;   
	PORTB_PCR9  = PORT_PCR_MUX(1U)  | PORT_PCR_DSE_MASK;   
	PORTB_PCR10 = PORT_PCR_MUX(1U)  | PORT_PCR_DSE_MASK;   
	PORTB_PCR11 = PORT_PCR_MUX(1U)  | PORT_PCR_DSE_MASK;  
	FGPIOB_PDDR |= GPIO_PIN(8U);
	FGPIOB_PDDR |= GPIO_PIN(9U);
	FGPIOB_PDDR |= GPIO_PIN(10U);
	FGPIOB_PDDR |= GPIO_PIN(11U);
}

/**************************************************************
 *  Name                 : vfn_init_userGPIO_speedSensors
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the speed sensors.  
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_init_userGPIO_speedSensors(void)
{
	PORTA_PCR1  = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTA1 as GPIO (ENABLE)
	PORTA_PCR2  = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK; //configure the PTA2 as GPIO (ENABLE)
}

/**************************************************************
 *  Name                 : ub_state_SpeedSensor0_PTA1
 *  Description          : Read the current state of the
 *  					   hall effect speed sensor 0 connected to PTA1.  
 *  Parameters           : void
 *  Return               : Current state of the speed sensor:
 *  					   TRUE or FALSE
 *  Critical/explanation : No
 **************************************************************/

volatile T_BOOLEAN ub_state_SpeedSensor0_PTA1 (void)
{
	volatile static T_BOOLEAN SPS1_Val = FALSE;
	SPS1_Val = (FGPIOA_PDIR>>1U) & 0x1;
	if(TRUE == SPS1_Val) return TRUE;
	else return FALSE;
}

/**************************************************************
 *  Name                 : ub_state_SpeedSensor1_PTA2
 *  Description          : Read the current state of the
 *  					   hall effect speed sensor 1 connected to PTA2.  
 *  Parameters           : void
 *  Return               : Current state of the speed sensor:
 *  					   TRUE or FALSE
 *  Critical/explanation : No
 **************************************************************/

volatile T_BOOLEAN ub_state_SpeedSensor1_PTA2 (void)
{
	volatile static T_BOOLEAN SPS2_Val = FALSE;
	SPS2_Val = (FGPIOA_PDIR>>2U) & 0x1;
	if(TRUE == SPS2_Val) return TRUE;
	else return FALSE;
}

/**************************************************************
 *  Name                 : u16_DipSW_val
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the tfc shield dip switch.  
 *  Parameters           : void
 *  Return               : value of dip switch
 *  Critical/explanation : No
 **************************************************************/
volatile uint16_t u16_DipSW_val(void)
{
	volatile static uint16_t DIP_Val = 0;
	DIP_Val = (FGPIOE_PDIR>>2) & 0xF;
	return DIP_Val;		
}

/**************************************************************
 *  Name                 : u8_PushButtonA_state
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the tfc shield push button A.  
 *  Parameters           : void
 *  Return               : 1 - button pressed
 *  					   0 - button no pressed
 *  Critical/explanation : No
 **************************************************************/
volatile uint8_t u8_PushButtonA_state(void) 
{
	static uint8_t SW1_Val=0;
	SW1_Val = (FGPIOC_PDIR>>13) & 0x1;
	return SW1_Val;		
}
/**************************************************************
 *  Name                 : u8_PushButtonB_state
 *  Description          : contains all the GPIO peripheral configuration
 *  					   for use the tfc shield push button B.  
 *  Parameters           : void
 *  Return               : 1 - button pressed
 *  					   0 - button no pressed
 *  Critical/explanation : No
 **************************************************************/
volatile uint8_t PUSH_BUTTON_2_STATE(void)
{
	static uint8_t SW2_Val=0;
	SW2_Val = (FGPIOC_PDIR>>17) & 0x1;
	return SW2_Val;		
}
