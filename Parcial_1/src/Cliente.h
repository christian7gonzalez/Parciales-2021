#ifndef CLIENTE_H_
#define CLIENTE_H_

#define CLI_LEN 100

#define CARGADO 0
#define VACIO 1

#define NOMBRE_LEN 100
#define CUIT_LEN 20
#define DIRE_LEN 100
#define LOCALIDAD_LEN 100



typedef struct
{
	int id;
	char nombreEmpresa[NOMBRE_LEN];
	char cuit[CUIT_LEN];
	char direccion[DIRE_LEN];
	char localidad[LOCALIDAD_LEN];
	int isEmpty;
}Cliente;

int cli_imprimir(Cliente* auxProducto);
int cli_inicializarArray(Cliente* array,int limite);
int cli_alta(Cliente* array,int limite, int indice, int* id);
int cli_buscarEmptyVacio(Cliente* array,int limite);
int cli_imprimirArray(Cliente* array,int limite);
int cli_buscarId(Cliente array[], int limite, int valorBuscado);
int cli_modificar(Cliente* array,int limite, int indice);
int cli_baja(Cliente* array,int limite, int indice);

int cli_altaForzadaArray(Cliente* array,int limite, int indice, int* id,char* nombreEmpresa,char* cuit, char* direccion, char* localidad);
int validarArrayCargado(Cliente* array,int limite);

#endif /* CLIENTE_H_ */
