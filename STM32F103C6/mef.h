
#ifndef mef
#define mef
#include <stm32f103x6.h>
#include <string.h>
#define MAX_TIME 999999
#define RANGO 0.1 //10% del valor
#define MAXLUX 3014 //el valor en voltios de la habitacion completamente iluminada 500LUXES
#define MIDLUX  2655
#define MINLUX   801

void MEF_Update(void);
void MEF_Init(void);

#endif
