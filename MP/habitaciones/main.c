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
    int cantReservas; //Para saber cu�ntas reservas tiene
    char reservas[MAX_RESERVAS][8];
}tRegCliente;

typedef struct{
    char codigo[8];
    int tipo;
    float precio;
}tRegHabitacion;

void menu_princ(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);

//Subprogramas opci�n Clientes
void menu_cliente(tRegCliente clientes[], int *cont_clientes);
void altaClientes(tRegCliente clientes[], int *cont_clientes);
void bajaClientes(tRegCliente clientes[], int *cont_clientes);
void modClientes(tRegCliente clientes[], int cont_clientes);
void consultaDatosClientes(tRegCliente clientes[], int cont_clientes);
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes);
void listadoClientesCat(tRegCliente clientes[], int cont_clientes);

//Subprogramas opci�n habitaciones
void menu_hab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int *cont_clientes);
void altaHab(tRegHabitacion habitaciones[], int *cont_hab);
void bajaHab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int cont_clientes);
void modHabitaciones(tRegHabitacion habitaciones[], int cont_hab);
void consultaDatosHab(tRegHabitacion habitaciones [], int cont_hab);
void listadoHab(tRegHabitacion habitaciones[], int cont_hab);

//Subprogramas opci�n reservas
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

    printf("\n\t�Bienvenido a la aplicaci�n GEST_HOTEL!\n");
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
        fgetc(cl); // Consumir salto de l�nea
        fgets(clientes[i].nombre, sizeof(clientes[i].nombre), cl);
        clientes[i].nombre[strcspn(clientes[i].nombre, "\n")] = '\0'; // Eliminar salto de l�nea
        fscanf(cl, "%d %d", &clientes[i].tipo, &clientes[i].cantReservas);
        if(clientes[i].cantReservas > MAX_RESERVAS){
            printf("\n\tERROR: El cliente posee m�s reservas de las permitidas.");
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
/*Subprograma:              Men� principal                                      */
/*Tipo:                     Procedimiento (funci�n tipo void)                   */
/*Par�metros de entrada:    Arrays de clientes, habitaciones y reservas, junto  */
/*                          con los contadores correspondientes a cada uno      */
/*Par�metros de salida:     ---                                                 */
/*Prerrequisitos:           ---                                                 */
/*Objetivo:                 Muestra por pantalla el men� principal del programa */
/********************************************************************************/
void menu_princ(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[] ,int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    int opc;

    do {
        printf("--------------------------------------------------------\n");
        printf("\n\t\tMEN� PRINCIPAL\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Gesti�n de Clientes\n");
        printf("\n\t2.- Gesti�n de Habitaciones\n");
        printf("\n\t3.- Gesti�n de Reservas\n");
        printf("\n\t4.- Informes Econ�micos\n");
        printf("\n\t5.- Importar Habitaciones desde Fichero\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);
        getchar();

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                //menu_cliente(clientes, cont_clientes);
                break;
            case 2:
                menu_hab(habitaciones, cont_hab, clientes, cont_clientes);
                break;
            case 3:
                //menu_reservas(clientes, cont_clientes, habitaciones, cont_hab, cont_reservas, reservas);
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
                printf("\n\t�Gracias por usar nuestro programa!\n\n");

                break;
        }
    }while(opc != 0);
}

/**************************************************************************************/
/*Subprograma:              Men� de las habitaciones                                  */
/*Tipo:                     Procedimiento (funci�n tipo void)                         */
/*Par�metros de entrada:    Array de las habitaciones y contador de las habitaciones  */
/*Par�metros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Muestra por pantalla el men� del subprograma con          */
/*                          todas sus opciones de las habitaciones                    */
/**************************************************************************************/
void menu_hab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int *cont_clientes){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTI�N DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificaci�n\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t0.- Volver al men� principal\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);
        fflush(stdin);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                altaHab(habitaciones, cont_hab);
                system("pause");
                system("cls");
                break;
            case 2:
                bajaHab(habitaciones, cont_hab, clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 3:
                modHabitaciones(habitaciones, *cont_hab);
                system("pause");
                system("cls");
                break;
            case 4:
                consultaDatosHab(habitaciones, *cont_hab);
                system("pause");
                system("cls");
                break;
            case 5:
                listadoHab(habitaciones, *cont_hab);
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/************************************************************************************************/
/*Subprograma:              Gesti�n alta habitaciones                                           */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array habitaciones y contadores de habitaciones                     */
/*Par�metros de salida:     Array habitaciones y contador de habitaciones                       */
/*Prerrequisitos:           Es necesario que haya espacio para nuevas habitaciones              */
/*Objetivo:                 Se encarga de a�adir nuevas reservas al array de reservas           */
/************************************************************************************************/
void altaHab(tRegHabitacion habitaciones[], int *cont_hab){
    printf("\n------------------------------------------------------\n");
    printf("\n\tALTA DE HABITACIONES\n");
    printf("\n------------------------------------------------------\n");

    if (*cont_hab >= MAX_HABITACIONES){
        printf("\n\tNo es posible a�adir nuevas habitaciones.\n");
        return;
    }

    tRegHabitacion nueva;

    //Genera el c�digo de la habitaci�n
    char cod[8];
    int encontrado = 0;

    //Los primeros caracteres del c�digo son fijos
    cod[0] = 'H';
    cod[1] = 'A';
    cod[2] = 'B';
    cod[3] = '_';

    for (int k = 0; k < 10 && encontrado == 0; k++){
        for (int j = 0; j < 10 && encontrado == 0; j++){
            for (int i = 1; i < 10 && encontrado == 0; i++){ //Empieza en 1 para que no exista la HAB_000
                cod[4] = k + '0';
                cod[5] = j + '0';
                cod[6] = i + '0';
                cod[7] = '\0'; //Cerramos el char

                //Comprobamos que el c�digo no se encuentra en el array
                int existe = -1;
                for(int e = 0; e < *cont_hab; e++){
                    if(strcmp(cod, habitaciones[e].codigo) == 0){
                        existe = e;
                        break;
                    }
                }

                if(existe == -1){
                    strcpy(nueva.codigo, cod);
                    encontrado = 1; //Para finalizar los bucles
                }
            }
        }
    }

    //Solicita el resto de informaci�n de la habitaci�n
    printf("\n\tTipo de habitaci�n: 1 = Individual, 2 = Doble, 3 = Suite");
    printf("\n\tIntroduzca el tipo de la nueva habitaci�n: ");
    scanf("%d", &nueva.tipo);
    fflush(stdin);

    printf("\n\tIntroduzca el precio de la nueva habitaci�n: ");
    scanf("%f", &nueva.precio);
    fflush(stdin);

    //Agregamos la habitaci�n al array
    habitaciones[*cont_hab] = nueva;
    (*cont_hab)++;
}

/************************************************************************************************/
/*Subprograma:              Gesti�n baja habitacioens                                           */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Arrays habitaciones y clientes y contadores clientes y habitaciones */
/*Par�metros de salida:     Array habitaciones y contador habitaciones                          */
/*Prerrequisitos:           Es necesario que la habitaci�n est� agregada en el listado y que no */
/*                          est� ocupada por ning�n cliente                                     */
/*Objetivo:                 Se encarga de eleminar habitaciones del registro de habitaciones    */
/*                          y guardar los datos de la habitaci�n borrada en un fichero de texto */
/************************************************************************************************/
void bajaHab(tRegHabitacion habitaciones[], int *cont_hab , tRegCliente clientes[], int cont_clientes){
    printf("\n------------------------------------------------------\n");
    printf("\n\tBAJA DE HABITACIONES\n");
    printf("\n------------------------------------------------------\n");

    char cod[8];
    printf("\n\tIntroduce el c�digo de la habitaci�n: ");
    fgets(cod, sizeof(cod), stdin);
    cod[strcspn(cod, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el c�digo se corresponde con alguna habitaci�n del array
    int encontrado = -1;
    for(int i=0; i < *cont_hab; i++){
        if(strcmp(cod, habitaciones[i].codigo) == 0){
                encontrado = i;
                break;
        }
    }
    if(encontrado == -1){
        printf("\n\tERROR: Esta habitaci�n no figura en nuestro registro de datos.\n\n");
        return;
    }

    //Comprobamos que no est� ocupada por ning�n cliente
    for (int i = 0; i < cont_clientes;  i++){
        if(clientes[i].cantReservas != 0){
            for (int j = 0; j < MAX_RESERVAS; j++){
                if(strcmp(habitaciones[encontrado].codigo, clientes[i].reservas[j]) == 0){
                    printf("\n\tERROR: No se puede dar de baja a la habitaci�n %s ya que tiene reservas asociadas.\n", habitaciones[encontrado].codigo);
                    return;
                }
            }
        }
    }

    //Guardamos el cliente en el fichero de bajas
    //Solicitamos fecha
    char fecha[11];
    printf("\n\tIntroduzca la fecha (DD/MM/AAAA): ");
    fgets(fecha, sizeof(fecha), stdin);
    fecha[strcspn(fecha, "\n")] = '\0';
    fflush(stdin);

    FILE *fichBajas = fopen("bajaHcoHabitaciones.txt", "a");
    if(fichBajas == NULL){
        printf("\n\tERROR: No se pudo abrir el registro de bajas.\n\n");
        return;
    }
    fprintf(fichBajas, "%s - ", habitaciones[encontrado].codigo);
    if(habitaciones[encontrado].tipo == 1){
        fprintf(fichBajas, "Individual - ");
    }else if(habitaciones[encontrado].tipo == 2){
        fprintf(fichBajas, "Doble - ");
    }else{
        fprintf(fichBajas, "Suite - ");
    }
    fprintf(fichBajas, "%s\n", fecha);
    fclose(fichBajas);

    //Eliminamos a la habitaci�n del fichero de habitaciones - primero del array tRegHabitacion
    for (int j = encontrado; j < (*cont_hab) - 1; j++){
        habitaciones[j] = habitaciones[j+1];
    }
    (*cont_hab)--;

    FILE *hab = fopen("habitaciones.dat", "w");

    if (hab == NULL) {
        printf("\n\tError al guardar las habitaciones.\n");
        return;
    }

    for (int i = 0; i < *cont_hab; i++) {
        fprintf(hab, "%s\n%d %.2f\n", habitaciones[i].codigo, habitaciones[i].tipo, habitaciones[i].precio);
    }

    fclose(hab);

    printf("\n\tHabitaci�n eliminada correctamente.\n\n");
}

/*************************************************************************************************/
/*Subprograma:              Gesti�n modificaci�n de datos de habitaciones                        */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array habitaciones y contador habitaciones                           */
/*Par�metros de salida:     Array habitaciones                                                   */
/*Prerrequisitos:           Es necesario que la habitaci�n est� agregada en el listado           */
/*Objetivo:                 Se encarga de cambiar datos de las habitaciones guardadas y mantener */
/*                          los cambios en el fichero. No permite cambiar el c�digo              */
/*************************************************************************************************/
void modHabitaciones(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n------------------------------------------------------------\n");
    printf("\n\tMODIFICACI�N DATOS DE HABITACIONES\n");
    printf("\n------------------------------------------------------------\n");

    char select[8];
    printf("\n\tIntroduce el c�digo de la habitaci�n: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
    int encontrado = -1;
    for(int i=0; i < cont_hab; i++){
        if(strcmp(select, habitaciones[i].codigo) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        printf("\n\t%s - ", habitaciones[encontrado].codigo);
        if(habitaciones[encontrado].tipo == 1){
            printf("Individual - ");
        }else if(habitaciones[encontrado].tipo == 2){
            printf("Doble - ");
        }else{
            printf("Suite - ");
        }
        printf("%.2f\n", habitaciones[encontrado].precio);

        //Selecci�n de qu� se quiere ejecutar
        int opc;
        do{
            printf("\n\n\tSELECCIONE UNA OPCI�N");
            printf("\n\t1- Cambiar tipo de habitaci�n\n");
            printf("\n\t2- Cambiar precio\n");
            printf("\n\t0- Salir\n");

            printf("\n\tSeleccione una opci�n: ");
            scanf("%d", &opc);
            fflush(stdin);

            switch(opc){
                case 1:
                    do{
                        printf("\n\tTipo de cliente: 1 = Individual, 2 = Doble, 3 = Suite");
                        printf("\n\tIntroduzca el nuevo tipo de habitaci�n: ");
                        scanf("%d", &habitaciones[encontrado].tipo);

                        if(habitaciones[encontrado].tipo < 1 || habitaciones[encontrado].tipo > 3){
                            printf("\n\tERROR: El tipo introducido no es v�lido. Intente de nuevo.\n");
                        }
                    } while(habitaciones[encontrado].tipo < 1 || habitaciones[encontrado].tipo > 3);

                    break;
                case 2:
                    printf("\n\tIntroduzca el nuevo precio de la habitaci�n: ");
                    scanf("%f", &habitaciones[encontrado].precio);
                    break;
                case 0:
                    break;
            }
        }while(opc != 0);
    }else{
        printf("\n\tLa habitaci�n %s no se encuentra en nuestro sistema.\n\n", select);
    }
}

/************************************************************************************************/
/*Subprograma:              Consulta de datos de una habitaci�n                                 */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array habitaciones y contador habitaciones                          */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           Es necesario que la habitaci�n est� agregada en el listado          */
/*Objetivo:                 Se encarga de mostrar los datos de la habitaci�n seleccionada       */
/************************************************************************************************/
void consultaDatosHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n------------------------------------------------------------\n");
    printf("\n\tCONSULTA DE DATOS DE UNA HABITACI�N\n");
    printf("\n------------------------------------------------------------\n");

    char select[8];
    printf("\n\tIntroduce el c�digo de la habitaci�n: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que la habitaci�n se corresponde con alguna del fichero
    int encontrado = -1;
    for(int i=0; i < cont_hab; i++){
        if(strcmp(select, habitaciones[i].codigo) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        printf("\n\tC�digo: %s\n\n\tTipo de habitaci�n: ", habitaciones[encontrado].codigo);
        if(habitaciones[encontrado].tipo == 1){
            printf("Individual");
        }else if(habitaciones[encontrado].tipo == 2){
            printf("Doble");
        }else{
            printf("Suite");
        }
        printf("\n\n\tPrecio: %.2f\n\n", habitaciones[encontrado].precio);
    }else{
        printf("\n\tLa habitaci�n %s no se encuentra en nuestro sistema.\n\n", select);
        system("pause");
        system("cls");
        consultaDatosHab(habitaciones, cont_hab);
    }
}

/************************************************************************************************/
/*Subprograma:              Mostrar listado de habitaciones                                     */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array habitaciones y contador habitaciones                          */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de mostrar los datos de las habitaciones                 */
/************************************************************************************************/
void listadoHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n--------------------------------------------------------------------\n");
    printf("\n\tLISTADO GENERAL DE HABITACIONES\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tC�digo\t\tTipo\t\tPrecio\n");
    printf("      |������������|����������������|��������������|");

    for(int i = 0; i < cont_hab; i++){
        printf("\n\t%-10s\t", habitaciones[i].codigo);

        if(habitaciones[i].tipo == 1){
            printf("Individual\t");
        }else if(habitaciones[i].tipo == 2){
            printf("Doble\t\t");
        }else{
            printf("Suite\t\t");
        }
        printf("%.2f\n", habitaciones[i].precio);
    }
    printf("\n");
}

/*************************************************************************************************/
/*Subprograma:              Guardar datos clientes                                               */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array clientes y contador de clientes                                */
/*Par�metros de salida:     ---                                                                  */
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
/*Tipo:                     Procedimiento (funci�n tipo void)                                        */
/*Par�metros de entrada:    Array habitaciones y contador de habitaciones                            */
/*Par�metros de salida:     ---                                                                      */
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
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array reservas                                                       */
/*Par�metros de salida:     ---                                                                  */
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

        // Comprobamos si hay al menos una reserva en este d�a
        for (int i = 0; i < MAX_HABITACIONES; i++) {
            //Comprueba que la cadena na vale 0 y que no est� vac�a para evitar que muestre todos los d�as en el fichero aunque estos no tengan reservas
            if (strcmp(reservas[dia][i], "0") != 0 && reservas[dia][i][0] != '\0') {
                hayReservas = 1;
                break;
            }
        }

        if (hayReservas) {
            fprintf(reserv, "%d\n", dia + 1);  // Guardamos el d�a (1-indexado)

            // Guardamos las habitaciones reservadas ese d�a
            for (int i = 0; i < MAX_HABITACIONES; i++) {
                if (strcmp(reservas[dia][i], "0") != 0 && reservas[dia][i][0] != '\0') {
                    fprintf(reserv, "%s ", reservas[dia][i]);
                }
            }
            fprintf(reserv, "\n");  // Fin de la l�nea de ese d�a
        }
    }

    fclose(reserv);
    printf("\n\tReservas guardadas correctamente.\n\n");
}

/*************************************************************************************************/
/*Subprograma:              Guardar contadores                                                   */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Contadores de clientes, habitaciones y reservas                      */
/*Par�metros de salida:     ---                                                                  */
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
