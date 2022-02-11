#include <stm32f103x6.h>
#include <stdint.h>
#include <stdio.h>
#include "mef.h"
#define TX_BUFFER_LENGTH 25

void usart1_init(void);
void usart1_sendByte(unsigned char c);
void usart1_sendStr(char* str);
void usart1_sendInt(unsigned int i);
uint8_t* getTX_Buffer(void);
void setLlegoMensaje(uint8_t d);
void setTXindice_escritura(uint8_t d);
uint8_t getTXindice_escritura(void);
void usart1_Write_Char_To_Buffer(char data);
uint8_t getLlegoMensaje(void);


