#include "main.h"
#include "gestionReservas.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/****************************************************************************/
/*Subprograma:              Menú de las reservas                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Presenta por pantalla el menú del subprograma   */
/*                          con todas las opciones disponibles              */
/****************************************************************************/
void menu_reservas(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    int opc;
    do{
        printf("------------------------------------------------------\n");
        printf("\n\t\tGESTIÓN DE RESERVAS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Realizar Reserva\n");
        printf("\n\t2.- Cancelar Reserva\n");
        printf("\n\t3.- Consultar Reservas de un Cliente\n");
        printf("\n\t4.- Listado General de Reservas\n");
        printf("\n\t0.- Volver al menú principal\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                realizarReserva(clientes, *cont_clientes, habitaciones, *cont_hab, cont_reservas, reservas);
                system("pause");
                system("cls");
                break;
            case 2:
                cancelarReservas(clientes, *cont_clientes, cont_reservas, reservas);
                system("pause");
                system("cls");
                break;
            case 3:
                consultarReservasCliente(clientes, *cont_clientes, habitaciones, *cont_hab, *cont_reservas, reservas);
                system("pause");
                system("cls");
                break;
            case 4:
                listadoGrlReservas(clientes, *cont_clientes, habitaciones, *cont_hab, *cont_reservas, reservas);
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/************************************************************************************************/
/*Subprograma:              Gestión realizar reservas                                           */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Arrays clientes, habitaciones y reservas, y contadores de clientes, */
/*                          habitaciones y reservas                                             */
/*Parámetros de salida:     Arrays clientes y reservas, y contador reservas                     */
/*Prerrequisitos:           Es necesario que haya espacio para nuevos clientes y que el DNI     */
/*                          introducido no exista en el array                                   */
/*Objetivo:                 Se encarga de añadir nuevas reservas al array de reservas. También  */
/*                          las carga en los clientes y actualiza el contador de reservas       */
/************************************************************************************************/
void realizarReserva(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    printf("\n\n\t\tREALIZAR RESERVAS\n");
    printf("\n--------------------------------------------------------------------\n");

    fflush(stdin);
    char select[10], cod[8];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con algún cliente del fichero
    int encontrado = -1, existe = -1, fecha;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        if(clientes[encontrado].cantReservas >= 5){
            printf("\n\tEste cliente ha alcanzado el máximo de reservas permitidas.\n");
            return;
        }
        printf("\n\tIntroduce el código de la habitación: ");
        fgets(cod, sizeof(cod), stdin);
        cod[strcspn(cod, "\n")] = '\0';
        fflush(stdin);

        //Comprobamos que el código se corresponde con alguna habitación del array
        for(int i=0; i < cont_hab; i++){
            if(strcmp(cod, habitaciones[i].codigo) == 0){
                    existe = i;
                    break;
            }
        }
        if(existe != -1){
            //Comprobamos que no está ocupada por ningún cliente
            for (int i = 0; i < cont_clientes;  i++){
                if(clientes[i].cantReservas != 0){
                    for (int j = 0; j < MAX_RESERVAS; j++){
                        if(strcmp(habitaciones[existe].codigo, clientes[i].reservas[j]) == 0){
                            printf("\n\tERROR: No se puede dar reservar la habitación %s ya que está ocupada.\n", habitaciones[existe].codigo);
                            return;
                        }
                    }
                }
            }
        } else{
            printf("\n\tERROR: Esta habitación no figura en nuestro registro de datos.\n\n");
            return;
        }
    }else{
        printf("\n\tEl cliente %s no se encuentra en nuestro sistema.\n\n", select);
        return;
    }

    //Guardamos la reserva en el array de reservas, y los cambios correspondientes en el cliente y los contadores
    //Solicitamos el día
    printf("\n\tIntroduzca el día en que se reserva la habitación: ");
    scanf("%d", &fecha);
    fflush(stdin);

    //Cambios en las reservas
    for (int i = 0; i < DIAS_MES; i++){
        if ( (fecha -1) == i){
            for (int j = 0; j < MAX_HABITACIONES; j++){
                if(strcmp (reservas[i][j], "0") != 0){
                    strcpy(reservas[i][j], cod);
                    break; //Solo la añade una vez
                }
            }
        }
    }

    //Cambios en el cliente
    (clientes[encontrado].cantReservas)++;
    for (int i = 0; i < MAX_RESERVAS; i++){
        if(strcmp (clientes[encontrado].reservas[i], "0") == 0){
            strcpy(clientes[encontrado].reservas[i], cod);
            break; //Solo la añade una vez
        }
    }

    //Cambios en el contador de reservas
    (*cont_reservas)++;
}

/************************************************************************************************/
/*Subprograma:              Gestión cancelar reservas                                           */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Arrays clientes, habitaciones y reservas, y contadores clientes,    */
/*                          habitaciones y reservas.                                            */
/*Parámetros de salida:     Arrays clientes y reservas y contador reservas.                     */
/*Prerrequisitos:           Es necesario que el DNI esté agregado en el listado                 */
/*Objetivo:                 Se encarga de eleminar reservas del array de clientes y de reservas */
/*                          y guardar los en el fichero de texto.                               */
/************************************************************************************************/
void cancelarReservas(tRegCliente clientes[], int cont_clientes, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    printf("\n\n\t\tCANCELAR RESERVAS\n");
    printf("\n------------------------------------------------------\n");

    fflush(stdin);
    char select[10];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con algún cliente del fichero
    int encontrado = -1;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    //Guardamos las reservas eliminadas en el fichero de cancelación y realizamos los cambios en el array reservas
    //Solicitamos fecha
    char fecha[11];
    printf("\n\tIntroduzca la fecha (DD/MM/AAAA): ");
    fgets(fecha, sizeof(fecha), stdin);
    fecha[strcspn(fecha, "\n")] = '\0';
    fflush(stdin);

    FILE *fichCanc= fopen("cancelacionHcoReservas.txt", "a");
    if(fichCanc == NULL){
        printf("\n\tERROR: No se pudo abrir el registro de cancelación.\n\n");
        return;
    }

    for (int i = 0; i < MAX_RESERVAS; i++){
        if(strcmp(clientes[encontrado].reservas[i], "0") != 0){
            fprintf(fichCanc, "%s - %s - %s\n", clientes[encontrado].dni, clientes[encontrado].reservas[i], fecha);
            for (int j = 0; j < DIAS_MES; j++){
                for (int k = 0; k < MAX_HABITACIONES; k++){
                    if(strcmp(reservas[j][k], clientes[encontrado].reservas[i]) == 0){
                        strcpy(reservas[j][k], "0");
                        (*cont_reservas)--;
                    }
                }
            }
        }
    }

    fclose(fichCanc);

    //Eliminamos las habitaciones del array del cliente y cambiamos la cantidad de reservas por 0
    for (int i = 0; i < MAX_RESERVAS; i++){
        if(strcmp(clientes[encontrado].reservas[i], "0") != 0){
            strcpy(clientes[encontrado].reservas[i], "0");
        }
    }
    clientes[encontrado].cantReservas = 0;

    printf("\n\tReservas eliminadas correctamente.\n\n");
}

/************************************************************************************************/
/*Subprograma:              Consulta de reservas de un cliente                                  */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Arrays clientes, habitaciones y reservas, y contadores clientes,    */
/*                          habitaciones y reservas                                             */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           Es necesario que el cliente esté agregado en el listado             */
/*Objetivo:                 Se encarga de mostrar los datos de las resersvas del cliente        */
/*                          seleccionado, junto con el importe total de la reserva              */
/************************************************************************************************/
void consultarReservasCliente(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    printf("\n\n\t\tCONSULTAR RESERVAS DE UN CLIENTE\n");
    printf("\n--------------------------------------------------------------------\n");

    fflush(stdin);
    char select[10];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con algún cliente del fichero
    int encontrado = -1;
    float coste = 0;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    if(clientes[encontrado].cantReservas != 0){
        //Mostramos los datos del cliente seleccionado y buscamos la habitacion en el array de habitaciones para el importe total de las reservas del cliente
        char hab[8];
        printf("\n\tHabitaciones reservadas por el cliente %s:\n", clientes[encontrado].dni);
        for (int i = 0; i < MAX_RESERVAS; i++){
            if(strcmp(clientes[encontrado].reservas[i], "0") != 0){
                printf("\n\t%s\n", clientes[encontrado].reservas[i]);
                strcpy(hab, clientes[encontrado].reservas[i]);

                for(int j = 0; j < cont_hab; j++){
                    if(strcmp(habitaciones[j].codigo, hab) == 0){
                        coste = coste + habitaciones[j].precio;
                    }
                }
            }
        }
        printf("\n\n\tImporte total de las reservas: %.2f\n\n", coste);
    } else {
        printf("\n\tEl cliente %s no posee reservas.\n\n", clientes[encontrado].dni);
    }
}

/************************************************************************************************/
/*Subprograma:              Mostrar listado de reservas                                         */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Arrays clientes, habitaciones y reservas, y contadores clientes,    */
/*                          habitaciones y reservas                                             */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           Que existan reservas                                                */
/*Objetivo:                 Se encarga de mostrar los datos de las reservas activas             */
/************************************************************************************************/
void listadoGrlReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    printf("\n\n\t\tLISTADO GENERAL DE RESERVAS\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tNombre Cliente\t\tCódigo Habitación\tTipo Habitación\n");
    for (int i = 0; i < cont_clientes; i++){
        if(clientes[i].cantReservas != 0){
            printf("\n\t%-20s\t", clientes[i].nombre);
            for (int j = 0; j < MAX_RESERVAS; j++){
                for(int k = 0; k < cont_hab; k++){
                    if(strcmp(clientes[i].reservas[j], habitaciones[k].codigo) == 0 && clientes[i].cantReservas == 1){
                        printf("%-10s\t\t", habitaciones[k].codigo);
                        if(habitaciones[k].tipo == 1){
                            printf("Individual\n");
                        } else if (habitaciones[k].tipo == 2){
                            printf("Doble\n");
                        } else{
                            printf("Suite\n");
                        }
                    } else if(strcmp(clientes[i].reservas[j], habitaciones[k].codigo) == 0 && clientes[i].cantReservas > 1){
                        printf("%-10s\t\t", habitaciones[k].codigo);
                        if(habitaciones[k].tipo == 1){
                            printf("Individual\n\t\t\t\t");
                        } else if (habitaciones[k].tipo == 2){
                            printf("Doble\n\t\t\t\t");
                        } else{
                            printf("Suite\n\t\t\t\t");
                        }
                    }
                }
            }
        }
    }
    printf("\n");
}
