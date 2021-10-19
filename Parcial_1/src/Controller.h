/*
 * Controller.h
 *
 *  Created on: 13 oct. 2021
 *      Author: chgonzalez
 */

int controllerAltaCliente(Cliente* array, int limite, int* idAutomatico);
int controllerModificarCliente(Cliente* array, int limite);
int controllerBajaCliente(Cliente* array, int limite);
int controllerCrearPedido(Cliente* arrayCliente, int limiteCliente, Pedido* array, int limite, int* idAutomatico);
int controllerProcesarReciduo(Pedido* array, int limite);
