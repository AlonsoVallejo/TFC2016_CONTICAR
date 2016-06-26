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
 *   1.1	    20/10/2015     AVR		Change the GPIO registers to FGPIO.      
 *   1.2		25/06/2016	   AVR		implement functions to batt voltage                                            							  */
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
void vfn_init_userGPIO_LineScanCamera (void)		  ;
void vfn_init_userGPIO_shield_DCmotors (void)		  ;
void vfn_init_userGPIO_tfcshield(void)				  ;
void vfn_init_userGPIO_speedSensors(void)			  ;
void vfn_LEDs_ctrl_BattLevel_LEDs (void)			  ;
void IO_ports_Set_PortB_pin(uint8_t lub_pin_number)	  ;
void IO_ports_Clear_PortB_pin(uint8_t lub_pin_number) ;
void IO_ports_Toggle_PortB_pin(uint8_t lub_pin_number);
volatile T_BOOLEAN ub_state_SpeedSensor0_PTA1(void)   ;
volatile T_BOOLEAN ub_state_SpeedSensor1_PTA2 (void)  ;
volatile uint16_t u16_DipSW_val(void)				  ;
volatile uint8_t u8_PushButtonA_state(void)			  ; 
volatile uint8_t u8_PushButtonB_state(void)			  ;

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
		
	PORTD_PCR7 = PORT_PCR_MUX(1U) | PORT_PCR_DSE_MASK; //configure the PTD3 is GPIO.
	PORTE_PCR1 = PORT_PCR_MUX(1U) | PORT_PCR_DSE_MASK; //configure the PTC1 is GPIO.
		
	PORTD_PCR5 = PORT_PCR_MUX(0U); //Make sure AO signal goes to an analog input
	PORTD_PCR6 = PORT_PCR_MUX(0U); //Make sure AO signal goes to an analog input
	
	FGPIOD_PDDR |= GPIO_PIN(7U); // Make sure the CLK and SI pins are outputs
	FGPIOE_PDDR |= GPIO_PIN(1U); // TAOS clock pin
	
	CAMERA_CLK_LOW;
	CAMERA_SI_LOW;
		
	PORTA_PCR12 = PORT_PCR_MUX(1U) | PORT_PCR_DSE_MASK; //configure the PTD3 is GPIO.
	FGPIOA_PDDR |= GPIO_PIN(12U); // Make sure the CLK and SI pins are outputs
		
	PORTA_PCR13 = PORT_PCR_MUX(1U) | PORT_PCR_DSE_MASK; //configure the PTD3 is GPIO.
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
	//Setup H-Bridge enables and faults
	PORTE_PCR21 = PORT_PCR_MUX(1);   
	PORTE_PCR20 = PORT_PCR_MUX(1); 
	
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
	PORTA_PCR1  = PORT_PCR_MUX(1U) | PORT_PCR_DSE_MASK; //configure the PTA1 as GPIO (ENABLE)
	PORTA_PCR2  = PORT_PCR_MUX(1U) | PORT_PCR_DSE_MASK; //configure the PTA2 as GPIO (ENABLE)
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
	DIP_Val = (FGPIOE_PDIR>>2U) & 0xF;
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
volatile T_BOOLEAN u8_PushButtonA_state(void) 
{
	static uint8_t SW1_Val=0U;
	SW1_Val = (FGPIOC_PDIR>>13U) & 0x1;
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
volatile T_BOOLEAN u8_PushButtonB_state(void)
{
	static uint8_t SW2_Val=0U;
	SW2_Val = (FGPIOC_PDIR>>17U) & 0x1;
	return SW2_Val;		
}

/**************************************************************
 *  Name                 :	vfn_LEDs_ctrl_BattLevel_LEDs
 *  Description          :	indicates batt voltage
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
#define BATT_LEDS_VLTG_LVL4 11
#define BATT_LEDS_VLTG_LVL3 10
#define BATT_LEDS_VLTG_LVL2 9
#define BATT_LEDS_VLTG_LVL1 8
void vfn_LEDs_ctrl_BattLevel_LEDs (void)
{
	uint16_t BatSenseADC_Value;
	uint8_t lub_VoltageLevel = 0;
	/* Read voltage from ADC */
	BatSenseADC_Value = u10_adc0_readBatteryVoltage();
	/* Determine level according thresholds */
	if(BatSenseADC_Value >= 99) // Full voltage level (from 6.7 to above)
	{
		lub_VoltageLevel = 4;
	}
	else if((BatSenseADC_Value < 400) && (BatSenseADC_Value >= 380)) // Voltage level 3 (from 6.2 to 6.7)
	{
		lub_VoltageLevel = 3;
	}
	else if((BatSenseADC_Value < 380) && (BatSenseADC_Value >= 360)) // Voltage level 2 (from 5.7 to 6.2)
	{
		lub_VoltageLevel = 2;
	}
	else if((BatSenseADC_Value < 360) && (BatSenseADC_Value >= 340)) // Voltage level 1 (from 5.2 to 5.7)
	{
		lub_VoltageLevel = 1;
	}
	else // Low voltage level (5.2 and below)
	{
		lub_VoltageLevel = 0;
	}
	/* Set LEDs state according level */
	switch(lub_VoltageLevel)
	{
		case 4:
			/* Turn On all the batt LEDs */
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL4);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL3);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL2);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL1);
		break;
		case 3:
			/* Turn On LEDs from LVL1 to LVL 3 only */
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL4);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL3);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL2);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL1);
		break;
		case 2:
			/* Turn On LEDs from LVL1 to LVL 2 only */
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL4);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL3);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL2);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL1);
		break;
		case 1:
			/* Turn On LED LVL1 only */
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL4);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL3);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL2);
			IO_ports_Set_PortB_pin(BATT_LEDS_VLTG_LVL1);
		break;
		case 0:
			/* Togle LED LVL1 only */
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL4);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL3);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL2);
			IO_ports_Toggle_PortB_pin(BATT_LEDS_VLTG_LVL1);
		break;
		default:
			/* Togle LED LVL4 only */
			IO_ports_Toggle_PortB_pin(BATT_LEDS_VLTG_LVL4);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL3);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL2);
			IO_ports_Clear_PortB_pin(BATT_LEDS_VLTG_LVL1);
		break;
	}
}

/**************************************************************
 *  Name                 :	IO_ports_Set_PortB_pin
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void IO_ports_Set_PortB_pin(uint8_t lub_pin_number)
{
	if(lub_pin_number < 32)
	{
		GPIOB_PSOR = GPIO_PIN(lub_pin_number);
	}
}

/**************************************************************
 *  Name                 :	IO_ports_Clear_PortB_pin
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void IO_ports_Clear_PortB_pin(uint8_t lub_pin_number)
{
	if(lub_pin_number < 32)
	{
		GPIOB_PCOR = GPIO_PIN(lub_pin_number);
	}
}

/**************************************************************
 *  Name                 :	IO_ports_Toggle_PortB_pin
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void IO_ports_Toggle_PortB_pin(uint8_t lub_pin_number)
{
	if(lub_pin_number < 32)
	{
		GPIOB_PTOR = GPIO_PIN(lub_pin_number);
	}
}
