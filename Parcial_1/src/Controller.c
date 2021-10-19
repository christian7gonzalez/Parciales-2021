/*
 * Controller.c
 *
 *  Created on: 13 oct. 2021
 *      Author: chgonzalez
 */
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "Cliente.h"
#include "Pedido.h"

/**
 * \brief Administra el alta de un cliente.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param idAutomatico se pasa un idincremental
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int controllerAltaCliente(Cliente* array, int limite, int* idAutomatico)
{
	int retorno = -1;
	int indice = -1;
	int rtn;

	if(array != NULL && limite > 0 && idAutomatico != NULL)
	{
		indice = cli_buscarEmptyVacio(array, limite);
		if(indice >= 0)
		{
			rtn = cli_alta(array, limite, indice, idAutomatico);
			mensajeProceso(rtn, "Alta");
			retorno = 0;
		}

	}
	return retorno;
}
/**
 * \brief Administra la modificacion de un cliente.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int controllerModificarCliente(Cliente* array, int limite){
	int retorno = -1;
	int id;
	int indice;
	char mensaje[500];
	char respuesta[3];
	int rtn;
	if(array != NULL && limite > 0)
	{
		if(!cli_imprimirArray(array,limite)){
			if(!utn_getNumero(&id,"\nIngrese el id a modificar: ","\nERROR - ID invalido!\n",NUM_MIN, CLI_LEN, REINTENTO)){
				utn_generarMensajeConVariableInt(mensaje, "¿Esta seguro que quiere remover el id",id,"?(si / no): ");
				indice = cli_buscarId(array, limite, id);
				if( !utn_getRespuesta(respuesta, 3, mensaje, "ERROR - Respuesta incorrecta!\n",REINTENTO) &&
					strncmp(respuesta,"si",sizeof(respuesta)) == 0)
				{
					rtn = cli_modificar(array, limite, indice);
					mensajeProceso(rtn, "Modificacion");
					retorno = 0;
				}
			}
		}

	}
	return retorno;
}
/**
 * \brief Administra la baja de un cliente.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int controllerBajaCliente(Cliente* array, int limite){
	int retorno = -1;
	int id;
	int indice;
	char mensaje[500];
	char respuesta[3];
	int rtn;
	if(array != NULL && limite > 0)
	{
		if(!cli_imprimirArray(array,limite)){
			if(!utn_getNumero(&id,"\nIngrese el id a eliminar: ","\nERROR - ID invalido!\n",NUM_MIN, CLI_LEN, REINTENTO)){
				utn_generarMensajeConVariableInt(mensaje, "¿Esta seguro que quiere eliminar el id",id,"?(si / no): ");
				indice = cli_buscarId(array, limite, id);
				if( !utn_getRespuesta(respuesta, 3, mensaje, "ERROR - Respuesta incorrecta!\n",REINTENTO) &&
					strncmp(respuesta,"si",sizeof(respuesta)) == 0)
				{
					rtn = cli_baja(array, limite, indice);
					mensajeProceso(rtn, "Eliminacion");
					retorno = 0;
				}
			}
		}

	}
	return retorno;
}
/**
 * \brief Administra la baja de un cliente.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param array Array de Peidos a recorrer
 * \param limite Limite del array de Peidos
 * \param idAutomatico se pasa un idincremental
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int controllerCrearPedido(Cliente* arrayCliente, int limiteCliente, Pedido* array, int limite, int* idAutomatico)
{
	int retorno = -1;
	int indiceCliete = -1;
	int indiceVacio = -1;
	int id;
	int rtn;
	if(array != NULL && limite > 0 && idAutomatico != NULL)
	{
		if(!cli_imprimirArray(arrayCliente,limiteCliente))
		{
			if(!utn_getNumero(&id,"\nIngrese el idCliente a cargar Pedido: ","\nERROR - ID invalido!\n",NUM_MIN, CLI_LEN, REINTENTO)){
				indiceCliete = cli_buscarId(arrayCliente, limiteCliente, id);
				indiceVacio = ped_buscarEmptyVacio(array, limite);
				if(indiceVacio > -1 && indiceCliete > -1)
				{
					rtn = ped_alta(array, limite, indiceVacio, idAutomatico, arrayCliente[indiceCliete].id);
					mensajeProceso(rtn, "Alta de pedido");
					retorno = 0;
				}else if(indiceCliete == -1){
					printf("\nERROR - No existe el id!\n");
				}else{
					printf("\nERROR - No hay espacio en el array!\n");
				}
			}
		}

	}
	return retorno;
}
/**
 * \brief Administra el proceso de reciduo de un Pedido.
 * \param array Array de Pedido a recorrer
 * \param limite Limite del array de Pedido
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int controllerProcesarReciduo(Pedido* array, int limite)
{
	int retorno = -1;
	int indicePed = -1;
	int id;
	int rtn;


	if(array != NULL && limite > 0)
	{
		if(!ped_imprimirArray(array,limite))
		{
			if(!utn_getNumero(&id,"\nIngrese el id del Pedido: ","\nERROR - ID invalido!\n",NUM_MIN, CLI_LEN, REINTENTO)){
				indicePed = ped_buscarId(array,limite, id);
				if(indicePed > -1)
				{
					rtn = ped_cargarCantidadPlaticosUnCliete(array, limite, indicePed);
					mensajeProceso(rtn, "Procesar Reciduo");
					retorno = 0;
				}
				else{
					printf("\nERROR - No existe el id!\n");
				}
			}
		}

	}
	return retorno;
}

