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


int main(void)
{
	char tecla =0;
	LCDinit();
	LCDclr();
	LCDhome();
	
    while (1) 
    {
		TECLADO_Actualizar(&tecla);
		if(1){
			LCDsendChar(tecla);
		}
		_delay_ms(100);	
		
    }
}

