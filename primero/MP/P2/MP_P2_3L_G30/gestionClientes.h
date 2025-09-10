#ifndef GESTIONCLIENTES
#define GESTIONCLIENTES

#include "main.h"


//Subprogramas opción Clientes
void menu_cliente(tRegCliente clientes[], int *cont_clientes);
void altaClientes(tRegCliente clientes[], int *cont_clientes);
void bajaClientes(tRegCliente clientes[], int *cont_clientes);
void modClientes(tRegCliente clientes[], int cont_clientes);
void consultaDatosClientes(tRegCliente clientes[], int cont_clientes);
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes);
void listadoClientesCat(tRegCliente clientes[], int cont_clientes);
void buscarCliente(tRegCliente clientes[], int cont_clientes);
void mostrarClientes(tRegCliente clientes[], int cont_clientes);

#endif
