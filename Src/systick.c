#include "stm32g071xx.h"

#define SYSTICK_LOAD_VAL_US   16
#define SYSTICK_LOAD_VAL_MS 16000
#define CTRL_ENABLE        (1U<<0)
#define CTRL_CLKSRC        (1U<<2)
#define CTRL_COUNTFLAG     (1U<<16)

void systickDelayus(int delay)
{
	/*Reload with no. of clocks per us*/
	SysTick->LOAD = SYSTICK_LOAD_VAL_US;

	/*Clear systick current value register*/
	SysTick->VAL = 0;

	/*Enable systick and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0;i<delay;i++)
	{
		/*wait until the count flag is set*/
		while(!(SysTick->CTRL&CTRL_COUNTFLAG));
	}
	SysTick->CTRL = 0;
}

void systickDelayms(int delay)
{
	/*Reload with no. of clocks per ms*/
	SysTick->LOAD = SYSTICK_LOAD_VAL_MS;

	/*Clear systick current value register*/
	SysTick->VAL = 0;

	/*Enable systick and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	for(int i=0;i<delay;i++)
	{
		/*wait until the count flag is set*/
		while(!(SysTick->CTRL&CTRL_COUNTFLAG));
	}
	SysTick->CTRL = 0;
}
