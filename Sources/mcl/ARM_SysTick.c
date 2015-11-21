#include "ARM_SysTick.h"

//Since this SysTick is part of the Cortex M4 Core,   you need to look in the 
//Cortex M4 Generic users Guide

static uint32_t SYSTICK_FREQUENCY;

//See Section 4.4
void InitSysTick(uint32_t Tick_Period_In_uS)
{
	SYSTICK_FREQUENCY = ((CORE_CLOCK * PERIOD_CORE_CLOCK))/(Tick_Period_In_uS * 0.000001);
	
	SYST_RVR = CORE_CLOCK/SYSTICK_FREQUENCY; // Period of the TICK execution.
	SYST_CSR = SysTick_CSR_ENABLE_MASK | SysTick_CSR_TICKINT_MASK | SysTick_CSR_CLKSOURCE_MASK;
	//Important!  Since the Systick is part of the Cortex core and NOT a kinetis peripheral
	// its Interrupt line is not passed through NVIC.   You need to make sure that
	//the SysTickIRQ function is poopulated in the vector table.  See the kinetis_sysinit.c file
}


