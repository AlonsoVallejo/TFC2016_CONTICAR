/*
 * TPM.c
 *
 *  Created on: Oct 18, 2015
 *      Author: Vallejo
 */
/*============================================================================*/
/*                     AVR - EMBEDDED SYSTEMS SOFTWARE                        */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        TPM.c
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
/*   1.0	    18/10/2015     AVR		add the init functions for FTM.          
 *   1.1	    28/11/2015     AVR		Move function and defines to another files                                   							  */
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "TPM.h"
/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */

/*source clock select.*/

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
void vfn_Init_SteeringServo_PTB0(void)									;
void vfn_Init_DCmotors(void)											;


/**************************************************************
 *  Name                 : vfn_Init_SteeringServo_PTB0
 *  Description          : Init GPIO and Timers to use servo motor
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_Init_SteeringServo_PTB0(void)
{
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0x1U); 
  
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; 
	
	//Blow away the control registers to ensure that the counter is not running
	TPM1_SC = 0x0U;
    TPM1_CONF = 0x0U;
   
    //While the counter is disabled we can setup the prescaler
	TPM1_SC = TPM_SC_PS(TPM1_CLK_PRESCALE);
    TPM1_MOD = TPM1_CLOCK/(1<<TPM1_CLK_PRESCALE)/TPM1_OVERFLOW_FREQUENCY;
                       
    TPM1_C0SC = TPM_PWM_H;
          
	//Enable the TPM Counter
	TPM1_SC |= TPM_SC_CMOD(0x1U);
               
	//Enable the FTM functions on the the port               
	PORTB_PCR0 = PORT_PCR_MUX(3U);     
}

/**************************************************************
 *  Name                 : vfn_Init_DCmotors
 *  Description          : Init GPIO and Timers to use DC motors. 
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_Init_DCmotors(void)
{	
    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0x1U); 
    
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
	
    //Blow away the control registers to ensure that the counter is not running
    TPM0_SC = 0x0U;
    TPM0_CONF = 0x0U;
    
    //While the counter is disabled we can setup the prescaler
    TPM0_SC = TPM_SC_PS(PS_1);
    
	TPM0_MOD = TPM0_MODULE; //PERIOD FOR THE TPM0 
	//TPM0_SC |= TPM_SC_CPWMS_MASK; // select the CPWMS mode.

	//Setup Channels 0,1,2,3
    TPM0_C0SC = TPM_PWM_H;
    TPM0_C1SC = TPM_PWM_L; // invert the second PWM signal for a complimentary output;
    TPM0_C2SC = TPM_PWM_H;
    TPM0_C3SC = TPM_PWM_L; // invert the second PWM signal for a complimentary output;

	TPM0_SC	|= TPM_SC_CMOD(0x1U); //Enable the TPM Counter
	
    //Enable the FTM functions on the the port
    PORTC_PCR1 = PORT_PCR_MUX(0x4U) | PORT_PCR_DSE_MASK;
    PORTC_PCR2 = PORT_PCR_MUX(0x4U) | PORT_PCR_DSE_MASK;     
    PORTC_PCR3 = PORT_PCR_MUX(0x4U) | PORT_PCR_DSE_MASK;  
    PORTC_PCR4 = PORT_PCR_MUX(0x4U) | PORT_PCR_DSE_MASK;  
    
}


