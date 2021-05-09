/*
 * IncFile1.h
 *
 * Created: 08/05/2021 20:12:12
 *  Author: Juanjo
 */ 

#ifndef TECLADO_H
#define TECLADO_H
	#include <avr/io.h>
	#define PORT PORTB
	#define DDR DDRB
	#define PIN PINB

	char TECLADO_Actualizar(char *pkey);

#endif