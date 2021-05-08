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


int main(void)
{
	LCDinit();
	LCDclr();
	LCDhome();
	
    while (1) 
    {
		_delay_ms(100);
		LCDsendChar('1');	
    }
}

