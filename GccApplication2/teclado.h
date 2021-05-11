/*
 * IncFile1.h
 *
 * Created: 08/05/2021 20:12:12
 *  Author: Juanjo
 */ 

#ifndef TECLADO_H
#define TECLADO_H
	
	#define PORT PORTB
	#define DDR DDRB
	#define PIN PINB
	
	void TECLADO_refrescar ();
	unsigned char TECLADO_tecla(unsigned char *pkey);


#endif