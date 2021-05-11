/*
* reloj.c
*
* Created: 10/05/2021 12:33:53
*  Author: tomas
*/
#include "reloj.h"
volatile unsigned char tiempo [6] = {0,0,0,0,0,0};
volatile char tiempo_String[]="00:00:00";

void RELOJ_Actualizar(void){ //Metodo que incrementa en 1 seg la hora y lo almacena en un string y un vector
	if(++tiempo[5]>9){
		tiempo[5]=0;
		if(++tiempo[4]>5){
			tiempo[4]=0;
			if(++tiempo[3]>9){
				tiempo[3]=0;
				if(++tiempo[2]>5){
					tiempo[2]=0;
					if((++tiempo[1]>9) && (tiempo[0]<2)){
						tiempo[1]=0;
						tiempo[0]++;
					}
					else{
						if((tiempo[0]==2) && (tiempo[1]>3)){
							tiempo[1]=0;
							tiempo[0]=0;
						}
					}
					tiempo_String[0]=tiempo[0] + '0'; //Almacenamiento en el string, digitos independientes
					tiempo_String[1]=tiempo[1] + '0';
				}
			}
			tiempo_String[3]=tiempo[2] + '0';
			tiempo_String[4]=tiempo[3] + '0';
		}
	}
	tiempo_String[6]=tiempo[4] + '0';
	tiempo_String[7]=tiempo[5] + '0';
}