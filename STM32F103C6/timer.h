

#include <stm32f103x6.h>
#include <stdint.h>
#include "delay.h"



void timer_init(void);
uint8_t timer_getFlag(void);
void SysTick_Handler(void);
void timer_resetFlag(void);

