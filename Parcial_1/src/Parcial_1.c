/*
 ============================================================================
 Name        : Parcial_1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "utn.h"
#include "Cliente.h"
#include "Pedido.h"
#include "Controller.h"
#include "Informes.h"


int main(void) {
	int opcion;
	int idClienteAutomatico = 1;
	int idPedidoAutomatico = 1;
	int flagArrayCargado;
	int mensaje = 0;
	Cliente listaCliente[CLI_LEN];
	Pedido listaPedido[PED_LEN];

	if(!cli_inicializarArray(listaCliente, CLI_LEN) && !ped_inicializarArray(listaPedido,PED_LEN))
	{
		cli_altaForzadaArray(listaCliente, CLI_LEN,0,&idClienteAutomatico,"EMPA","36901002003","Av.Corrientes 675","CABA");
		cli_altaForzadaArray(listaCliente, CLI_LEN,1,&idClienteAutomatico,"ATLA","36901002003","Av.Corrientes 800","CABA");
		idClienteAutomatico = 100;
		cli_altaForzadaArray(listaCliente, CLI_LEN,3,&idClienteAutomatico,"CERO","33333332003","Av.Puente 800","SAN cristobal");
		pub_altaForzadaArray(listaPedido,PED_LEN,0,&idPedidoAutomatico,7.5,PENDIENTE,1,2.5,2,3);
		idPedidoAutomatico = 20;
		pub_altaForzadaArray(listaPedido,PED_LEN,1,&idPedidoAutomatico,5.5,COMPLETADO,1,2.5,2.5,0.5);
		pub_altaForzadaArray(listaPedido,PED_LEN,2,&idPedidoAutomatico,5.5,COMPLETADO,2,2.5,2.5,0.5);
		pub_altaForzadaArray(listaPedido,PED_LEN,3,&idPedidoAutomatico,7.5,COMPLETADO,1,2.5,2,3);
		do{
			flagArrayCargado = validarArrayCargado(listaCliente, CLI_LEN);
			if(!utn_getNumero(&opcion,"\n\n1.Alta de Cliente"
									  "\n2.Modificar datos de Cliente"
									  "\n3.Baja de Cliente"
									  "\n4.Crear pedido de recoleccion"
									  "\n5.Procesar residuos"
									  "\n6.Imprimir Clientes "
									  "\n7.Imprimir Pedidos Pendientes"
									  "\n8.Imprimir Pedidos Procesados"
									  "\n9.Informar pedidos pendientes por localidad"
									  "\n10.Informar cantidad de polipropileno y promedio por cliente"
									  "\n11.Salir\n\n"
									  "Ingrese la opcion del menu: ",
									  "\nERROR - Menu invalido!\n",
									  NUM_MIN, 11, REINTENTO)){
				switch(opcion){
				case 1:
					controllerAltaCliente(listaCliente, CLI_LEN, &idClienteAutomatico);
					break;
				case 2:
					if(!flagArrayCargado)
						controllerModificarCliente(listaCliente, CLI_LEN);
					else
						mensaje = 1;
					break;
				case 3:
					if(!flagArrayCargado)
						controllerBajaCliente(listaCliente, CLI_LEN);
					else
						mensaje = 1;
					break;
				case 4:
					if(!flagArrayCargado)
					{
						controllerCrearPedido(listaCliente, CLI_LEN, listaPedido, PED_LEN, &idPedidoAutomatico);
					}
					else{
						mensaje = 1;
					}
					break;
				case 5:
					if(!flagArrayCargado)
						controllerProcesarReciduo(listaPedido, PED_LEN);
					else
						mensaje = 1;
					break;
				case 6:
					if(!flagArrayCargado)
						info_imprimirArrayConCantPedidos(listaCliente, CLI_LEN, listaPedido, PED_LEN);
					else
						mensaje = 1;
					break;
				case 7:
					if(!flagArrayCargado)
						info_imprimirPedidosPendientes(listaCliente, CLI_LEN, listaPedido, PED_LEN);
					else
						mensaje = 1;
					break;
				case 8:
					if(!flagArrayCargado)
						info_imprimirPedidosProcesados(listaCliente, CLI_LEN, listaPedido, PED_LEN);
					else
						mensaje = 1;
					break;
				case 9:
					if(!flagArrayCargado)
						info_imprimirPedidosPorLocalidad(listaCliente, CLI_LEN, listaPedido, PED_LEN);
					else
						mensaje = 1;
					break;
				case 10:
					if(!flagArrayCargado)
						info_imprimirCantidadPolipropilenoPromedioPorCliente(listaCliente, CLI_LEN, listaPedido, PED_LEN);
					else
						mensaje = 1;
					break;
				default :
					printf("\nLa opcion no pertence al menu.");
					break;
				}//
			}
			if(mensaje){
				printf("\nERROR - No hay empleados cargados.\n\n");
			}

		}while(opcion != 11);
	}

	return EXIT_SUCCESS;
}
