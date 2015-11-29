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
void vfn_SetPosition_SteeringServo(int8_t i8position)					;
void vfn_Set_RightMotors_PWM(uint8_t u8MotorA1pwm, uint8_t u8MotorA2pwm);
void vfn_Set_LeftMotors_PWM(uint8_t u8MotorB1pwm, uint8_t u8MotorB2pwm)	;


/**************************************************************
 *  Name                 : vfn_Init_SteeringServo_PTB0
 *  Description          : Init GPIO and Timers to use servo motor
 *  Parameters           : void
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_Init_SteeringServo_PTB0(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); 
  
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; 

	TPM1_SC = 0;
    TPM1_CONF = 0;
   
	TPM1_SC = TPM_SC_PS(TPM1_CLK_PRESCALE) | TPM_SC_TOIE_MASK;;
    TPM1_MOD = TPM1_CLOCK/(1<<TPM1_CLK_PRESCALE)/TPM1_OVERFLOW_FREQUENCY;
                       
    TPM1_C0SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
          
	//Enable the TPM Counter
	TPM1_SC |= TPM_SC_CMOD(1);
               
	//Enable the FTM functions on the the port               
	PORTB_PCR0 = PORT_PCR_MUX(3);     
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
	//Setup H-Bridge enables and faults
	PORTE_PCR21 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;   
	PORTE_PCR20 = PORT_PCR_MUX(1); 
	
    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); 
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK;
        
    TPM0_SC = 0;
    TPM0_CONF = 0;
    
    TPM0_SC = TPM_SC_PS(TPM0_CLK_PRESCALE);
	TPM0_MOD = TPM0_MODULE;
    
	//Setup Channels 0,1,2,3
    TPM0_C0SC = TPM_PWM_H ;
    TPM0_C1SC = TPM_PWM_L ; // invert the second PWM signal for a complimentary output;
    TPM0_C2SC = TPM_PWM_H ;
    TPM0_C3SC = TPM_PWM_L ; // invert the second PWM signal for a complimentary output;
    
    TPM0_C3V = STOP_MOTOR_L;
    TPM0_C1V = STOP_MOTOR_L;
    
    //Enable the TPM COunter
    TPM0_SC |= TPM_SC_CMOD(1);
    
    //Enable the FTM functions on the the port
    PORTC_PCR1 = PORT_PCR_MUX(4);
    PORTC_PCR2 = PORT_PCR_MUX(4);     
    PORTC_PCR3 = PORT_PCR_MUX(4);  
    PORTC_PCR4 = PORT_PCR_MUX(4);  
    
	//Setup GPIO H-Bridge enable
    GPIOE_PDDR =  HBRIDGE_EN_LOC;  
    HBRIDGE_DISABLE;
}

/**************************************************************
 *  Name                 : vfn_Set_RightMotors_PWM
 *  Description          : Set the PWM command of the motors. 
 *  Parameters           : u8MotorA1pwm, forward PWM value
 *  					   u8MotorA2pwm, backward complementary PWM value
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_Set_RightMotors_PWM(uint8_t u8MotorA1pwm, uint8_t u8MotorA2pwm)
{
	MOTORA1_RIGHT_VALUE = u8MotorA1pwm;
	MOTORA2_RIGHT_VALUE = u8MotorA2pwm;
}

/**************************************************************
 *  Name                 : vfn_Set_LeftMotors_PWM
 *  Description          : Set the PWM command of the motors. 
 *  Parameters           : u8MotorB1pwm, forward PWM value
 *  					   u8MotorB2pwm, backward complementary PWM value
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_Set_LeftMotors_PWM(uint8_t u8MotorB1pwm, uint8_t u8MotorB2pwm)
{
	MOTORB1_LEFT_VALUE = u8MotorB1pwm;
	MOTORB2_LEFT_VALUE = u8MotorB2pwm;
}
