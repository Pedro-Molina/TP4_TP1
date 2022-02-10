#include "dc_motor.h"


void dc_motor_anticlockwise() //giro antihorario
{
	GPIOA->ODR &= ~(1<<1);	
	GPIOA->ODR |= (1<<2); 
}

void dc_motor_clockwise() //giro horario
{
	GPIOA->ODR &= ~(1<<2);	
	GPIOA->ODR |= (1<<1); 
}

void dc_motor_stop(){
	GPIOA->ODR &= ~(1<<2);	
	GPIOA->ODR &= ~(1<<1);	
}



