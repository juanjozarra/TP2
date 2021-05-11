/*
 * GccApplication2.c
 *
 * Created: 08/05/2021 15:05:00
 * Author : Juanjo
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "lcd.h"
#include "teclado.h"
#include "SEOS.h"



int main(void)
{
	//INICIALIZAR COSAS
	LCD_Init();
	SEOSTimer0Init();	
	
    while (1) 
    {
		//DISPACHER
		SEOSDispatcherTasks();	
		
    }
}