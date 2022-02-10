/* Main.c file generated by New Project wizard
 *
 * Created:   mar. feb. 1 2022
 * Processor: STM32F103C6
 * Compiler:  Keil for ARM
 */

#include <stm32f103x6.h>
#include "dc_motor.h"
#include "delay.h"
#include "adc.h"



int main()
{
	RCC->APB2ENR |= 0xFC | (1<<9) | (1<<14); 	/* enable GPIO clocks */
	RCC->APB1ENR |= (1<<0);
	//RCC->APB1ENR |= (1<<0); 	/* enable TIM2 clock */
	GPIOA ->CRL |= 0x44444330; 	/* PA1,PA2: output push-pull - PA0 analog input*/
	init_RC();
	//medirRC();
	//dc_motor_clockwise();
	//delay_us(1000000);
	//dc_motor_anticlockwise();
	//delay_us(1000000);
	//dc_motor_stop();

	
	while(1)
	{
		medirRC();
		delay_us(1000);
	}
}

