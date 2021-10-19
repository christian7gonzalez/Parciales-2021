#ifndef PEDIDO_H_
#define PEDIDO_H_

#define PED_LEN 1000

#define PENDIENTE 1
#define COMPLETADO 0

#define CARGADO 0
#define VACIO 1

typedef struct{
	float hdpe;
	float ldpe;
	float pp;
}Platico;

typedef struct
{
	int id;
	float cantidadTotal;
	int estado;
	int idCliente;
	Platico platicos;
	int isEmpty;
}Pedido;

int ped_imprimir(Pedido* auxProducto);
int ped_inicializarArray(Pedido* array,int limite);
int ped_alta(Pedido* array,int limite, int indice, int* id, int idCliente);
int ped_getEmptyIndex(Pedido* array,int limite);
int ped_imprimirArray(Pedido* array,int limite);
int ped_imprimirArrayDeUnCliente(Pedido* array,int limite,int idCliente);
int ped_buscarEmptyVacio(Pedido* array,int limite);
int ped_buscarId(Pedido array[], int limite, int valorBuscado);
int ped_buscarIdCliente(Pedido array[], int limite, int valorBuscado);
int ped_buscarIdClientePos(Pedido array[], int limite, int valorBuscado);
int ped_modificar(Pedido* array,int limite, int indice);
int ped_baja(Pedido* array,int limite, int indice);
int ped_modificarEstadoActivo(Pedido* array,int limite , int idPublicacion);
int ped_modificarEstadoPausado(Pedido* array,int limite , int idPublicacion);
int ped_bajaPublicacionesPorId(Pedido* array,int limite,int indice);
int ped_cargarCantidadPlaticosUnCliete(Pedido* array,int limite , int indice);


int pub_altaForzadaArray(Pedido* array,int limite, int indice, int* id,float cantidadTotal,int estado,int idCliente, float hdpe, float ldpe, float pp);

#endif /* PEDIDO_H_ */
