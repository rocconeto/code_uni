/*  Asigantura: Metodología de la programación Curso: 1
    Tarea que realiza el programa: Gestión de clientes, habitaciones y reservas de un hotel
    Alumno 1: Atanasov Angelov, Daniel
    Alumno 2: Sanz Tomé, Raúl
    Grupo de laboratorio: 30
    Fecha: 24/02/2025 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_HABITACIONES 50
#define DIAS_MES 31
#define MAX_RESERVAS 5

typedef struct{
    char dni[10];
    char nombre[50];
    int tipo;
    int cantReservas; //Para saber cuántas reservas tiene
    char reservas[MAX_RESERVAS][8];
}tRegCliente;

typedef struct{
    char codigo[8];
    int tipo;
    float precio;
}tRegHabitacion;

void menu_princ(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);

//Subprogramas opción Clientes
void menu_cliente(tRegCliente clientes[], int *cont_clientes);
void altaClientes(tRegCliente clientes[], int *cont_clientes);
void bajaClientes(tRegCliente clientes[], int *cont_clientes);
void modClientes(tRegCliente clientes[], int cont_clientes);
void consultaDatosClientes(tRegCliente clientes[], int cont_clientes);
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes);
void listadoClientesCat(tRegCliente clientes[], int cont_clientes);

//Subprogramas opción habitaciones
void menu_hab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int *cont_clientes);
void altaHab(tRegHabitacion habitaciones[], int *cont_hab);
void bajaHab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int cont_clientes);
void modHabitaciones(tRegHabitacion habitaciones[], int cont_hab);
void consultaDatosHab(tRegHabitacion habitaciones [], int cont_hab);
void listadoHab(tRegHabitacion habitaciones[], int cont_hab);

//Subprogramas opción reservas
void menu_reservas(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void realizarReserva(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void cancelarReservas(tRegCliente clientes[], int cont_clientes, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void consultarReservasCliente(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void listadoGrlReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);

//Subprograma guardar datos
void guardar_clientes(tRegCliente clientes[], int *cont_clientes);
void guardar_hab(tRegHabitacion habitaciones[], int *cont_hab);
void guardar_reservas(char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void guardar_contadores(int *cont_clientes, int *cont_hab, int *cont_reservas);

int main(){
    setlocale(LC_ALL, "spanish");

    tRegCliente clientes[MAX_CLIENTES];
    tRegHabitacion habitaciones[MAX_HABITACIONES];
    char reservas[DIAS_MES][MAX_HABITACIONES][8];
    int cont_clientes = 0, cont_hab = 0, cont_reservas = 0;

    //Inicializamos

    printf("\n\t¡Bienvenido a la aplicación GEST_HOTEL!\n");
    printf("\n--------------------------------------------------------\n");
    printf("\n\tCargando datos...\n\n");

    //Cargamos los datos de los ficheros
    FILE *contadores = fopen("totalGlobalHotel.dat", "r");
    if(contadores == NULL) {
        printf("\n\tError al abrir el fichero totalGlobalHotel.dat\n\n");
        exit(1);
    }
    if(fscanf(contadores, "%d %d %d", &cont_clientes, &cont_hab, &cont_reservas) != 3){
        printf("\n\tERROR al leer los contadores.\n");
    }
    if(cont_clientes >= MAX_CLIENTES){
        printf("\n\tError cantidad de clientes superior a la permitida");
    }
    if(cont_hab >= MAX_HABITACIONES){
        printf("\n\tError cantidad de habitaciones superior a la permitida");
    }

    fclose(contadores);

    FILE *cl = fopen("clientes.dat", "r");
    if (cl == NULL) {
        printf("\n\tError al abrir el fichero clientes.dat\n\n");
        exit(1);
    }

    for (int i = 0; i <= cont_clientes; i++){
        fscanf(cl, "%s", clientes[i].dni);
        fgetc(cl); // Consumir salto de línea
        fgets(clientes[i].nombre, sizeof(clientes[i].nombre), cl);
        clientes[i].nombre[strcspn(clientes[i].nombre, "\n")] = '\0'; // Eliminar salto de línea
        fscanf(cl, "%d %d", &clientes[i].tipo, &clientes[i].cantReservas);
        if(clientes[i].cantReservas > MAX_RESERVAS){
            printf("\n\tERROR: El cliente posee más reservas de las permitidas.");
            exit(1);
        }
        for (int j = 0; j < MAX_RESERVAS; j++) {
            fscanf(cl, "%s", clientes[i].reservas[j]);
        }
    }
    fclose(cl);

    FILE *hab = fopen("habitaciones.dat", "r");
    if (hab == NULL){
        printf("\n\tError al abrir el fichero habitaciones.dat");
        exit(1);
    }
    for(int i = 0; i < cont_hab; i++){
        fscanf(hab, "%s", habitaciones[i].codigo);
        fgetc(hab);
        fscanf(hab, "%d %f", &habitaciones[i].tipo, &habitaciones[i].precio);
    }

    FILE *reserv = fopen("reservas.dat", "r");
    if (reserv == NULL) {
        printf("\n\tError al abrir el fichero reservas.dat\n\n");
        exit(1);
    }

    int dia;
    char linea[100];
    for(int i = 0; i<cont_reservas; i++){
        fscanf(reserv, "%d", &dia);
        fgetc(reserv);

        //Leer la linea que contiene las habitaciones
        if(fgets(linea, sizeof(linea), reserv) != NULL){
            int i = 0;
            char *token = strtok(linea, " \n");
            while (token != NULL && i < MAX_HABITACIONES) {
                strcpy(reservas[dia - 1][i], token);
                i++;
                token = strtok(NULL, " \n");
            }
        }
    }
    fclose(reserv);

    system("pause");
    system("cls");

     menu_princ(clientes, &cont_clientes, habitaciones, &cont_hab, &cont_reservas, reservas);
    return 0;
}

/********************************************************************************/
/*Subprograma:              Menú principal                                      */
/*Tipo:                     Procedimiento (función tipo void)                   */
/*Parámetros de entrada:    Arrays de clientes, habitaciones y reservas, junto  */
/*                          con los contadores correspondientes a cada uno      */
/*Parámetros de salida:     ---                                                 */
/*Prerrequisitos:           ---                                                 */
/*Objetivo:                 Muestra por pantalla el menú principal del programa */
/********************************************************************************/
void menu_princ(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[] ,int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    int opc;

    do {
        printf("--------------------------------------------------------\n");
        printf("\n\t\tMENÚ PRINCIPAL\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Gestión de Clientes\n");
        printf("\n\t2.- Gestión de Habitaciones\n");
        printf("\n\t3.- Gestión de Reservas\n");
        printf("\n\t4.- Informes Económicos\n");
        printf("\n\t5.- Importar Habitaciones desde Fichero\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);
        getchar();

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                //menu_cliente(clientes, cont_clientes);
                break;
            case 2:
                //menu_hab(habitaciones, cont_hab, clientes, cont_clientes);
                break;
            case 3:
                menu_reservas(clientes, cont_clientes, habitaciones, cont_hab, cont_reservas, reservas);
                break;
            case 4:
                printf("\n\tInformes\n\n");
                system("pause");
                system("cls");
                break;
            case 5:
                printf("\n\tImportar\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                printf("\n\tGuardando los datos...\n");
                printf("\n--------------------------------------------------------\n\n");
                guardar_clientes(clientes, cont_clientes);
                guardar_hab(habitaciones, cont_hab);
                guardar_reservas(reservas);
                guardar_contadores(cont_clientes, cont_hab, cont_reservas);
                printf("\n\t¡Gracias por usar nuestro programa!\n\n");

                break;
        }
    }while(opc != 0);
}
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
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTIÓN DE RESERVAS\n");
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
    printf("\n--------------------------------------------------------------------\n");
    printf("\n\tREALIZAR RESERVAS\n");
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
    printf("\n------------------------------------------------------\n");
    printf("\n\tCANCELAR RESERVAS\n");
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
    printf("\n--------------------------------------------------------------------\n");
    printf("\n\tCONSULTAR RESERVAS DE UN CLIENTE\n");
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
    printf("\n--------------------------------------------------------------------\n");
    printf("\n\tLISTADO GENERAL DE RESERVAS\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tNombre Cliente\t\tCódigo Habitación\tTipo Habitación\n");
    for (int i = 0; i < cont_clientes; i++){
        if(clientes[i].cantReservas != 0){
            printf("\n\t%-20s\t", clientes[i].nombre);
            for (int j = 0; j < MAX_RESERVAS; j++){
                for(int k = 0; k < cont_hab; k++){
                    if(strcmp(clientes[i].reservas[j], habitaciones[k].codigo) == 0 && clientes[i].cantReservas == 1){
                        printf("%-10s\t", habitaciones[k].codigo);
                        if(habitaciones[k].tipo == 1){
                            printf("Individual\n");
                        } else if (habitaciones[k].tipo == 2){
                            printf("Doble\n");
                        } else{
                            printf("Suite\n");
                        }
                    } else if(strcmp(clientes[i].reservas[j], habitaciones[k].codigo) == 0 && clientes[i].cantReservas > 1){
                        printf("%-10s\t", habitaciones[k].codigo);
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

/*************************************************************************************************/
/*Subprograma:              Guardar datos clientes                                               */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Array clientes y contador de clientes                                */
/*Parámetros de salida:     ---                                                                  */
/*Prerrequisitos:           Llamada al fichero creada correctamente                              */
/*Objetivo:                 Guardar en el fichero los cambios realizados en el array de clientes */
/*************************************************************************************************/
void guardar_clientes(tRegCliente clientes[], int *cont_clientes) {
    FILE *cl = fopen("clientes.dat", "w");

    if (cl == NULL) {
        printf("\n\tError al guardar los clientes.\n");
        return;
    }

    for (int i = 0; i < *cont_clientes; i++) {
        fprintf(cl, "%s\n%s\n%d\n%d", clientes[i].dni, clientes[i].nombre, clientes[i].tipo, clientes[i].cantReservas);
        for (int j = 0; j < MAX_RESERVAS; j++) {
            fprintf(cl, " %s", clientes[i].reservas[j]);
        }
        fprintf(cl, "\n");
    }

    fclose(cl);
}

/*****************************************************************************************************/
/*Subprograma:              Guardar datos habitaciones                                               */
/*Tipo:                     Procedimiento (función tipo void)                                        */
/*Parámetros de entrada:    Array habitaciones y contador de habitaciones                            */
/*Parámetros de salida:     ---                                                                      */
/*Prerrequisitos:           Llamada al fichero creada correctamente                                  */
/*Objetivo:                 Guardar en el fichero los cambios realizados en el array de habitaciones */
/*****************************************************************************************************/
void guardar_hab(tRegHabitacion habitaciones[], int *cont_hab){
    FILE *hab = fopen("habitaciones.dat", "w");

    if (hab == NULL) {
        printf("\n\tError al guardar las habitaciones.\n");
        return;
    }

    for (int i = 0; i < *cont_hab; i++) {
        fprintf(hab, "%s\n%d %.2f\n", habitaciones[i].codigo, habitaciones[i].tipo, habitaciones[i].precio);
    }

    fclose(hab);
}

/*************************************************************************************************/
/*Subprograma:              Guardar datos reservas                                               */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Array reservas                                                       */
/*Parámetros de salida:     ---                                                                  */
/*Prerrequisitos:           Llamada al fichero creada correctamente                              */
/*Objetivo:                 Guardar en el fichero los cambios realizados en el array de reservas */
/*************************************************************************************************/
void guardar_reservas(char reservas[DIAS_MES][MAX_HABITACIONES][8]) {
    FILE *reserv = fopen("reservas.dat", "w");
    if (reserv == NULL) {
        printf("\n\tERROR: No se pudo abrir el archivo de reservas para guardar los datos.\n\n");
        return;
    }

    for (int dia = 0; dia < DIAS_MES; dia++) {
        int hayReservas = 0;

        // Comprobamos si hay al menos una reserva en este día
        for (int i = 0; i < MAX_HABITACIONES; i++) {
            //Comprueba que la cadena na vale 0 y que no está vacía para evitar que muestre todos los días en el fichero aunque estos no tengan reservas
            if (strcmp(reservas[dia][i], "0") != 0 && reservas[dia][i][0] != '\0') {
                hayReservas = 1;
                break;
            }
        }

        if (hayReservas) {
            fprintf(reserv, "%d\n", dia + 1);  // Guardamos el día (1-indexado)

            // Guardamos las habitaciones reservadas ese día
            for (int i = 0; i < MAX_HABITACIONES; i++) {
                if (strcmp(reservas[dia][i], "0") != 0 && reservas[dia][i][0] != '\0') {
                    fprintf(reserv, "%s ", reservas[dia][i]);
                }
            }
            fprintf(reserv, "\n");  // Fin de la línea de ese día
        }
    }

    fclose(reserv);
    printf("\n\tReservas guardadas correctamente.\n\n");
}

/*************************************************************************************************/
/*Subprograma:              Guardar contadores                                                   */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Contadores de clientes, habitaciones y reservas                      */
/*Parámetros de salida:     ---                                                                  */
/*Prerrequisitos:           Llamada al fichero creada correctamente                              */
/*Objetivo:                 Guardar en el fichero los cambios realizados en los contadores       */
/*************************************************************************************************/
void guardar_contadores(int *cont_clientes, int *cont_hab, int *cont_reservas){
    FILE *contadores = fopen("totalGlobalHotel.dat", "w");
    if (contadores == NULL) {
        printf("\n\tError al abrir el fichero totalGlobalHotel.dat\n\n");
        return;
    }
    fprintf(contadores, "%d %d %d", *cont_clientes, *cont_hab, *cont_reservas);
    fclose(contadores);
}
