/*
 * CFile1.c
 *
 * Created: 08/05/2021 19:57:50
 *  Author: Juanjo
 */ 
#include "teclado.h"
#include <avr/io.h>

volatile unsigned char nueva_tecla = 0;
volatile unsigned char tecla;

	unsigned char TECLADO_Actualizar(unsigned char *pkey);
	unsigned char KeypadScan (unsigned char *Key);
	

unsigned char KeypadScan (unsigned char *Key){ //escaneo del teclado
	unsigned char teclaPresionada=0;
	unsigned char aux;
	DDR=0b00001111; //setea las columnas como entradas y las filas como salidas
	PORT=0b11110000; //habilita pull-up en las columnas
	
	for (unsigned char filaActual=0; filaActual<=3; filaActual++){
	switch(filaActual){
		case 0:
			PORT=0b11111110; //coloca un nivel bajo solo en la primera fila y recorre las columnas
			aux=~PIN; //cuando se presiona una tecla, llega un 0 a la entrada de la columna correspondiente, invierto los bits para que me quede un 1 en la entrada de la columna correspondiente
			if(aux&0b00010000){*Key='1';teclaPresionada=1;}
			if(aux&0b00100000){*Key='2';teclaPresionada=1;}
			if(aux&0b01000000){*Key='3';teclaPresionada=1;}
			if(aux&0b10000000){*Key='A';teclaPresionada=1;}
		break;
		case 1:
			PORT=0b11111101;
			aux=~PIN;
			if(aux&0b00010000){*Key='4';teclaPresionada=1;}
			if(aux&0b00100000){*Key='5';teclaPresionada=1;}
			if(aux&0b01000000){*Key='6';teclaPresionada=1;}
			if(aux&0b10000000){*Key='B';teclaPresionada=1;}
		break;
		case 2:
			PORT=0b11111011;
			aux=~PIN;
			if(aux&0b00010000){*Key='7';teclaPresionada=1;}
			if(aux&0b00100000){*Key='8';teclaPresionada=1;}
			if(aux&0b01000000){*Key='9';teclaPresionada=1;}
			if(aux&0b10000000){*Key='C';teclaPresionada=1;}
		break;
		case 3:
			PORT=0b11110111;
			aux=~PIN;
			if(aux&0b00010000){*Key='*';teclaPresionada=1;}
			if(aux&0b00100000){*Key='0';teclaPresionada=1;}
			if(aux&0b01000000){*Key='#';teclaPresionada=1;}
			if(aux&0b10000000){*Key='D';teclaPresionada=1;}
		break;
	}
		}
	
	return teclaPresionada;
}

unsigned char TECLADO_Actualizar(unsigned char *pkey){
	static unsigned char teclaAnterior = 0xFF;  //Inicializo como que no hubo tecla seleccionada
	static unsigned char ultimaTeclaValida=0xFF; //Inicializo como que no hubo tecla seleccionada
	unsigned char aux_tecla;
	
	if(!KeypadScan(&aux_tecla)){ //Si no se presiono una tecla
		teclaAnterior=0xFF;
		ultimaTeclaValida=0xFF;
		return 0;
	}
	
	if(aux_tecla==teclaAnterior){ //Segunda Verificacion
		if(aux_tecla!=ultimaTeclaValida){
			*pkey=aux_tecla;
			ultimaTeclaValida=aux_tecla;
			return 1;
		}
	}
	teclaAnterior=aux_tecla; //Primera verificacion
	return 0;
}

void TECLADO_refrescar (){ //Metodo que actualiza las variable globales 
	unsigned char aux_tecla;
	nueva_tecla = TECLADO_Actualizar(&aux_tecla);
	tecla = aux_tecla;
}
