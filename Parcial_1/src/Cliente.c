#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cliente.h"
#include "utn.h"

/**
 * \brief Imprime los datos de un cliente
 * \param pElemento Puntero al producto que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_imprimir(Cliente* pElemento)
{
	int retorno=-1;
	if(pElemento != NULL )
	{
		retorno=0;
		printf(" %-10s %-13s %-22s %-20s",pElemento->nombreEmpresa,pElemento->cuit,pElemento->direccion, pElemento->localidad);
	}
	return retorno;
}

/**
 * \brief Imprime el array de clientes
 * \param array Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_imprimirArray(Cliente* array,int limite)
{
	int respuesta = -1;
	int i;
	int idConsola = 1;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		printf("\nID   EMPRESA	CUIT	      DIRECCION		     LOCALIDAD\n"
			   "--------------------------------------------------------------\n");
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == CARGADO){
				printf("%-4d",idConsola++);
				cli_imprimir(&array[i]);
			}
		}
	}
	return respuesta;
}


/**
 * \brief Inicializa el array
 * \param array Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_inicializarArray(Cliente* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			array[i].isEmpty = VACIO;
		}
	}
	return respuesta;
}

/**
 * \brief Da de alta un cliente en una posicion del array
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de pantallas
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la pantalla
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_alta(Cliente* array,int limite, int indice, int* id)
{
	int respuesta = -1;
	Cliente bufferEntidad;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		if(	!utn_getNombre(bufferEntidad.nombreEmpresa,NOMBRE_LEN,"\nIngrese el nombre de Empresa del Cliente: ","\nERROR - Nombre invalido!\n",REINTENTO) &&
			!utn_getCuilCuit(bufferEntidad.cuit, CUIT_LEN,"Ingrese el cuit del Cliente: ","\nERROR - Cuit invalido!\n",2) &&
			!utn_getString(bufferEntidad.direccion, "Ingrese la direccion del Cliente: ","\nERROR - Direccion invalida!\n", DIRE_LEN, REINTENTO) &&
			!utn_getString(bufferEntidad.localidad, "Ingrese la localidad del Cliente: ","\nERROR - Localidad invalida!\n", LOCALIDAD_LEN, REINTENTO))
		{
			utn_toUpperArray(bufferEntidad.localidad, LOCALIDAD_LEN);
			respuesta = 0;
			bufferEntidad.id = *id;
			bufferEntidad.isEmpty = CARGADO;
			array[indice] = bufferEntidad;
			(*id)++;
		}
	}
	return respuesta;
} //20*94213754-1

/**
 * \brief Actualiza los datos de un cliente en una posicion del array
 * \param array Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_modificar(Cliente* array,int limite, int indice)
{
	int respuesta = -1;
	Cliente bufferEntidad;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && array[indice].isEmpty == CARGADO)
	{
		if(	!utn_getString(bufferEntidad.direccion,"\nIngrese la direccion nueva del Cliente: ","\nERROR - Direccion invalida!\n",DIRE_LEN, REINTENTO) &&
			!utn_getString(bufferEntidad.localidad,"\nIngrese la localidad nueva del Cliente: ","\nERROR - Localidad invalida!\n",LOCALIDAD_LEN, REINTENTO))
		{
			respuesta = 0;
			bufferEntidad.id = array[indice].id;
			strncpy(bufferEntidad.nombreEmpresa, array[indice].nombreEmpresa, sizeof(bufferEntidad.nombreEmpresa));
			strncpy(bufferEntidad.cuit, array[indice].cuit, sizeof(bufferEntidad.cuit));
			bufferEntidad.isEmpty = CARGADO;
			array[indice] = bufferEntidad;
		}
	}
	return respuesta;
}

/**
 * \brief Actualiza una posicion del array
 * \param array Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_baja(Cliente* array,int limite, int indice)
{
	int respuesta = -1;
	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && array[indice].isEmpty == 0)
	{
		array[indice].isEmpty = VACIO;
		respuesta = 0;
	}
	return respuesta;
}


/** \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param array cliente Array de cliente
* \param limite int Tamaño del array
* \param posicion int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*
*/
int cli_buscarId(Cliente array[], int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	int idConsola = 1;
	if(array != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == CARGADO)
			{
				if(idConsola == valorBuscado){
					respuesta = i;
					break;
				}
				idConsola++;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Buscar primer posicion vacia
 * \param array Array de clientes
 * \param limite Limite del array de clientes
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 *
 */
int cli_buscarEmptyVacio(Cliente* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == VACIO)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}


/**
 * \brief Da de alta un cliente en una posicion del array
 * \param array Array de cliente a ser actualizado
 * \param limite Limite del array de pantallas
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la pantalla
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cli_altaForzadaArray(Cliente* array,int limite, int indice, int* id,char* nombreEmpresa,char* cuit, char* direccion, char* localidad)

{
	int respuesta = -1;
	Cliente bufferEntidad;
	char localidadAux[LOCALIDAD_LEN];
	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		strncpy(localidadAux,localidad,LOCALIDAD_LEN);
		utn_toUpperArray(localidadAux,LOCALIDAD_LEN);
		strncpy(bufferEntidad.nombreEmpresa,nombreEmpresa,NOMBRE_LEN);
		strncpy(bufferEntidad.cuit,cuit,CUIT_LEN);
		strncpy(bufferEntidad.direccion,direccion,DIRE_LEN);
		strncpy(bufferEntidad.localidad,localidadAux,LOCALIDAD_LEN);
		respuesta = 0;
		bufferEntidad.id = *id;
		bufferEntidad.isEmpty = CARGADO;
		array[indice] = bufferEntidad;
		(*id)++;
	}
	return respuesta;
}

/**
 * \brief Se verifica que el array tenga un cliente cargado
 * \param array Array de cliente a ser actualizado
 * \param limite Limite del array de pantallas
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int validarArrayCargado(Cliente* array,int limite){
	int retorno = -1;
	if(array != NULL && limite > 0)
	{
		for(int i=0; i<limite; i++)
		{
			if(array[i].isEmpty == CARGADO)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}













