/*
 * SEOS.c
 *
 * Created: 10/05/2021 1:35:16
 *  Author: tomas
 */ 

#include "SEOS.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "teclado.h"
#include "lcd.h"

static unsigned char flag_teclado=0;
void mandarTecla();
void SEOSSChedulerTasks();

void SEOSTimer0Init(){
		OCR0A = 9; //Valor con el cual comparar
		TCCR0A = (1<<WGM01);// = 0b00000010; Modo CTC
		TCCR0B = (1<<CS01); // = 0b00000010; clk/8 (From Prescaler) 8MHz/8 =  1 MHz
		TIMSK0 = (1<<OCIE0A); // Habilita el comparador. T=10/1MHz = 0.01 s = 10 ms
		sei(); //Habilito interrupciones
}

ISR (TIMER0_COMPA_vect) //Que hacer cuando se interrumpe
{
	SEOSSChedulerTasks();
}

void SEOSDispatcherTasks(){
	if(flag_teclado){
		mandarTecla();
		flag_teclado = 0;
	}
}

void SEOSGoToSleep(void){
	//PONER EN IDLE
}

void SEOSSChedulerTasks(){
	flag_teclado = 1;
}
void mandarTecla(){ //VOLAR A LA MIERDAAAAAAAAAAAAAAAAAA
	char tecla = 0;
	if(TECLADO_Actualizar(&tecla)){
		LCDsendChar(tecla);
	}
}