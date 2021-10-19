
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Pedido.h"
#include "utn.h"


/**
 * \brief Imprime los datos de una Publicacion
 * \param pElemento Puntero al producto que se busca imprimir
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_imprimir(Pedido* pElemento)
{
	int retorno=-1;
	if(pElemento != NULL){
		printf(" %-4.2f %20s \t%-4d\n",pElemento->cantidadTotal,pElemento->estado==PENDIENTE?"PENDIENTE":"COMPLETADO", pElemento->idCliente);
		retorno=0;
	}
	return retorno;
}

/**
 * \brief Imprime el array de Publicacion
 * \param array Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_imprimirArray(Pedido* array,int limite)
{
	int respuesta = -1;
	int i;
	int idConsola = 1;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		printf("\nID   CANT. TOTAL     ESTADO	IDCLIENTE\n"
				"----------------------------------------------\n");
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == CARGADO){
				printf("%-4d",idConsola++);
				ped_imprimir(&array[i]);
			}
		}
	}
	return respuesta;
}

/**
 * \brief Imprime el array de publicaciones de un cliente po idCliente
 * \param array Array de clientes a ser actualizado
 * \param limite Limite del array de clientes
 * \param idCliente id de array de clientes en array de publicaciones, valor a buscar.
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 *//*
int ped_imprimirArrayDeUnCliente(Pedido* array,int limite, int idCliente)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			if(array[i].idCliente == idCliente && array[i].isEmpty == 0)
			{
				ped_imprimir(&array[i]);
			}
		}
	}
	return respuesta;
}*/

/**
 * \brief Inicializa el array
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de clientes
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_inicializarArray(Pedido* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		respuesta = 0;
		for(i=0;i<limite;i++)
		{
			array[i].isEmpty = 1;
		}
	}
	return respuesta;
}

/**
 * \brief Da de alta una Publicacion en una posicion del array
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la pantalla
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_alta(Pedido* array,int limite, int indice, int* id, int idCliente)
{
	int respuesta = -1;
	Pedido bufferEntidad;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
		if(	!utn_getNumeroFlotante(&bufferEntidad.cantidadTotal,"\nIngrese la cantidad total a recolectar del Cliente: ", "\nERROR - Cantidad invalida!\n",0,1000,REINTENTO))
		{
			respuesta = 0;
			bufferEntidad.id = *id;
			bufferEntidad.idCliente = idCliente;
			bufferEntidad.estado = PENDIENTE;
			bufferEntidad.isEmpty = CARGADO;
			array[indice] = bufferEntidad;
			(*id)++;
		}
	}
	return respuesta;
}

/**
 * \brief Actualiza los datos de una Publicacion en una posicion del array
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de clientes
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_modificar(Pedido* array,int limite, int indice)
{
	int respuesta = -1;
	Pedido bufferEntidad;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && array[indice].isEmpty == 0)
	{
		if(	!utn_getNumero(&bufferEntidad.idCliente,"\nIngrese el ID del Cliente: \n", "\nERROR\n",0,PED_LEN,REINTENTO) &&
			!utn_getNumero(&bufferEntidad.estado,"\nIngrese el estado de la Publicidad?\n","\nERROR\n",0,1,REINTENTO))
		{
			respuesta = 0;
			bufferEntidad.id = array[indice].id;
			bufferEntidad.isEmpty = 0;
			array[indice] = bufferEntidad;
		}
	}
	return respuesta;
}

/**
 * \brief Actualiza una posicion del array
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \param indice Posicion a ser actualizada
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_baja(Pedido* array,int limite, int indice)
{
	int respuesta = -1;
	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && array[indice].isEmpty == 0)
	{
		array[indice].isEmpty = 1;
		respuesta = 0;
	}
	return respuesta;
}

/**
 * \brief Buscar primer posicion vacia
 * \param array Array de clientes
 * \param limite Limite del array de Pedido
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 *
 */
int ped_buscarEmptyVacio(Pedido* array,int limite)
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

/** \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param array cliente Array de Publicacion
* \param limite int Tamaño del array
* \param valorBuscado es el ID de publicidad a buscar   //int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - >= 0 (i) posicion de ID
*
*/
int ped_buscarId(Pedido array[], int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	int idConsola = 1;
	if(array != NULL && limite > 0 && valorBuscado >= 0 )
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

/** \brief Busca un ID de publicacion en un array y devuelve el idCliente
* \param array Array de publicacion
* \param limite int Tama�o del array
* \param valorBuscado es el ID de publicidad a buscar
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - >= 0 (i) ID de la publicacion
*
*/
int ped_buscarIdCliente(Pedido array[], int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0 && valorBuscado >= 0 )
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].id == valorBuscado && array[i].isEmpty == 0 )
			{
				respuesta = array[i].idCliente;
				break;
			}
		}
	}
	return respuesta;
}


/** \brief Busca un IDcliente en un array y devuelve la posicion en que se encuentra
* \param array publicacion Array de publicaciones
* \param limite int Tamaño del array
* \param  valorBuscado es el ID de publicidad a buscar
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - >= 0 (i) si encuentra el valor buscado
*
*/
int ped_buscarIdClientePos(Pedido array[], int limite, int valorBuscado)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0 && valorBuscado >= 0 )
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].idCliente == valorBuscado && array[i].isEmpty == 0 )
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}

/**
 * \brief Buscar primer posicion vacia
 * \param array Array de Publicacion
 * \param limite Limite del array de publicacion
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 *
 */
int ped_getEmptyIndex(Pedido* array,int limite)
{
	int respuesta = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == 1)
			{
				respuesta = i;
				break;
			}
		}
	}
	return respuesta;
}


/**
 * \brief modifica el estado de una publicacion a 0 (ACTIVA), con el id de publicacion
 * \param array Array de publicacion a ser actualizado
 * \param limite Limite del array de publicacion
 * \param idPublicacion Identificador a buscar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_modificarEstadoActivo(Pedido* array,int limite , int idPublicacion)
{
	int retorno = -1;
	int i;
	if(array != NULL && limite > 0 && idPublicacion >=0)
	{
		retorno = 0;
		for(i=0; i<limite ; i++)
		{
			if(array[i].id == idPublicacion && array[i].isEmpty == 0 && array[i].estado == 1)
			{
				array[i].estado = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief modifica el estado de una publicacion a 1 (PAUSADA), con el id de publicacion
 * \param array Array de publicacion a ser actualizado
 * \param limite Limite del array de publicacion
 * \param idPublicacion Identificador a buscar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_modificarEstadoPausado(Pedido* array,int limite , int idPublicacion)
{
	int retorno = -1;
	int i;
	if(array != NULL && limite > 0 && idPublicacion >=0)
	{
		retorno = 0;
		for(i=0; i<limite ; i++)
		{
			if(array[i].id == idPublicacion && array[i].isEmpty == 0 && array[i].estado == 0)
			{
				array[i].estado = 1;
				break;
			}
		}
	}
	return retorno;
}
/**
 * \brief se modifica isEmpty siempre que haya un idCliente
 * \param array Array de publicacion a ser actualizado
 * \param limite Limite del array de publicacion
 * \param id Identificador a buscar en array de publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_bajaPublicacionesPorId(Pedido* array,int limite,int id)
{
	int retorno = -1;
	int auxIndice;
	if(array != NULL && limite>0 && id >= 0)
	{
		retorno = 0;
		do
		{
			auxIndice = ped_buscarIdClientePos(array,limite,id);
			printf("%d",auxIndice);
			if(	auxIndice >= 0)
			{
				ped_baja(array,limite,auxIndice);
			}
		}while(auxIndice!=-1);
	}
	return retorno;
}

/**
 * \brief Da de alta una publicacion en una posicion del array
 * \param array Array de publicacion a ser actualizado
 * \param limite Limite del array de pantallas
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la pantalla
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int pub_altaForzadaArray(Pedido* array,int limite, int indice, int* id,float cantidadTotal,int estado,int idCliente, float hdpe, float ldpe, float pp)

{
	int respuesta = -1;
	Pedido bufferEntidad;

	if(array != NULL && limite > 0 && indice < limite && indice >= 0 && id != NULL)
	{
			bufferEntidad.cantidadTotal = cantidadTotal;
			bufferEntidad.estado = estado;
			bufferEntidad.idCliente = idCliente;
			respuesta = 0;
			bufferEntidad.id = *id;

			bufferEntidad.platicos.hdpe = hdpe;
			bufferEntidad.platicos.ldpe = ldpe;
			bufferEntidad.platicos.pp = pp;

			bufferEntidad.isEmpty = 0;

			array[indice] = bufferEntidad;
			(*id)++;
	}
	return respuesta;
}

/**
 * \brief obtiene el valor de cantidad total
 * \param array Array de publicacion a ser actualizado
 * \param limite Limite del array de publicacion
 * \param idPublicacion Identificador a buscar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int ped_cargarCantidadPlaticosUnCliete(Pedido* array,int limite , int indice)
{
	int retorno = -1;
	float cantTotal;
	Pedido bufferPedido;
	char respuesta[3];
	if(array != NULL && limite > 0 && indice >=0)
	{
		cantTotal = array[indice].cantidadTotal;
		if(!utn_getNumeroFlotante(&bufferPedido.platicos.hdpe,"\nIngrese la cantidad de Poliestileno de Alta densidad(HDPE): ","\nERROR - Cantidad invalida!\n",0,cantTotal,REINTENTO)){
			cantTotal -= bufferPedido.platicos.hdpe;
			if(!utn_getNumeroFlotante(&bufferPedido.platicos.ldpe,"\nIngrese la cantidad de Poliestileno de Baja densidad(LDPE): ","\nERROR - Cantidad invalida!\n",0,cantTotal,REINTENTO)){
				cantTotal -= bufferPedido.platicos.ldpe;
				if(!utn_getNumeroFlotante(&bufferPedido.platicos.pp,"\nIngrese la cantidad de Poliestileno de Baja densidad(PP): ","\nERROR - Cantidad invalida!\n",0,cantTotal,REINTENTO))
				{
					bufferPedido.estado = COMPLETADO;
					bufferPedido.id = cantTotal = array[indice].id;
					bufferPedido.idCliente =  array[indice].idCliente;
					bufferPedido.isEmpty = CARGADO;
					if( !utn_getRespuesta(respuesta, 3, "¿Esta seguro que quiere procesar el reciduo?(si / no): ", "ERROR - Respuesta incorrecta!\n",REINTENTO) &&
						strncmp(respuesta,"si",sizeof(respuesta)) == 0)
					{
						array[indice] = bufferPedido;
						retorno = 0;
					}
				}
			}
		}
	}
	return retorno;
}











