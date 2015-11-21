#ifndef ARM_SYSTICK_H_
#define ARM_SYSTICK_H_

#include "derivative.h"
#include "CrystalClock.h"

void InitSysTick(uint32_t Tick_Period_In_uS);

#define PERIPHERAL_BUS_CLOCK (CORE_CLOCK/2)	
#define PERIOD_CORE_CLOCK	 (0.0000000208) 

#endif /* SYSTICK_H_ */

