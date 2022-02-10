
#include "timer.h"
#include <stm32f103x6.h>
#include <stdio.h>


static volatile uint8_t flag = 0;

void timer_init(){
	SysTick_Config (1800000);		//timer cada 25 ms con 1 mhz de frecuencia 1800000
}

uint8_t timer_getFlag(){
	return flag;
} 

void timer_resetFlag(){
	flag = 0;
}
void SysTick_Handler()
{
	flag = 1;
}

