#ifndef INFORMES_H_
#define INFORMES_H_

int info_imprimirArrayConCantPedidos(Cliente* arrayCli, int limiteCli, Pedido* arrayPub, int limitePub);
int info_imprimirPedidosPendientes(Cliente* arrayCli, int limiteCli, Pedido* arrayPub, int limitePub);
int info_imprimirPedidosProcesados(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed);
int info_imprimirPedidosPorLocalidad(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed);
int info_imprimirCantidadPolipropilenoPromedioPorCliente(Cliente* arrayCli, int limiteCli, Pedido* arrayPed, int limitePed);


#endif /* INFORMES_H_ */
