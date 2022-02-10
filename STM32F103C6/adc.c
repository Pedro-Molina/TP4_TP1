   #include "adc.h"

   volatile uint32_t adcResult=0,time=0;
   volatile uint32_t capacitancia;

   void medirRC(){
	 ADC1->SQR3 = 0; //choose channel 0 as input
	 ADC1->CR2 = 1; //ADCON = 1 star conversion
	 while((ADC1->SR&(1<<1)) == 0);
	 adcResult=ADC1->DR;
   }

   void init_RC(){
      ADC1->CR2 = 1; //ADON = 1 (power-up)
      ADC1->SMPR2 = 7; // SMP1 = 111 (7.5 ADC clock cycles)
      delay_us(10000);
   }
