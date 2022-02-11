
#ifndef mef
#define mef
#include <stm32f103x6.h>
#include <string.h>
#define MAX_TIME 999999
#define RANGO 0.1 //10% del valor
#define MAXLUX 1152 //el valor en voltios de la habitacion completamente iluminada 500LUXES


void MEF_Update(void);
void MEF_Init(void);
uint32_t rangoAceptable(uint32_t adc, uint32_t valor);
#endif
