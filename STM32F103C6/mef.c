#include "mef.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lcd4bits.h"
#include "adc.h"
#include "dc_motor.h"

typedef enum {invalido,ingresar_porcentaje} state_name;
	
//constantes

//Variables Privadas
static state_name actual_state;
static uint32_t valor_LDR = (uint32_t) MAXLUX*0.33;
//static uint8_t time_state= 0;
static uint8_t hora=0,min=0,seg=0,cantTiempo = 9;
static uint8_t stringTime[8]= {'0','0',':','0','0',':','0','0'};
unsigned char* opcionIntensidad[3]={"BAJA",",MEDIA\0","ALTA\0"};
uint8_t opcionBytes[3]={4,7,6};
uint8_t opcion=0;

char num='0';
int mensaje;
int num_digits;
unsigned char snum[6];
uint32_t datoADC;

//funciones privadas
void actualizarTiempo(void);
void prepararHora(void);
uint8_t verificarStringValido(unsigned char*);
void processInvalido(void);
void processIngresarPorcentaje(void);
void processConsultarPorcentaje(void);

uint32_t rangoAceptable(uint32_t adc, uint32_t valor){
if(adc > valor-((uint32_t) MAXLUX*RANGO)){
    if(adc <valor+((uint32_t)MAXLUX*RANGO)){
         return 1;
    }
}
return 0;
}

char* itoa(int num, char* buffer, int base) {
    int curr = 0;
 
    if (num == 0) {
        // Base case
        buffer[curr++] = '0';
        buffer[curr] = '\0';
        return buffer;
    }
 
    num_digits = 0;
 
    if (num < 0) {
        if (base == 10) {
            num_digits ++;
            buffer[curr] = '-';
            curr ++;
            // Make it positive and finally add the minus sign
            num *= -1;
        }
        else
            // Unsupported base. Return NULL
            return NULL;
    }
 
    num_digits += (int)floor(log(num) / log(base)) + 1;
 
    // Go through the digits one by one
    // from left to right
    while (curr < num_digits) {
        // Get the base value. For example, 10^2 = 1000, for the third digit
        int base_val = (int) pow(base, num_digits-1-curr);
 
        // Get the numerical value
        int num_val = num / base_val;
 
        char value = num_val + '0';
        buffer[curr] = value;
 
        curr ++;
        num -= base_val * num_val;
    }
    buffer[curr] = '\0';
    return buffer;
}

void MEF_Init(){
	actual_state = invalido;
}


void MEF_Update(){
    if (++cantTiempo == 40){	//actualizo cada 1s
		actualizarTiempo();
		prepararHora();
		cantTiempo =0;
	}

    datoADC=adc_read();  //LEO LA RESISTENCIA
    if(rangoAceptable(datoADC,valor_LDR)){ //SI LA RESISTENCIA ES IGIUAL A LCDREAD O CERCA
    //NO SE MUEVE
    dc_motor_stop();
    }else{
    //SE MUEVE
    if(datoADC>valor_LDR){
       dc_motor_clockwise();
     }else{
       dc_motor_anticlockwise();
     }
}
      

	//SI LLEGO MENSAJE
    mensaje=getLlegoMensaje();
	if(mensaje){
	switch(actual_state){
		case invalido:
			processInvalido();
		break;
		case ingresar_porcentaje:
			processIngresarPorcentaje();
		break;
	}
	setLlegoMensaje(0);
     }
     
}

void prepararHora(){
	//stringTime[1] =  '0' + (uint8_t)((hora)%  (uint8_t)10);
	stringTime[4] =  '0' + (uint8_t)((min)%  (uint8_t)10);
	stringTime[7] =  '0' + (uint8_t)((seg)%  (uint8_t)10);
	stringTime[0] = ((hora/10)% 10) + '0';
	stringTime[3] = ((min/10)% 10) + '0';
	stringTime[6] = ((seg/10)% 10) + '0';

	//imprimir la hora en el led
	LCDGotoXY(0, 0);
	LCDstring(stringTime, 8);
    //LCDGotoXY(0, 1);
    //LCDstring("BAJA",4);
	//LCDstring(opcionIntensidad[opcion], opcionBytes[opcion]);
	
}
void actualizarTiempo(){

	if(++seg == 60)
	{
		seg = 0;
		if(++min == 60)
		{
			min =0;
			if(++hora == 24)
			{
				hora=0;
			}
		}
	}
}

//RETORNA 1 SI ES INVALIDO Y 0 SI NO ES ESTADO INVALIDO
uint8_t verificarStringValido(unsigned char* str){
	 usart1_sendStr("buffer: ");
	 usart1_sendStr(str);
     usart1_sendStr("\r\n\0");
	if(strncmp(str,"CONOCER INTENSIDAD\0",(sizeof(unsigned char))*22) == 0){
	   usart1_sendStr("LA INTENSIDAD ES: \0");
		//ilum = ((long)V*A*10)/((long)B*Rc*(1024-V))
       usart1_sendStr(opcionIntensidad[opcion]);
	   usart1_sendStr("\r\n\0");
	   actual_state=invalido;
	   return 0;
	   }else{
	      if(strncmp(str,"ELEGIR INTENSIDAD\0",(sizeof(unsigned char))*22) == 0){
		 actual_state=ingresar_porcentaje;
         usart1_sendStr("ELIJA UNA OPCION: \r\n\0" );
		 usart1_sendStr(" 1.LUMINOSIDAD BAJA \r\n 2.LUMINOSIDAD MEDIA\r\n 3.LUMINOSIDAD ALTA\r\n\0" );
		 return 0;
		 }
       }
	 return 1;
 }



void processInvalido(){
   if(verificarStringValido(getTX_Buffer())){
      usart1_sendStr("\r\n BIENVENIDO AL SISTEMA AUTOMATICO DE ILUMINACION \r\n Para conocer la intensidad de iluminacion del cuarto ingrese CONOCER INTENSIDAD \r\n Para modificar la intensidad de iluminacion ingrese ELEGIR INTENSIDAD \r\n \0");
      }
   
}

void processIngresarPorcentaje(){
	int comando_invalido = 1;
   num=getTX_Buffer()[0];
					LCDGotoXY(0, 1);
					
					switch(num) 
					{
						case '1' : 
							valor_LDR= MAXLUX*0.33; opcion=0; usart1_sendStr("OPCION VALIDA: Su intensidad de iluminacion es BAJA \0");
							LCDstring("BAJA ",4);
							//LCDstring(opcionIntensidad[opcion], opcionBytes[opcion]);
						break;
						case '2': 
							valor_LDR = MAXLUX*0.66; opcion=1; usart1_sendStr("OPCION VALIDA: Su intensidad de iluminacion es MEDIA\0");
							LCDstring("MEDIA",5);
						break;
						case '3': 
							valor_LDR = MAXLUX; opcion=2; usart1_sendStr("OPCION VALIDA: Su intensidad de iluminacion es ALTA\0");
							LCDstring("ALTA ",4);
						break;
						default:
						 //itoa(num,snum,10);
						 //usart1_sendStr(snum);
						usart1_sendStr("NUMERO INVALIDO Por favor ingrese nuevamente una opcion entre 1 y 3 \r\n \0");
						comando_invalido = 0;
						break;
					} 
					if (comando_invalido) {
						usart1_sendStr("\r\n\0");
						actual_state=invalido;

					}
					
}


