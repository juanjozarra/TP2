/*
 * IncFile1.h
 *
 * Created: 08/05/2021 20:12:12
 *  Author: Juanjo
 */ 


#ifndef	TECLADO_H_
#define TECLADO_H_

void TECLADO_Iniciar(void);
void TECLADO_Actualizar(void);
unsigned char KeypadScan (char *Key);
unsigned char TECLADO_getKey(char *auxKey);



#endif 