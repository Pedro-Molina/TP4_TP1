#include "mef.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "lcd.h"

typedef enum {invalido,ingresar_porcentaje} state_name;
	
//constantes

//Variables Privadas
static state_name actual_state;
//static uint8_t time_state= 0;
static uint8_t hora=0,min=0,seg=0,cantTiempo = 9;
static uint8_t stringTime[8]= {'0','0',':','0','0',':','0','0'};

int num=0;
int num_digits;
unsigned char snum[6];

//funciones privadas
void actualizarTiempo(void);
void prepararHora(void);
uint8_t verificarStringValido(unsigned char*);
void processInvalido(void);
void processIngresarPorcentaje(void);
void processConsultarPorcentaje(void);

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
	//SI LLEGO MENSAJE
	if(getLlegoMensaje()){
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
	lcd_gotoXY(0, 0);
	lcd_string(stringTime, 8);
	
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
	if(strncmp(str,"CONOCER PORCENTAJE\0",(sizeof(unsigned char))*22) == 0){
	   usart1_sendStr("EL PORCENTAJE DE ILUMINACION ES: X \r\n\0");
	   actual_state=invalido;
	   return 0;
	   }else{
	      if(strncmp(str,"CAMBIAR PORCENTAJE\0",(sizeof(unsigned char))*22) == 0){
		 actual_state=ingresar_porcentaje;
		 usart1_sendStr("INGRESE UN VALOR DE ILUMINACION DE 0-100:  \n \0");
		 return 0;
		 }
       }
	 return 1;
 }



void processInvalido(){
   if(verificarStringValido(getTX_Buffer())){
      usart1_sendStr("\r\n BIENVENIDO AL SISTEMA AUTOMATICO DE ILUMINACION \r\n Para conocer el porcentaje de iluminacion del cuarto ingrese CONOCER PORCENTAJE \r\n Para modificar el porcentaje de iluminacion ingrese CAMBIAR PORCENTAJE \r\n \0");
      }
   
}

void processIngresarPorcentaje(){
   int flag=0;
   num=atoi(getTX_Buffer());
			if(num > 0){
                 if(num<100){
                     usart1_sendStr("NUMERO VALIDO: Su porcentaje de iluminacion es: \0");
			         itoa(num,snum,10);
			         usart1_sendStr(snum);
			         usart1_sendStr("\r\n\0");
					 flag=1;
                     actual_state=invalido;
                  }
              }
			  if(!flag) usart1_sendStr("NUMERO INVALIDO Por favor ingrese nuevamente un numero entre 0 y 100 \r\n \0");
}


