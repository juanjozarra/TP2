/*
* MEF.c
*
* Created: 10/05/2021 12:58:54
*  Author: tomas
*/
#include "MEF.h"
#include "lcd.h"
#include "reloj.h"
#include "teclado.h"


typedef enum {
	DEFAULT,
	SET_HORA,
	SET_MIN,
	SET_SEG,
	READ_PASS,
	DENY,
	OPEN,
	OLD_PASS,
	NEW_PASS,
}ENUMS;

static void STATE_default();
static void STATE_setHora();
static void STATE_setMIN();
static void STATE_setSEG();

ENUMS STATE = DEFAULT;

extern unsigned char tiempo_String[];
volatile unsigned char tecla, nueva_tecla = 0;
static unsigned char key[4] = {'0','8','5','2'};
static unsigned char aux_key[4];
extern unsigned char tiempo[6];


void MEF_actualizar(){
	switch (STATE)
	{
		case DEFAULT:
			STATE_default();
		break;
		case SET_HORA: 
			STATE_setHora();	
		break;
		case SET_MIN:
			STATE_setMIN();
		break;			
	}	
}


void STATE_default(){
	LCDclr();
	LCDstring(tiempo_String,8);
	unsigned char cerrado[]="CERRADO";
	LCDGotoXY(9,1);
	LCDstring(cerrado,7);
	if(nueva_tecla){
		switch (tecla){
			case 'A':
			STATE = SET_HORA;
			break;
			case 'B':
			STATE = SET_MIN;
			break;
			case 'C':
			STATE = SET_SEG;
			break;
			case 'D':
			STATE = OLD_PASS;
			break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			aux_key[0] = tecla;
			STATE = READ_PASS;
			break;
		}
	}
}

void STATE_setHora(){
	LCDclr();
	LCDcursorOFF();
	static unsigned char aux_hora[2] = {0,0};
	LCDstring(tiempo_String,8);
	if (!aux_hora[0]){
		LCDGotoXY(0,0);
		LCDcursorOnBlink();
	} else {
		if(!aux_hora[1]){
			LCDGotoXY(0,0);
			LCDsendChar(aux_hora[0]);
			LCDcursorOnBlink();
		} else {
			LCDGotoXY(0,0);
			LCDstring(aux_hora, 2);
		}
	}
	if (nueva_tecla){
		switch (tecla){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (!aux_hora[0]){
					aux_hora[0] = tecla;
				} else {
					if (!aux_hora[1])
						aux_hora[1] = tecla;
					}
			break;
			case 'A':
				if (aux_hora[0] && aux_hora[1]) {
					if (aux_hora[0] < '2' || (aux_hora[0] == '2' && aux_hora[1] < '4')){
						tiempo[0] = aux_hora[0] - '0';
						tiempo[1] = aux_hora[1] - '0';
						tiempo_String[0] = aux_hora[0];
						tiempo_String[1] = aux_hora[1];
					}
					aux_hora[0] = 0;
					aux_hora[1] = 0;
					LCDcursorOFF();
					STATE = DEFAULT; 
										
				}
			break;
			case '#':
				aux_hora[0] = 0;
				aux_hora[1] = 0;
				LCDcursorOFF();
				STATE = DEFAULT;
			break;
		}
	}
}


void STATE_setMIN(){
	LCDclr();
	LCDcursorOFF();
	static unsigned char aux_min[2] = {0,0};
	LCDstring(tiempo_String,8);
	if (!aux_min[0]){
		LCDGotoXY(3,0);
		LCDcursorOnBlink();
		} else {
		if(!aux_min[1]){
			LCDGotoXY(3,0);
			LCDsendChar(aux_min[0]);
			LCDcursorOnBlink();
			} else {
			LCDGotoXY(3,0);
			LCDstring(aux_min, 2);
		}
	}
	if (nueva_tecla){
		switch (tecla){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			if (!aux_min[0]){
				aux_min[0] = tecla;
				} else {
				if (!aux_min[1])
				aux_min[1] = tecla;
			}
			break;
			case 'B':
			if (aux_min[0] && aux_min[1]) {
				if (aux_min[0] < '6'){
					tiempo[2] = aux_min[0] - '0';
					tiempo[3] = aux_min[1] - '0';
					tiempo_String[3] = aux_min[0];
					tiempo_String[4] = aux_min[1];
				}
				aux_min[0] = 0;
				aux_min[1] = 0;
				LCDcursorOFF();
				STATE = DEFAULT;
				
			}
			break;
			case '#':
			aux_min[0] = 0;
			aux_min[1] = 0;
			LCDcursorOFF();
			STATE = DEFAULT;
			break;
		}
	}
}

void STATE_setSEG(){
	LCDclr();
	LCDcursorOFF();
	static unsigned char aux_seg[2] = {0,0};
	LCDstring(tiempo_String,8);
	if (!aux_seg[0]){
		LCDGotoXY(6,0);
		LCDcursorOnBlink();
		} else {
		if(!aux_seg[1]){
			LCDGotoXY(6,0);
			LCDsendChar(aux_seg[0]);
			LCDcursorOnBlink();
			} else {
			LCDGotoXY(6,0);
			LCDstring(aux_seg, 2);
		}
	}
	if (nueva_tecla){
		switch (tecla){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			if (!aux_seg[0]){
				aux_seg[0] = tecla;
				} else {
				if (!aux_seg[1])
				aux_seg[1] = tecla;
			}
			break;
			case 'C':
			if (aux_seg[0] && aux_seg[1]) {
				if (aux_seg[0] < '6'){
					tiempo[4] = aux_seg[0] - '0';
					tiempo[5] = aux_seg[1] - '0';
					tiempo_String[6] = aux_seg[0];
					tiempo_String[7] = aux_seg[1];
				}
				aux_seg[0] = 0;
				aux_seg[1] = 0;
				LCDcursorOFF();
				STATE = DEFAULT;
				
			}
			break;
			case '#':
			aux_seg[0] = 0;
			aux_seg[1] = 0;
			LCDcursorOFF();
			STATE = DEFAULT;
			break;
		}
	}
}

