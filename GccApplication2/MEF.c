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
	SUCCESS_UPDATE
}ENUMS;

static void STATE_default();
static void STATE_setHora();
static void STATE_setMIN();
static void STATE_setSEG();
static void STATE_deny();
static void STATE_open();
static void STATE_successUpdate();
static void STATE_oldPass();
static void STATE_newPass();
static void STATE_readPass();


ENUMS STATE = DEFAULT;

extern unsigned char tiempo_String[];
extern unsigned char tiempo[6];
extern unsigned char tecla;
extern unsigned char nueva_tecla;

static unsigned char key[4] = {'0','8','5','2'};
static unsigned char aux_key[4];



void MEF_actualizar(){ //Metodo que actualiza el estado de la maquina
	switch (STATE) //Segun el estado actual de la maquina se llama al metodo correspondiente
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
		case SET_SEG:
			STATE_setSEG();
			break;
		case DENY:
			STATE_deny();
			break;
		case OPEN:
			STATE_open();
			break;
		case READ_PASS:
			STATE_readPass();
			break;
		case OLD_PASS:
			STATE_oldPass();
			break;
		case NEW_PASS:
			STATE_newPass();
			break;
		case SUCCESS_UPDATE:
			STATE_successUpdate();
		break;
	}
}


void STATE_default(){
	//Se muestra la informacion en pantalla
	LCDclr();
	LCDstring(tiempo_String,8); 
	static unsigned char cerrado[]="CERRADO";
	LCDGotoXY(9,1);
	LCDstring(cerrado,7);
	
	//Si se presiono una tecla cambia el estado al correspondiente
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
			aux_key[0] = tecla; //Se almacena ya el primer valor del ingreso de la clave
			STATE = READ_PASS;
			break;
		}
	}
}

void STATE_setHora(){
	//Se muestra la informacion en pantalla
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
	
	//Si se presiono una tecla valida realiza la accion correspondiente
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
			//Si no se ingreso ya, almacena el valor para la hora
			if (!aux_hora[0]){
				aux_hora[0] = tecla;
				} else {
				if (!aux_hora[1])
				aux_hora[1] = tecla;
			}
			break;
			case 'A':
			//Guarda en el reloj el valor almacenado si ingreso una hora valida y vuelve al estado default
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
			case '#': // Vuelve al estado default sin guardar la hora
			aux_hora[0] = 0;
			aux_hora[1] = 0;
			LCDcursorOFF();
			STATE = DEFAULT;
			break;
		}
	}
}


void STATE_setMIN(){
	//Se muestra la informacion en pantalla
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
	//Si se presiono una tecla valida realiza la accion correspondiente
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
			//Si no se ingreso ya, almacena el valor para los minutos
			if (!aux_min[0]){
				aux_min[0] = tecla;
				} else {
				if (!aux_min[1])
				aux_min[1] = tecla;
			}
			break;
			case 'B':
			//Guarda en el reloj el valor almacenado si ingreso minutos validos y vuelve al estado default
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
			// Vuelve al estado default sin guardar los minutos
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

void STATE_deny(){
	LCDclr();
	static unsigned char msj []= "DENEGADO";
	static unsigned char counter = 0;
	LCDstring(msj,8);
	if(++counter == 4){
		STATE = DEFAULT;
		counter = 0;
	}
}

void STATE_open(){	
		LCDclr();
		LCDstring(tiempo_String,8);
		unsigned char abierto[]="ABIERTO";
		LCDGotoXY(9,1);
		LCDstring(abierto,7);
		static unsigned char counter = 0;
		if(++counter == 6){
			STATE = DEFAULT;
			counter = 0;
		}
		
		
}

void STATE_successUpdate(){
	LCDclr();
	unsigned char msj1[]="FIN INGRESO";
	unsigned char msj2[]= "NUEVA CLAVE";
	LCDstring(msj1,11);
	LCDGotoXY(0,1);
	LCDstring(msj2,11);	
	static unsigned char counter = 0;
	if(++counter == 6){
		STATE = DEFAULT;
		counter = 0;
	}	
}


void STATE_oldPass(){
	LCDclr();
	static unsigned char indice = 0;
	static unsigned char msj [] = "CLAVE ACTUAL:";
	LCDstring(msj,13);
	LCDGotoXY(0,1);
	if(aux_key[0]){
		LCDsendChar('*');
	}
	if(aux_key[1]){
		LCDsendChar('*');
	}
	if(aux_key[2]){
		LCDsendChar('*');
	}
	LCDcursorOnBlink();
	if(nueva_tecla){
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
			aux_key[indice] = tecla;
			LCDsendChar('*');
			indice++;
			if(indice==4){ //ingreso toda la clave
				indice = 0;
				if((aux_key[0]==key[0])&&(aux_key[1]==key[1])&&(aux_key[2]==key[2])&&(aux_key[3]==key[3])){
					STATE = NEW_PASS;
				}
				else{
					STATE = DENY;
				}
				aux_key[0]=0;
				aux_key[1]=0;
				aux_key[2]=0;
				aux_key[3]=0;
				indice=0;
			}
			break;
			case '#':
			aux_key[0]=0;
			aux_key[1]=0;
			aux_key[2]=0;
			aux_key[3]=0;
			indice=0;
			STATE = DEFAULT;
			break;
		}
		
	}
	LCDcursorOFF();
}
void STATE_newPass(){
		LCDclr();
		static unsigned char indice = 0;
		static unsigned char msj [] = "CLAVE NUEVA:";
		LCDstring(msj,12);
		LCDGotoXY(0,1);
		if(aux_key[0]){
			LCDsendChar('*');
		}
		if(aux_key[1]){
			LCDsendChar('*');
		}
		if(aux_key[2]){
			LCDsendChar('*');
		}
		LCDcursorOnBlink();
		if(aux_key[3]){
			LCDsendChar('*');
			LCDcursorOFF();
		}
		
		if(nueva_tecla){
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
				if(indice<4){
					aux_key[indice] = tecla;
					LCDsendChar('*');
					indice++;
				}
				break;
				case '#':
				STATE = DEFAULT;
					aux_key[0]=0;
					aux_key[1]=0;
					aux_key[2]=0;
					aux_key[3]=0;
					indice =0;
				break;
				case 'D':
				STATE = SUCCESS_UPDATE;
					key[0]=aux_key[0];
					key[1]=aux_key[1];
					key[2]=aux_key[2];
					key[3]=aux_key[3];
					aux_key[0]=0;
					aux_key[1]=0;
					aux_key[2]=0;
					aux_key[3]=0;
					indice =0;
				break;
			}
			
		}
		LCDcursorOFF();
}
void STATE_readPass(){
	LCDclr();
	static unsigned char indice = 1;
	LCDsendChar('*');
	if(aux_key[1]){
		LCDsendChar('*');
	}
	if(aux_key[2]){
		LCDsendChar('*');
	}
	LCDcursorOnBlink();
	if(nueva_tecla){
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
				aux_key[indice] = tecla;
				LCDsendChar('*');
				indice++;	
				if(indice==4){ //ingreso toda la clave
					indice = 1;
					if((aux_key[0]==key[0])&&(aux_key[1]==key[1])&&(aux_key[2]==key[2])&&(aux_key[3]==key[3])){
						STATE = OPEN;						
					}
					else{
						STATE = DENY;
					}
					aux_key[0]=0;
					aux_key[1]=0;
					aux_key[2]=0;
					aux_key[3]=0;
				}			
			break;		
		}
				
	}
	LCDcursorOFF();	
}