
#include <usart.h>

volatile uint8_t TX_Buffer[]= "Bienvenidos a mi casa";
static uint8_t llegoMensaje=0;
static uint8_t TXindice_escritura=0;


void usart1_Write_Char_To_Buffer(char data) {
   if(TXindice_escritura < TX_BUFFER_LENGTH){
      TX_Buffer[TXindice_escritura] = data;
      TXindice_escritura++;
      } else{
	 //MENSAJE DE ERROR DE BUFFER
	 usart1_sendStr("ERROR\n\0");
      }
}




void usart1_init(){
	GPIOA->ODR|=(1<<10); //pull-up PA10
	GPIOA->CRH =0x444448B4; //RX1=input with pull-up (PA10), TX1 = alt func output 50MHz (PA9)
	USART1->CR1=0x202C; // 0010 0000 0010 1100 -> Enable USART, 8N1, Receiver enable - TX ENABLE-  RECIEVE INTERRUMPTION
	USART1->BRR=7500; //ACA EN REALIDAD VA 72MHz/9600bps=7500; for some reason USART1 - PERO EN REALIDAD USAMOS 1 MHZ PQ TODO SE ROMPIA SINO
        NVIC_EnableIRQ(USART1_IRQn);
}												//doesn't use 36MHz clock by default and uses the 72MHz

void usart1_sendByte(unsigned char c){
        
        USART1->DR=c;
	while((USART1->SR&(1<<6))==0); //wait until the TC flag is set
	 USART1->SR &= ~(1<<6);
	
}
void usart1_sendStr(char* str){
	while(*str!=0){ //while char act is not '\0'
		usart1_sendByte(*str); //print it
		str++; //go to next char
	}
}

void usart1_sendInt(unsigned int i){
	char str[10]; //local variable to store string
	sprintf(str,"%d",i); //transform i to a string and store it in str
	usart1_sendStr(str); //print it in the USART1 str
}

uint8_t* getTX_Buffer(){
      return TX_Buffer;
 }
 
 uint8_t getLlegoMensaje(){
      return llegoMensaje;
 }

 void setLlegoMensaje(uint8_t d){
    llegoMensaje=d;
    }

  void setTXindice_escritura(uint8_t d){
    TXindice_escritura=d;
}

uint8_t getTXindice_escritura(){
   return TXindice_escritura;
   }
