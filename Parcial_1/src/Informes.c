#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Cliente.h"
#include "Pedido.h"
#include "Informes.h"
#include "utn.h"

//static const char PED_ESTADO[2][10]={"PROCESADA","PENDIENTE"};
static int crearListaLocalidades(char arrayLocalidad[][100],int len, Cliente* arrayPed, int limitePed);
static int crearListaId(int arrayId[],int len, Pedido* arrayPed, int limitePed);

/**
 * \brief Imprime datos del cliente junto con la cantidad de pedidos
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param arrayPed Array de Pedidos a recorrer
 * \param limite Limite del array de Pedidos
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirArrayConCantPedidos(Cliente* arrayCli, int limiteCli, Pedido* arrayPub, int limitePed)
{
	int retorno = -1;
	int idConsola = 1;
	int cantPed = 0;
	if(arrayCli != NULL && limiteCli > 0 && arrayPub != NULL && limitePed > 0){
		printf("\nID    EMPRESA	 CUIT	       DIRECCION	      LOCALIDAD		   CANTIDAD DE PEDIDOS\n"
				 "-------------------------------------------------------------------------------------------------\n");
		for(int i=0; i < limiteCli; i++)
		{
			for(int j=0; j < limitePed; j++)
			{
				if(arrayCli[i].isEmpty == CARGADO &&
					arrayCli[i].id == arrayPub[j].idCliente && arrayPub[j].estado == PENDIENTE )
				{
					cantPed++;
				}
			}
			if(cantPed>0){
				printf("%-4d ",idConsola++);
				cli_imprimir(&arrayCli[i]);
				printf(" %-5d\n", cantPed);
				cantPed = 0;
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Imprime cada pedido con el cuit que le pertenece a cada una.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param arrayCli Array de Publicacion a recorrer
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirPedidosPendientes(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed)
{
	int retorno = -1;
	//int idCliente;
	//int auxIndice;
	//int idConsola = 1;
	if(arrayCli != NULL && limiteCli > 0 && arrayPed != NULL && limitePed > 0)
	{
		retorno = 0;
		printf("\nCUIT         DIRECCION          CANT.TOTAL"
			   "\n-------------------------------------------------");
		for(int i=0;i<limiteCli;i++)
		{
			for(int j=0;j<limitePed; j++)
			{
				if(arrayCli[i].isEmpty == CARGADO && arrayPed[j].isEmpty == CARGADO &&
				   arrayPed[j].estado == PENDIENTE && arrayCli[i].id == arrayPed[j].idCliente)
				{
					printf("\n%s  %-15s \t%.2f",arrayCli[i].cuit, arrayCli[i].direccion,arrayPed[i].cantidadTotal);
				}
			}
		}
	}
	return retorno;
}
/**
 * \brief Imprime cada pedido con el cuit que le pertenece a cada una.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param arrayCli Array de Publicacion a recorrer
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirPedidosProcesados(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed)
{
	int retorno = -1;
	//int idCliente;
	//int auxIndice;
	if(arrayCli != NULL && limiteCli > 0 && arrayPed != NULL && limitePed > 0)
	{
		retorno = 0;
		printf("\nCUIT         DIRECCION          C.HDPE  C.LDPE  C.PP"
			   "\n-----------------------------------------------------");
		for(int i=0;i<limiteCli;i++)
		{
			for(int j=0;j<limitePed; j++)
			{
				if(arrayCli[i].isEmpty == CARGADO && arrayPed[j].isEmpty == CARGADO &&
				   arrayPed[j].estado == COMPLETADO && arrayCli[i].id == arrayPed[j].idCliente)
				{
					printf("\n%s  %-15s \t%.2f \t%.2f \t%.2f",arrayCli[i].cuit, arrayCli[i].direccion,arrayPed[i].platicos.hdpe,arrayPed[i].platicos.ldpe,arrayPed[i].platicos.pp );
				}
			}
		}
	}
	return retorno;
}
/**
 * \brief Imprime cantidad de pedidos Pendientes para una localidad.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param arrayCli Array de Publicacion a recorrer
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirPedidosPorLocalidad(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed)
{
	int retorno = -1;
	char arrayLocalidad[CLI_LEN][LOCALIDAD_LEN];
	int idAux;
	int auxIndice;
	int cantPedidosPendientes = 0;
	if(arrayCli != NULL && limiteCli > 0 && arrayPed != NULL && limitePed > 0)
	{
		if(!crearListaLocalidades(arrayLocalidad, CLI_LEN,arrayCli,limiteCli))
		{
			if(!utn_getNumero(&idAux,"\nIngrese el id de la localidad: ","\nERROR - id invalido\n",NUM_MIN,CLI_LEN,REINTENTO))
			{
				auxIndice = idAux - 1;
				for(int i=0;i<limiteCli; i++)
				{
					for(int j=0; j<limitePed; j++)
					{

						if(strncmp(arrayCli[i].localidad,arrayLocalidad[auxIndice],sizeof(arrayCli[i].localidad))==0 &&
								arrayCli[i].isEmpty == CARGADO && arrayPed[j].isEmpty == CARGADO &&
								arrayCli[i].id == arrayPed[j].idCliente && arrayPed[j].estado == PENDIENTE)
						{
							cantPedidosPendientes++;
						}
					}
				}
				printf("\nCantidad de Pedidos Pendientes: %d", cantPedidosPendientes);
				retorno = 0;
			}
		}
	}
	return retorno;
}

/**
 * \brief Crea lista de localidades.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int crearListaLocalidades(char arrayLocalidad[][100],int len, Cliente* arrayPed, int limitePed)
{
	int retorno = -1;
	if(arrayLocalidad!= NULL && len > 0 && arrayPed != NULL && limitePed > 0)
	{
		for(int j=0; j<len; j++) //INICIALIZO ARRAY
		{
			strncpy(arrayLocalidad[j],"1",len);

		}
		for(int i=0; i<limitePed;i++) //CARGO ARRAY LOCALIDADES
		{
			if(arrayPed[i].isEmpty == CARGADO){
				for(int j=0; j<len; j++)
				{
					if(strncmp(arrayPed[i].localidad, arrayLocalidad[j],sizeof(arrayPed[i].localidad)) != 0 && strncmp(arrayLocalidad[j], "1",LOCALIDAD_LEN)==0)
					{
						strncpy(arrayLocalidad[j],arrayPed[i].localidad,LOCALIDAD_LEN);
						retorno = 0;
						break;
					}else if(strncmp(arrayPed[i].localidad, arrayLocalidad[j],sizeof(arrayPed[i].localidad)) == 0 && strncmp(arrayLocalidad[j], "1",LOCALIDAD_LEN)!=0)
					{
						break;
					}
				}
			}

		}
		printf("\nID LOCALIDAD"
			   "\n-------------");
		for(int j=0; j<CLI_LEN; j++) //MUESTRO LA LISTA
		{
			if(strncmp(arrayLocalidad[j], "1",len)!=0)
			{
				printf("\n%-4d %-13s", j+1, arrayLocalidad[j]);
			}

		}
	}
	return retorno;
}

/**
 * \brief Crea lista de id con polipropileno.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int crearListaId(int arrayId[],int len, Pedido* arrayPed, int limitePed)
{
	int retorno = -1;
	if(arrayId!= NULL && len > 0 && arrayPed != NULL && limitePed > 0)
	{
		for(int j=0; j<len; j++) //INICIALIZO ARRAY
		{
			arrayId[j]=-1;
		}
		for(int i=0; i<limitePed;i++) //CARGO ARRAY LOCALIDADES
		{
			if(arrayPed[i].isEmpty == CARGADO)
			{
				for(int j=0; j<len; j++)
				{
					if(arrayPed[i].idCliente != arrayId[j] && arrayId[j] ==  -1
							&& arrayPed[i].platicos.pp > 0)
					{
						arrayId[j] = arrayPed[i].idCliente;
						retorno = 0;
						break;
					}else if(arrayPed[i].idCliente == arrayId[j] && arrayId[j] != -1
							&& arrayPed[i].platicos.pp > 0)
					{
						break;
					}
				}
			}

		}
		/*printf("\nID"
			   "\n-------------");
		for(int j=0; j<CLI_LEN; j++) //MUESTRO LA LISTA
		{
			if(arrayId[j] != -1)
			{
				printf("\n%-4d", arrayId[j]);
			}

		}*/
	}
	return retorno;
}
/**
 * \brief Imprime cantidad de pedidos Pendientes para una localidad.
 * \param arrayCli Array de Cliente a recorrer
 * \param limiteCli Limite del array de Cliente
 * \param arrayCli Array de Publicacion a recorrer
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int info_imprimirCantidadPolipropilenoPromedioPorCliente(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed)
{
	int retorno = -1;
	int cantClientePolipropileno = 0;
	float totalPolipropileno = 0;
	int listaId[CLI_LEN];

	if(arrayCli != NULL && limiteCli > 0 && arrayPed != NULL && limitePed > 0)
	{
		if(!crearListaId(listaId,CLI_LEN, arrayPed,limitePed))
		{
			for(int i=0;i<limiteCli; i++)
			{
				for(int j=0; j<limitePed; j++)
				{
					if(arrayPed[j].platicos.pp > 0 && arrayPed[j].isEmpty==CARGADO)
					{
						totalPolipropileno += arrayPed[j].platicos.pp;
						if(listaId[i] != -1 && arrayPed[j].idCliente == listaId[i] && arrayPed[j].estado ==COMPLETADO)
						{
							cantClientePolipropileno++;
						}
					}
				}
				if(listaId[i]!=-1)
				printf("\nID:%d    Promedio: %.2f",listaId[i], totalPolipropileno/cantClientePolipropileno);
				cantClientePolipropileno = 0;
				totalPolipropileno = 0;
			}
		}


	}
	return retorno;
}


