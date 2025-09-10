#ifndef GESTIONHABITACIONES
#define GESTIONHABITACIONES

#include "main.h"
#include "gestionClientes.h"

void altaHab(tRegHabitacion habitaciones[], int *cont_hab);
void bajaHab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int cont_clientes);
void modHabitaciones(tRegHabitacion habitaciones[], int cont_hab);
void consultaDatosHab(tRegHabitacion habitaciones [], int cont_hab);
void listadoHab(tRegHabitacion habitaciones[], int cont_hab);
void buscarHab(tRegHabitacion habitaciones[], int cont_hab);
void mostrarHab(tRegHabitacion habitaciones[], int cont_hab);

#endif
