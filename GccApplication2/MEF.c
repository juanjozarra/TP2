/*
 * MEF.c
 *
 * Created: 10/05/2021 12:58:54
 *  Author: tomas
 */ 
#include "MEF.h"
#include "lcd.h"
#include "reloj.h"

extern unsigned char tiempo_String[];

void MEF_actualizar(){
	LCDclr();
	LCDstring(tiempo_String,8);
}
