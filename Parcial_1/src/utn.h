/*
 * utn.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Mauro
 */

#ifndef UTN_H_
#define UTN_H_

#define REINTENTO 3
#define NUM_MIN 1
#define NUM_MAX 1000 //provisorio

int utn_getString(char* pResultado, char* mensaje, char* mensajeError, int len, int reintentos);
int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos);
int utn_getChar(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getCaracterImprimible(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getMail(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getCuilCuit(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getRespuesta(char* pRespuesta,int len, char* mensaje, char* mensajeError,int reintentos);
int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_getDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos);
int utn_toUpperArray(char* arrayEntada, int len);

void utn_generarMensajeConVariableInt(char* mensajeSalida, char* mensaje1, int var, char* mensaje2);

void mostrarArrayINT(int* pArray, int len);
void mostrarArrayCHAR(char* pArray, int len);
void mensajeProceso(int proceso, char* mensajeOperacion);
void utn_generarMensajeConVariableInt(char* mensajeSalida, char* mensaje1, int var, char* mensaje2);

#endif /* UTN_H_ */
