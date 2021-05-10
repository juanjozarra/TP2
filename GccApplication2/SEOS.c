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
#include "lcd.h" //VOLAAAAAAAAAAAAAAAAAAAAAAAAR
#include "MEF.h"
#include "reloj.h"

void SEOSSChedulerTasks();
void mandarTecla();

static unsigned char flag_teclado=0;
static unsigned char counter_teclado=2; //Empieza dos ticks antes para desfasarse

static unsigned char flag_MEF=0;
static unsigned char counter_MEF=1; //Empieza un tick antes para desfasarse

static unsigned char flag_tiempo=0;
static unsigned char counter_tiempo=0;




void SEOSTimer0Init(){
	OCR0A = 77; //Valor con el cual comparar
	TCCR0A = (1<<WGM01);// = 0b00000010; Modo CTC
	TCCR0B = (1<<CS02)|(1<<CS00); // = 0b00000101; clk/1024 (From Prescaler) 8MHz/1024 =  7812.5 Hz
	TIMSK0 = (1<<OCIE0A); // Habilita el comparador. T=78/7812.5 Hz ~= 9,98 ms ~= 10ms
	sei(); //Habilito interrupciones
}

ISR (TIMER0_COMPA_vect) //Que hacer cuando se interrumpe
{
	SEOSSChedulerTasks();
}

void SEOSDispatcherTasks(){
	
	if(flag_teclado){
		//mandarTecla();
		flag_teclado = 0;
	}
	
	if(flag_MEF){
		MEF_actualizar();
		flag_MEF = 0;
	}
	
	if(flag_tiempo){
		RELOJ_Actualizar();
		flag_tiempo = 0;
	}
}

void SEOSGoToSleep(void){
	//PONER EN IDLE
}

void SEOSSChedulerTasks(){

	if(++counter_teclado==10){
		flag_teclado = 1;
		counter_teclado=0;
	}
	
	if(++counter_tiempo==100){
		flag_tiempo = 1;
		counter_tiempo = 0;
	}
	
	if(++counter_MEF==30){
		flag_MEF = 1;
		counter_MEF=0;
	}
	
	
}
void mandarTecla(){ //VOLAR A LA MIERDAAAAAAAAAAAAAAAAAA
	char tecla = 0;
	if(TECLADO_Actualizar(&tecla)){
		LCDsendChar(tecla);
	}
}