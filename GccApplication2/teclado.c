/*
 * CFile1.c
 *
 * Created: 08/05/2021 19:57:50
 *  Author: Juanjo
 */ 
/****************************************
* Conexion del teclado:
*
* FILA1 -> PORTB0
* FILA2 -> PORTB1
* FILA3 -> PORTB2
* FILA4 -> PORTB3
*
* COLUMNA1 -> PORTB4
* COLUMNA2 -> PORTB5
* COLUMNA3 -> PORTB6
* COLUMNA4 -> PORTB7
****************************************/
#include "derivative.h"
#include "teclado.h"
static unsigned char recorrer_fila;
static char teclaPresionada;
static unsigned char flagNuevaTecla; //avisa que se leyo una tecla, ambas variables evitan leer varias veces la misma tecla si se mantiene presionada
static unsigned char esperandoTecla; //avisa que ademas, la tecla leida fue nueva respecto a la lectura anterior, es decir, se produjo flanco ascendente
unsigned char KeypadScan (char *Key){ //escaneo del teclado
	unsigned char sePresiono_tecla = 0;
	unsigned char aux;
	PTBDD=0x0F; //setea las columnas como entradas y las filas como salidas
	PTBPE=0xF0; //habilita pull-up en las columnas
	switch(recorrer_fila){
		case 0:
		PTBD=0xFE; //coloca un nivel bajo en la primera fila y recorre las columnas
		aux=~PTBD; //cuando se presiona una tecla, llega un 0 a la entrada de la columna correspondiente
		if(aux&0x10){*Key='1';sePresiono_tecla=1;}
		if(aux&0x20){*Key='2';sePresiono_tecla=1;}
		if(aux&0x40){*Key='3';sePresiono_tecla=1;}
		if(aux&0x80){*Key='A';sePresiono_tecla=1;}
		recorrer_fila=1;
		break;
		case 1:
		PTBD=0xFD;
		aux=~PTBD;
		if(aux&0x10){*Key='4';sePresiono_tecla=1;}
		if(aux&0x20){*Key='5';sePresiono_tecla=1;}
		if(aux&0x40){*Key='6';sePresiono_tecla=1;}
		if(aux&0x80){*Key='B';sePresiono_tecla=1;}
		recorrer_fila=2;
		33
		break;
		case 2:
		PTBD=0xFB;
		aux=~PTBD;
		if(aux&0x10){*Key='7';sePresiono_tecla=1;}
		if(aux&0x20){*Key='8';sePresiono_tecla=1;}
		if(aux&0x40){*Key='9';sePresiono_tecla=1;}
		if(aux&0x80){*Key='C';sePresiono_tecla=1;}
		recorrer_fila=3;
		break;
		case 3:
		PTBD=0xF7;
		aux=~PTBD;
		if(aux&0x10){*Key='*';sePresiono_tecla=1;}
		if(aux&0x20){*Key='0';sePresiono_tecla=1;}
		if(aux&0x40){*Key='#';sePresiono_tecla=1;}
		if(aux&0x80){*Key='D';sePresiono_tecla=1;}
		recorrer_fila=0;
		break;
	}
	return sePresiono_tecla;
}
void TECLADO_Iniciar(void){
	recorrer_fila=0;
	flagNuevaTecla=0;
	esperandoTecla=1;
}
void TECLADO_Actualizar(void){
	char tecla=' ';
	if(KeypadScan(&tecla)==1){ //revisa si hubo una nueva tecla presionada y actualiza flag
		teclaPresionada=tecla;
		flagNuevaTecla=1;
		}else{
		esperandoTecla=1; //cuando se deja de presionar se reinicia el flag y pasa a esperar tecla nueva
	}
}
unsigned char TECLADO_getKey(char *auxKey){
	if((flagNuevaTecla==1)&&(esperandoTecla==1)){ //la unica manera de acceder es con el flanco ascendente al presionar nueva tecla (evitando leer teclas repetidas por mantener presionado)
		*auxKey=teclaPresionada;
		flagNuevaTecla=0; //de esta manera se asegura de no repetir lecturas
		esperandoTecla=0;
		return 1;
		}else{
		return 0;
	}
}