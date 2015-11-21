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
/*   1.0	    18/10/2015     AVR		add the init functions for FTM.                                             							  */
/*============================================================================*/       
/*============================================================================*/

/* Includes */
/* -------- */
#include "TPM.h"
/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */

/*source clock select.*/
#define TPM_PLLFLL 					1
#define TPM_OSCERCLK 				2
#define TPM_MCGIRCLK				3

#define	TPM_CNT_DIS					0
#define	TPM_CLK						1
#define	TPM_EXT_CLK					2

/*preescaler definitions.*/
#define PS_1						0
#define PS_2						1
#define PS_4						2
#define PS_8						3
#define PS_16						4
#define PS_32						5
#define PS_64						6
#define PS_128						7

/*confuralbles bits for the TPM modules.*/
#define TPM_OC_TOGGLE				TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK
#define TPM_OC_CLR					TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_SET					TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTL					TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTH					TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK

#define TPM_PWM_H 					TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK /* PWM  with HIGH TRUE pulse. */
#define TPM_PWM_L					TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK /* PWM  with LOW  TRUE pulse. */

#define EDGE_PWM					(0U) 
#define CENTER_PWM					(1U)

#define RISING_CAPTURE				(TPM_CnSC_ELSA_MASK)		/* TPM2_INPUT_CAPTURE_MODE  */
#define FALLING_CAPTURE				(TPM_CnSC_ELSB_MASK)	    /* TPM2_INPUT_CAPTURE_MODE  */

/*Servo and dc motors to PWM control definitions*/
/*Based in the FRDM-TFC SHIELD 2014 schematics*/

#define SERVO_MOTOR_VALUE 			TPM1_C0V /* PTB0    */
#define LEDS_CAMERA_PWM				TPM1_C1V /* PTB1    */
#define MOTORB1_LEFT_VALUE			TPM0_C0V /* PTC1 B1 */
#define MOTORB2_LEFT_VALUE			TPM0_C1V /* PTC2 B2 */
#define MOTORA1_RIGHT_VALUE			TPM0_C2V /* PTC3 A1 */
#define MOTORA2_RIGHT_VALUE			TPM0_C3V /* PTC4 A2 */

#define STOP_MOTOR_H				0U
#define STOP_MOTOR_L				255U

#define TPM0_CLOCK					(CORE_CLOCK/2)
#define TPM0_CLK_PRESCALE           (0U)  			// Prescale Selector value
#define TPM0_OVERFLOW_FREQUENCY 	(3000U) 		//Desired Frequency of PWM Signal 
#define TPM0_MODULE					(TPM0_CLOCK/(1<<TPM0_CLK_PRESCALE)/TPM0_OVERFLOW_FREQUENCY)
#define TPM0_PWM_UNIT				(TPM0_MODULE/200U)

#define TPM1_CLOCK					(48000000/2)	//48000000/2
#define TPM1_CLK_PRESCALE			(6U) 			//divide by 64
#define TPM1_OVERFLOW_FREQUENCY 	(50U)			//Desired Frequency of PWM Signal - Here 50Hz => 20ms period 

#define SERVO_MIN_DUTY_CYCLE		(SERVO_MIN_us*(TPM1_CLOCK/(1<<TPM1_CLK_PRESCALE)))/1000000
#define SERVO_MAX_DUTY_CYCLE		(SERVO_MAX_us*(TPM1_CLOCK/(1<<TPM1_CLK_PRESCALE)))/1000000

//Modify these numbers to set the servo limits
#define SERVO_MIN_us				(1100U)
#define SERVO_MAX_us				(1900U)

// H-Bridge management
#define HBRIDGE_EN_LOC				(uint32_t)(1<<21)
#define HBRIDGE_ENABLE				GPIOE_PSOR = HBRIDGE_EN_LOC	
#define HBRIDGE_DISABLE				GPIOE_PCOR = HBRIDGE_EN_LOC	
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
 *  Name                 : vfn_SetPosition_SteeringServo
 *  Description          : Set servo position 
 *  Parameters           : i8position, from -100 (max left) to +100 (max right)
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/
void vfn_SetPosition_SteeringServo(int8_t i8position)
{
	//Saturation control
	if(i8position>100)
	{
		i8position=100;
	}
	if(i8position<-100)
	{
		i8position=-100;
	}
	
	//Set the right value to servo timer
	SERVO_MOTOR_VALUE =((((i8position+100)/2)*(SERVO_MAX_DUTY_CYCLE - SERVO_MIN_DUTY_CYCLE))/100)+SERVO_MIN_DUTY_CYCLE;
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
