###############################################################################
# Makefile for project 
###############################################################################

## General options
PROJECT = 
MCU = STM32F103C6
COMPILER = "Keil for ARM"
TARGET = Debug
SHELL = C:\WINDOWS\system32\cmd.exe

## Tools general options
ASMFLAGS=--cpu=cortex-m3 --thumb -g
CCFLAGS=--cpu=cortex-m3 --thumb -I.. -I../../../../../../../../Keil_v5/ARM/CMSIS/Include -g
LDFLAGS=--scatter ../stm32f103x6.sct

## Processing Tools
CC=armcc.exe
LD=armlink.exe
ASM=armasm.exe
BIN2HEX=fromelf.exe
#  C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/Debug.elf: TOOL=LD
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/main.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/main.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/SYSTEM~1.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/system_stm32f1xx.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/STARTU~1.o: TOOL=ASM
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/startup_stm32f103.s
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/dc_motor.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/dc_motor.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/delay.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/delay.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/adc.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/adc.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/mef.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/mef.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/timer.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/timer.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/usart.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/usart.c
#     C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/Debug/lcd.o: TOOL=CC
#        C:/Users/tinch/OneDrive/Documentos/Proteus/TP4_TP1/STM32F103C6/lcd.c

# Build tree:
all:	Debug

Debug:	Debug.elf

Debug.elf:	main.o SYSTEM~1.o STARTU~1.o dc_motor.o delay.o adc.o mef.o timer.o usart.o lcd.o 
	$(LD)  $(LDFLAGS)  "main.o" "SYSTEM~1.o" "STARTU~1.o" "dc_motor.o" "delay.o" "adc.o" "mef.o" "timer.o" "usart.o" "lcd.o" --output "Debug.elf"

main.o:	../main.c 
	$(CC) $(CCFLAGS)  "../main.c" -c -o "main.o"

SYSTEM~1.o:	../system_stm32f1xx.c 
	$(CC) $(CCFLAGS)  "../system_stm32f1xx.c" -c -o "SYSTEM~1.o"

STARTU~1.o:	../startup_stm32f103.s 
	$(ASM) $(ASMFLAGS)  "../startup_stm32f103.s" -o "STARTU~1.o"

dc_motor.o:	../dc_motor.c 
	$(CC) $(CCFLAGS)  "../dc_motor.c" -c -o "dc_motor.o"

delay.o:	../delay.c 
	$(CC) $(CCFLAGS)  "../delay.c" -c -o "delay.o"

adc.o:	../adc.c 
	$(CC) $(CCFLAGS)  "../adc.c" -c -o "adc.o"

mef.o:	../mef.c 
	$(CC) $(CCFLAGS)  "../mef.c" -c -o "mef.o"

timer.o:	../timer.c 
	$(CC) $(CCFLAGS)  "../timer.c" -c -o "timer.o"

usart.o:	../usart.c 
	$(CC) $(CCFLAGS)  "../usart.c" -c -o "usart.o"

lcd.o:	../lcd.c 
	$(CC) $(CCFLAGS)  "../lcd.c" -c -o "lcd.o"

# tidy - delete all temporary files which are not involved in the target generation
tidy:

# cleanup - delete all generated files
clean:	tidy
	rm -rf Debug.elf
	rm -rf main.o
	rm -rf SYSTEM~1.o
	rm -rf STARTU~1.o
	rm -rf dc_motor.o
	rm -rf delay.o
	rm -rf adc.o
	rm -rf mef.o
	rm -rf timer.o
	rm -rf usart.o
	rm -rf lcd.o
