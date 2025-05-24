/*  Asigantura: Metodolog�a de la programaci�n Curso: 1
    Tarea que realiza el programa: Gesti�n de clientes, habitaciones y reservas de un hotel
    Alumno 1: Atanasov Angelov, Daniel
    Alumno 2: Sanz Tom�, Ra�l
    Grupo de laboratorio: 30
    Fecha: 24/02/2025 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

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
void buscarCliente(tRegCliente clientes[], int cont_clientes);
void mostrarClientes(tRegCliente clientes[], int cont_clientes);

//Subprogramas opci�n habitaciones
void menu_hab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int *cont_clientes);
void altaHab(tRegHabitacion habitaciones[], int *cont_hab);
void bajaHab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int cont_clientes);
void modHabitaciones(tRegHabitacion habitaciones[], int cont_hab);
void consultaDatosHab(tRegHabitacion habitaciones [], int cont_hab);
void listadoHab(tRegHabitacion habitaciones[], int cont_hab);
void buscarHab(tRegHabitacion habitaciones[], int cont_hab);
void mostrarHab(tRegHabitacion habitaciones[], int cont_hab);

//Subprogramas opci�n reservas
void menu_reservas(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void realizarReserva(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void cancelarReservas(tRegCliente clientes[], int cont_clientes, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void consultarReservasCliente(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);
void listadoGrlReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]);

//Subprogramas opci�n informes econ�micos
void menu_infEco(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab);
void infCatCliente(tRegCliente clientes[], int cont_clientes);
void infOcupHab(tRegCliente clientes[], int cont_clientes, int cont_hab);
void infIngrReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab);

//Subprograma importar habitaciones desde fichero
void importHab(tRegHabitacion habitaciones[], int *cont_hab);

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
    if(cont_clientes > MAX_CLIENTES){
        printf("\n\tError cantidad de clientes superior a la permitida\n");
        exit(1);
    }
    if(cont_hab > MAX_HABITACIONES){
        printf("\n\tError cantidad de habitaciones superior a la permitida\n");
        exit(1);
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
            printf("\n\tERROR: El cliente %s posee m�s reservas de las permitidas.\n", clientes[i].nombre);
            exit(1);
        }
        for (int j = 0; j < MAX_RESERVAS; j++) {
            fscanf(cl, "%s", clientes[i].reservas[j]);
        }
    }
    fclose(cl);

    FILE *hab = fopen("habitaciones.dat", "r");
    if (hab == NULL){
        printf("\n\tError al abrir el fichero habitaciones.dat\n");
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
        printf("-----------------------------------------------------------\n");
        printf("\n\t\tMEN� PRINCIPAL\n");
        printf("\n-----------------------------------------------------------\n");
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
                menu_cliente(clientes, cont_clientes);
                break;
            case 2:
                menu_hab(habitaciones, cont_hab, clientes, cont_clientes);
                break;
            case 3:
                menu_reservas(clientes, cont_clientes, habitaciones, cont_hab, cont_reservas, reservas);
                break;
            case 4:
                menu_infEco(clientes, cont_clientes, habitaciones, cont_hab);
                break;
            case 5:
                importHab(habitaciones, cont_hab);
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


/****************************************************************************/
/*Subprograma:              Men� del subprograma de clientes                */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    Array de clientes y su contador correspondiente */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/*                          con todas sus opciones                          */
/****************************************************************************/
void menu_cliente(tRegCliente clientes[], int *cont_clientes){
    int opc;
    do {
        printf("------------------------------------------------------\n");
        printf("\n\t\tGESTI�N DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificaci�n\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Listado por Categor�a\n");
        printf("\n\t7.- Buscar Cliente\n");
        printf("\n\t8.- Mostrar Cliente\n");
        printf("\n\t0.- Volver al men� principal\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);
        fflush(stdin);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                altaClientes(clientes, cont_clientes);
                system("pause");
                system("cls");
                break;
            case 2:
                bajaClientes(clientes, cont_clientes);
                system("pause");
                system("cls");
                break;
            case 3:
                modClientes(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 4:
                consultaDatosClientes(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 5:
                listadoGrlClientes(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 6:
                listadoClientesCat(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 7:
                buscarCliente(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 8:
                mostrarClientes(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/************************************************************************************************/
/*Subprograma:              Gesti�n alta clientes                                               */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     Array clientes y contador clientes                                  */
/*Prerrequisitos:           Es necesario que haya espacio para nuevos clientes y que el DNI     */
/*                          introducido no exista en el array                                   */
/*Objetivo:                 Se encarga de a�adir nuevos clientes al registro de clientes        */
/************************************************************************************************/
void altaClientes(tRegCliente clientes[], int *cont_clientes){
    printf("\n\n\t\tALTA DE CLIENTES\n");
    printf("\n------------------------------------------------------\n");

    if(*cont_clientes >= MAX_CLIENTES){
        printf("\n\tNo se pueden introducir m�s clientes.\n\n");
        system("pause");
        system("cls");
        return;
    }

    tRegCliente nuevo;

    //Solicita los datos del cliente al usuario - no tendr� reservas de momento
    printf("\n\tIntroduzca el DNI: ");
    fgets(nuevo.dni, sizeof(nuevo.dni), stdin);
    nuevo.dni[strcspn(nuevo.dni, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI no se encuentra en el array - no puede haber 2 DNIs iguales
    int encontrado = -1;
    for(int i=0; i < *cont_clientes; i++){
        if(strcmp(nuevo.dni, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }
    if(encontrado != -1){
        printf("\n\tERROR: El DNI introducido ya est� registrado en el sistema.\n");
        return;
    }

    printf("\n\tIntroduzca el nombre: ");
    fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';
    fflush(stdin);

    do{
        printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
        printf("\n\tIntroduzca el tipo de cliente: ");
        scanf("%d", &nuevo.tipo);
        fflush(stdin);
    } while(nuevo.tipo < 1 || nuevo.tipo >3);

    nuevo.cantReservas = 0;
    for (int j = 0; j < MAX_RESERVAS; j++) {
            strcpy(nuevo.reservas[j], "0"); //Empieza sin reservas
        }


    //Agregamos el cliente al array
    clientes[*cont_clientes] = nuevo;
    (*cont_clientes)++;

    printf("\n\tCliente agregado correctamente\n\n");
}

/************************************************************************************************/
/*Subprograma:              Gesti�n baja clientes                                               */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     Array clientes y contador clientes                                  */
/*Prerrequisitos:           Es necesario que el cliente est� agregado en el listado y que no    */
/*                          posea reservas asociadas a �l                                       */
/*Objetivo:                 Se encarga de eleminar clientes del registro de clientes y guardar  */
/*                          los datos del cliente borrado en un fichero de texto                */
/************************************************************************************************/
void bajaClientes(tRegCliente clientes[], int *cont_clientes){
    printf("\n\n\t\tBAJA DE CLIENTES\n");
    printf("\n------------------------------------------------------\n");

    char cl[10], r[2];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(cl, sizeof(cl), stdin);
    cl[strcspn(cl, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con alg�n cliente del array
    int encontrado = -1;
    for(int i=0; i < *cont_clientes; i++){
        if(strcmp(cl, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }
    if(encontrado == -1){
        printf("\n\tERROR: Este cliente no figura en nuestro registro de datos.\n\n");
        return;
    }
    if(clientes[encontrado].cantReservas != 0){
        printf("\n\tERROR: No se puede dar de baja al cliente %s ya que tiene reservas asociadas.\n\n", cl);
        return;
    }
    printf("\n\t%s - %s - ", clientes[encontrado].dni, clientes[encontrado].nombre);
    if(clientes[encontrado].tipo == 1){
        printf("Normal\n");
    }else if(clientes[encontrado].tipo == 2){
        printf("VIP\n");
    }else{
        printf("Empresa\n");
    }
    printf("\n\t�Desea dar de baja a este cliente? (S/N): ");
    fgets(r, sizeof(r), stdin);
    r[strcspn(r, "\n")] = '\0';
    fflush(stdin);

    if(strcmp(r, "S") == 0){
        //Guardamos el cliente en el fichero de bajas
        FILE *fichBajas = fopen("bajaHcoClientes.txt", "a");
        if(fichBajas == NULL){
            printf("\n\tERROR: No se pudo abrir el registro de bajas.\n\n");
            return;
        }
        fprintf(fichBajas, "%s - %s - ", clientes[encontrado].dni, clientes[encontrado].nombre);
        if(clientes[encontrado].tipo == 1){
            fprintf(fichBajas, "Normal\n");
        }else if(clientes[encontrado].tipo == 2){
            fprintf(fichBajas, "VIP\n");
        }else{
            fprintf(fichBajas, "Empresa\n");
        }
        fclose(fichBajas);

        //Eliminamos al cliente del fichero de clientes - primero del array tRegClientes
        for (int j = encontrado; j < (*cont_clientes) - 1; j++){
            clientes[j] = clientes[j+1];
        }
        (*cont_clientes)--;

        FILE *fich = fopen("clientes.dat", "w");
        if(fich == NULL){
            printf("\n\tERROR: No se pudo abrir el archivo de clientes.\n\n");
            return;
        }
        for (int i=0; i < *cont_clientes; i++){
            fprintf(fich, "%s %s %d %d\n", clientes[i].dni, clientes[i].nombre, clientes[i].tipo, clientes[i].cantReservas);
            for (int j = 0; j < MAX_RESERVAS; j++) {
                fprintf(fich, "%s", clientes[i].reservas[j]);
            }
        }
        fclose(fich);

        printf("\n\tCliente eliminado correctamente.\n\n");
    } else{
        printf("\n\tEl cliente no ha sido eliminado.\n\n");
    }
}

/************************************************************************************************/
/*Subprograma:              Gesti�n modificaci�n de datos de clientes                           */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     Array clientes                                                      */
/*Prerrequisitos:           Es necesario que el cliente est� agregado en el listado             */
/*Objetivo:                 Se encarga de cambiar datos de los clientes guardados y mantener    */
/*                          los cambios en el fichero. No permite cambiar DNI ni reservas       */
/************************************************************************************************/
void modClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tMODIFICACI�N DATOS DE CLIENTES\n");
    printf("\n------------------------------------------------------------\n");

    char select[10];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
    int encontrado = -1;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        printf("\n\t%s - %s - ", clientes[encontrado].dni, clientes[encontrado].nombre);
        if(clientes[encontrado].tipo == 1){
            printf("Normal\n");
        }else if(clientes[encontrado].tipo == 2){
            printf("VIP\n");
        }else{
            printf("Empresa\n");
        }

        //Selecci�n de qu� se quiere ejecutar
        int opc;
        do{
            printf("\n\n\tSELECCIONE UNA OPCI�N");
            printf("\n\t1- Cambiar nombre\n");
            printf("\n\t2- Cambiar tipo de cliente\n");
            printf("\n\t0- Salir\n");

            printf("\n\tSeleccione una opci�n: ");
            scanf("%d", &opc);
            fflush(stdin);

            switch(opc){
                case 1:
                    printf("\n\tIntroduzca el nombre: ");
                    fgets(clientes[encontrado].nombre, sizeof(clientes[encontrado].nombre), stdin);
                    clientes[encontrado].nombre[strcspn(clientes[encontrado].nombre, "\n")] = '\0';
                    break;
                case 2:
                    do{
                        printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
                        printf("\n\tIntroduzca el tipo de cliente: ");
                        scanf("%d", &clientes[encontrado].tipo);

                        if(clientes[encontrado].tipo < 1 || clientes[encontrado].tipo > 3){
                            printf("\n\tERROR: El tipo introducido no es v�lido. Intente de nuevo.\n");
                        }
                    } while(clientes[encontrado].tipo < 1 || clientes[encontrado].tipo > 3);
                    break;
                case 0:
                    break;
            }
        }while(opc != 0);
    }else{
        printf("\n\tEl cliente %s no se encuentra en nuestro sistema.\n\n", select);
    }
}

/************************************************************************************************/
/*Subprograma:              Consulta de datos de un cliente                                     */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           Es necesario que el cliente est� agregado en el listado             */
/*Objetivo:                 Se encarga de mostrar los datos del cliente seleccionado            */
/************************************************************************************************/
void consultaDatosClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tCONSULTA DE DATOS DE UN CLIENTE\n");
    printf("\n------------------------------------------------------------\n");

    char select[10];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
    int encontrado = -1;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        printf("\n\tDNI: %s\n\n\tNombre: %s\n\n\tTipo de cliente: ", clientes[encontrado].dni, clientes[encontrado].nombre);
        if(clientes[encontrado].tipo == 1){
            printf("Normal");
        }else if(clientes[encontrado].tipo == 2){
            printf("VIP");
        }else{
            printf("Empresa");
        }
        printf("\n\n\tReservas: %d\n", clientes[encontrado].cantReservas);
        if(clientes[encontrado].cantReservas != 0){
            printf("\n\tHabitaciones Reservadas: ");
            for (int j = 0; j < MAX_RESERVAS; j++) {
                if(strcmp(clientes[encontrado].reservas[j], "0") != 0){
                    printf("%s ", clientes[encontrado].reservas[j]);
                }
            }
            printf("\n\n");
        }
    }else{
        printf("\n\tEl cliente %s no se encuentra en nuestro sistema.\n\n", select);
    }
}

/************************************************************************************************/
/*Subprograma:              Mostrar listado de clientes                                         */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de mostrar los datos de los clientes                     */
/************************************************************************************************/
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tLISTADO GENERAL DE CLIENTES\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tNombre y apellidos\tDNI\t\tCategor�a\n");
    printf("      |����������������������|�������������|����������������|");

    for(int i = 0; i < cont_clientes; i++){
        printf("\n\t%-20s\t%s\t", clientes[i].nombre, clientes[i].dni);

        if(clientes[i].tipo == 1){
            printf("Normal\n");
        }else if(clientes[i].tipo == 2){
            printf("VIP\n");
        }else{
            printf("Empresa\n");
        }
    }
    printf("\n");
}

/**********************************************************************************************************/
/*Subprograma:              Mostrar listado de clientes por categor�a                                     */
/*Tipo:                     Procedimiento (funci�n tipo void)                                             */
/*Par�metros de entrada:    Array clientes y contador clientes                                            */
/*Par�metros de salida:     ---                                                                           */
/*Prerrequisitos:           ---                                                                           */
/*Objetivo:                 Se encarga de mostrar los datos de los clientes de la categor�a seleccionada  */
/**********************************************************************************************************/
void listadoClientesCat(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tLISTADO DE CLIENTES - Categor�as\n");
    printf("\n--------------------------------------------------------------------\n");

    int cat, cont = 0;
    do{
        printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
        printf("\n\tSeleccione una categor�a: ");
        scanf("%d", &cat);
    } while(cat < 1 || cat > 3);

    system("pause");
    system("cls");

    if(cat == 1){
        printf("\n\tLISTADO DE CLIENTES - Categor�a Normal\n");
        printf("\n--------------------------------------------------------------------\n");

        printf("\n\tNombre y apellidos\tDNI\n");
        for(int i=0; i < cont_clientes; i++){
            if(clientes[i].tipo == cat){
                printf("\n\t%-20s\t%s\n", clientes[i].nombre, clientes[i].dni);
                cont++;
            }
        }
        printf("\n\tTotal: %d Clientes Normales.\n\n", cont);
    }else if(cat == 2){
        printf("\n\tLISTADO DE CLIENTES - Categor�a VIP\n");
        printf("\n--------------------------------------------------------------------\n");

        printf("\n\tNombre y apellidos\tDNI\n");
        for(int i=0; i < cont_clientes; i++){
            if(clientes[i].tipo == cat){
                printf("\n\t%-20s\t%s\n", clientes[i].nombre, clientes[i].dni);
                cont++;
            }
        }
        printf("\n\tTotal: %d Clientes VIP.\n\n", cont);
    } else if(cat == 3){
        printf("\n\tLISTADO DE CLIENTES - Categor�a Empresa\n");
        printf("\n--------------------------------------------------------------------\n");

        printf("\n\tNombre y apellidos\tDNI\n");
        for(int i=0; i < cont_clientes; i++){
            if(clientes[i].tipo == cat){
                printf("\n\t%-20s\t%s\n", clientes[i].nombre, clientes[i].dni);
                cont++;
            }
        }
        printf("\n\tTotal: %d Clientes Empresa.\n\n", cont);
    }
}

/**************************************************************************************/
/*Subprograma:              Buscar cliente en el array                                */
/*Tipo:                     Procedimiento (funci�n tipo void)                         */
/*Par�metros de entrada:    Array de clientes y contador de clientes                  */
/*Par�metros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Solicita un DNI al usuario y lo busca en el array,        */
/*                          devolviendo su posici�n o -1 si no est� en el array       */
/**************************************************************************************/
void buscarCliente(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tBUSCAR CLIENTE\n");
    printf("\n--------------------------------------------------------------------\n");

    char select[10];
    int encontrado = -1;
    printf("\n\tIntroduzca el DNI del cliente al cual quiere buscar: ");
    fgets(select, sizeof(select), stdin);

    //Busca el DNI en el array de clientes
    for(int i = 0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
            encontrado = i;
        }
    }

    //Muestra la posici�n del cliente en el array
    if(encontrado == -1){
        printf("\n\tEl cliente %s se encuentra en la posici�n %d\n", select, encontrado);
        printf("\n\tEse DNI no se encuentra en nuestro sistema.\n\n");
    } else {
        printf("\n\tEl cliente %s se encuentra en la %d� posici�n\n\n", select, encontrado + 1);
    }
}

/**************************************************************************************/
/*Subprograma:              Mostrar clientes                                          */
/*Tipo:                     Procedimiento (funci�n tipo void)                         */
/*Par�metros de entrada:    Array de clientes y contador de clientes                  */
/*Par�metros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Muestra todos los datos de los clientes                   */
/**************************************************************************************/
void mostrarClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tMOSTRAR CLIENTES\n");
    printf("\n--------------------------------------------------------------------\n");

    for(int i = 0; i < cont_clientes; i++){
        printf("\n\n\tDNI: %s\n\n\tNombre: %s\n\n\tTipo de cliente: ", clientes[i].dni, clientes[i].nombre);
        if(clientes[i].tipo == 1){
            printf("Normal");
        }else if(clientes[i].tipo == 2){
            printf("VIP");
        }else{
            printf("Empresa");
        }
        printf("\n\n\tReservas: %d", clientes[i].cantReservas);
        if(clientes[i].cantReservas != 0){
            printf("\n\n\tHabitaciones Reservadas: ");
            for (int j = 0; j < MAX_RESERVAS; j++) {
                if(strcmp(clientes[i].reservas[j], "0") != 0){
                    printf("%s ", clientes[i].reservas[j]);
                }
            }
        }
        printf("\n\n\n\t��������������������������������\n");
    }
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
        printf("------------------------------------------------------\n");
        printf("\n\t\tGESTI�N DE HABITACIONES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificaci�n\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Buscar Habitaci�n\n");
        printf("\n\t7.- Mostrar Habitaci�n\n");
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
            case 6:
                buscarHab(habitaciones, *cont_hab);
                system("pause");
                system("cls");
                break;
            case 7:
                mostrarHab(habitaciones, *cont_hab);
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
    printf("\n\n\t\tALTA DE HABITACIONES\n");
    printf("\n------------------------------------------------------\n");

    if (*cont_hab >= MAX_HABITACIONES){
        printf("\n\tNo es posible a�adir nuevas habitaciones.\n");
        return;
    }

    tRegHabitacion nueva;

    //Genera el c�digo de la habitaci�n de forma aleatoria (se repite hasta que el c�digo no exista)
    //Para que no genere siempre el mismo n�mero
    int encontrado = 0;
    do{
        srand(time(NULL));

        //Genera un n�mero del 1 al 1000
        int num = rand() %999 + 1;
        sprintf(nueva.codigo, "HAB_%03d", num);

        //Comprobamos que el c�digo no se encuentra en el array
        int existe = -1;
        for(int i = 0; i < *cont_hab; i++){
            if(strcmp(nueva.codigo, habitaciones[i].codigo) == 0){
                existe = i;
                break;
            }
        }

        if(existe == -1){
            encontrado = 1;
        }
    } while(encontrado == 0);
    printf("\n\tC�digo de la habitaci�n: %s", nueva.codigo);

    //Solicita el resto de informaci�n de la habitaci�n
    printf("\n\tTipo de habitaci�n: 1 = Individual, 2 = Doble, 3 = Suite");
    do{
        printf("\n\tIntroduzca el tipo de la nueva habitaci�n: ");
        scanf("%d", &nueva.tipo);
        fflush(stdin);
    }while(nueva.tipo < 1 || nueva.tipo > 3);

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
    printf("\n\n\t\tBAJA DE HABITACIONES\n");
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
    printf("\n\n\t\tMODIFICACI�N DATOS DE HABITACIONES\n");
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
    printf("\n\n\t\tCONSULTA DE DATOS DE UNA HABITACI�N\n");
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
    printf("\n\n\t\tLISTADO GENERAL DE HABITACIONES\n");
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

/**************************************************************************************/
/*Subprograma:              Buscar habitaci�n en el array                             */
/*Tipo:                     Procedimiento (funci�n tipo void)                         */
/*Par�metros de entrada:    Array de habitaciones y contador de habitaciones          */
/*Par�metros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Solicita un c�digo al usuario y lo busca en el array,     */
/*                          devolviendo su posici�n o -1 si no est� en el array       */
/**************************************************************************************/
void buscarHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tBUSCAR HABITACI�N\n");
    printf("\n--------------------------------------------------------------------\n");

    char select[8];
    int encontrado = -1;
    printf("\n\tIntroduzca el c�digo de la habitaci�n que quiere buscar: ");
    fgets(select, sizeof(select), stdin);

    //Busca el DNI en el array de clientes
    for(int i = 0; i < cont_hab; i++){
        if(strcmp(select, habitaciones[i].codigo) == 0){
            encontrado = i;
        }
    }

    //Muestra la posici�n del cliente en el array
    if(encontrado == -1){
        printf("\n\tLa habitaci�n %s se encuentra en la posici�n %d\n", select, encontrado);
        printf("\n\tEsa habitaci�n no se encuentra en nuestro sistema.\n\n");
    } else {
        printf("\n\tLa habitaci�n %s se encuentra en la %d� posici�n\n\n", select, encontrado + 1);
    }
}

/**************************************************************************************/
/*Subprograma:              Mostrar habitaciones                                      */
/*Tipo:                     Procedimiento (funci�n tipo void)                         */
/*Par�metros de entrada:    Array habitaciones y contador habitaciones                */
/*Par�metros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Muestra todos los datos de las habitaciones               */
/**************************************************************************************/
void mostrarHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tMOSTRAR HABITACIONES\n");
    printf("\n--------------------------------------------------------------------\n");

    for(int i = 0; i < cont_hab; i++){
        printf("\n\n\tC�digo: %s\n\n\tTipo de Habitaci�n: ", habitaciones[i].codigo);
        if(habitaciones[i].tipo == 1){
            printf("Individual");
        }else if(habitaciones[i].tipo == 2){
            printf("Doble");
        }else{
            printf("Suite");
        }
        printf("\n\n\tPrecio: %.2f", habitaciones[i].precio);
        printf("\n\n\n\t��������������������������������\n");
    }
}

/****************************************************************************/
/*Subprograma:              Men� de las reservas                            */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Presenta por pantalla el men� del subprograma   */
/*                          con todas las opciones disponibles              */
/****************************************************************************/
void menu_reservas(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab, int *cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    int opc;
    do{
        printf("------------------------------------------------------\n");
        printf("\n\t\tGESTI�N DE RESERVAS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Realizar Reserva\n");
        printf("\n\t2.- Cancelar Reserva\n");
        printf("\n\t3.- Consultar Reservas de un Cliente\n");
        printf("\n\t4.- Listado General de Reservas\n");
        printf("\n\t0.- Volver al men� principal\n");

        printf("\n\tSelecciona una opci�n: ");
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
/*Subprograma:              Gesti�n realizar reservas                                           */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Arrays clientes, habitaciones y reservas, y contadores de clientes, */
/*                          habitaciones y reservas                                             */
/*Par�metros de salida:     Arrays clientes y reservas, y contador reservas                     */
/*Prerrequisitos:           Es necesario que haya espacio para nuevos clientes y que el DNI     */
/*                          introducido no exista en el array                                   */
/*Objetivo:                 Se encarga de a�adir nuevas reservas al array de reservas. Tambi�n  */
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

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
    int encontrado = -1, existe = -1, fecha;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        if(clientes[encontrado].cantReservas >= 5){
            printf("\n\tEste cliente ha alcanzado el m�ximo de reservas permitidas.\n");
            return;
        }
        printf("\n\tIntroduce el c�digo de la habitaci�n: ");
        fgets(cod, sizeof(cod), stdin);
        cod[strcspn(cod, "\n")] = '\0';
        fflush(stdin);

        //Comprobamos que el c�digo se corresponde con alguna habitaci�n del array
        for(int i=0; i < cont_hab; i++){
            if(strcmp(cod, habitaciones[i].codigo) == 0){
                    existe = i;
                    break;
            }
        }
        if(existe != -1){
            //Comprobamos que no est� ocupada por ning�n cliente
            for (int i = 0; i < cont_clientes;  i++){
                if(clientes[i].cantReservas != 0){
                    for (int j = 0; j < MAX_RESERVAS; j++){
                        if(strcmp(habitaciones[existe].codigo, clientes[i].reservas[j]) == 0){
                            printf("\n\tERROR: No se puede dar reservar la habitaci�n %s ya que est� ocupada.\n", habitaciones[existe].codigo);
                            return;
                        }
                    }
                }
            }
        } else{
            printf("\n\tERROR: Esta habitaci�n no figura en nuestro registro de datos.\n\n");
            return;
        }
    }else{
        printf("\n\tEl cliente %s no se encuentra en nuestro sistema.\n\n", select);
        return;
    }

    //Guardamos la reserva en el array de reservas, y los cambios correspondientes en el cliente y los contadores
    //Solicitamos el d�a
    printf("\n\tIntroduzca el d�a en que se reserva la habitaci�n: ");
    scanf("%d", &fecha);
    fflush(stdin);

    //Cambios en las reservas
    for (int i = 0; i < DIAS_MES; i++){
        if ( (fecha -1) == i){
            for (int j = 0; j < MAX_HABITACIONES; j++){
                if(strcmp (reservas[i][j], "0") != 0){
                    strcpy(reservas[i][j], cod);
                    break; //Solo la a�ade una vez
                }
            }
        }
    }

    //Cambios en el cliente
    (clientes[encontrado].cantReservas)++;
    for (int i = 0; i < MAX_RESERVAS; i++){
        if(strcmp (clientes[encontrado].reservas[i], "0") == 0){
            strcpy(clientes[encontrado].reservas[i], cod);
            break; //Solo la a�ade una vez
        }
    }

    //Cambios en el contador de reservas
    (*cont_reservas)++;
}

/************************************************************************************************/
/*Subprograma:              Gesti�n cancelar reservas                                           */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Arrays clientes, habitaciones y reservas, y contadores clientes,    */
/*                          habitaciones y reservas.                                            */
/*Par�metros de salida:     Arrays clientes y reservas y contador reservas.                     */
/*Prerrequisitos:           Es necesario que el DNI est� agregado en el listado                 */
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

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
    int encontrado = -1;
    for(int i=0; i < cont_clientes; i++){
        if(strcmp(select, clientes[i].dni) == 0){
                encontrado = i;
                break;
        }
    }

    //Guardamos las reservas eliminadas en el fichero de cancelaci�n y realizamos los cambios en el array reservas
    //Solicitamos fecha
    char fecha[11];
    printf("\n\tIntroduzca la fecha (DD/MM/AAAA): ");
    fgets(fecha, sizeof(fecha), stdin);
    fecha[strcspn(fecha, "\n")] = '\0';
    fflush(stdin);

    FILE *fichCanc= fopen("cancelacionHcoReservas.txt", "a");
    if(fichCanc == NULL){
        printf("\n\tERROR: No se pudo abrir el registro de cancelaci�n.\n\n");
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
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Arrays clientes, habitaciones y reservas, y contadores clientes,    */
/*                          habitaciones y reservas                                             */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           Es necesario que el cliente est� agregado en el listado             */
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

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
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
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Arrays clientes, habitaciones y reservas, y contadores clientes,    */
/*                          habitaciones y reservas                                             */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           Que existan reservas                                                */
/*Objetivo:                 Se encarga de mostrar los datos de las reservas activas             */
/************************************************************************************************/
void listadoGrlReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab, int cont_reservas, char reservas[DIAS_MES][MAX_HABITACIONES][8]){
    printf("\n\n\t\tLISTADO GENERAL DE RESERVAS\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tNombre Cliente\t\tC�digo Habitaci�n\tTipo Habitaci�n\n");
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

/****************************************************************************/
/*Subprograma:              Men� de los informes econ�micos                 */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Presenta por pantalla el men� del subprograma   */
/*                          con todas las opciones disponibles              */
/****************************************************************************/
void menu_infEco(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab){
    int opc;
    do{
        printf("------------------------------------------------------\n");
        printf("\n\t\tINFORMES ECON�MICOS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Informe Mensual por Categor�a de Cliente\n");
        printf("\n\t2.- Informe Mensual de Ocuapaci�n de Habitaciones\n");
        printf("\n\t3.- Informe Mensual de Ingresos por Reservas\n");
        printf("\n\t0.- Volver al men� principal\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                infCatCliente(clientes, *cont_clientes);
                system("pause");
                system("cls");
                break;
            case 2:
                infOcupHab(clientes, *cont_clientes, *cont_hab);
                system("pause");
                system("cls");
                break;
            case 3:
                infIngrReservas(clientes, *cont_clientes, habitaciones, *cont_hab);
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/*************************************************************************************************/
/*Subprograma:              Informe Mensual Categor�a Cliente                                    */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array clientes y contador de clientes                                */
/*Par�metros de salida:     ---                                                                  */
/*Prerrequisitos:           ---                                                                  */
/*Objetivo:                 Mostrar por pantalla la cantidad de clientes de cada tipo que hay    */
/*                          registrados en el array y el importe registrado para cada tipo       */
/*************************************************************************************************/
void infCatCliente(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tINFORME MENSUAL (Por Categor�a de Clientes)\n");
    printf("\n--------------------------------------------------------------------\n");

    //Calcula cuantos clientes hay de cada tipo
    int normales = 0, vip = 0, empresas = 0, precio_normal = 100, precio_vip = 150, precio_empresas = 200, total = 0;
    for(int i = 0; i < cont_clientes; i++){
        if(clientes[i].tipo == 1){
            normales++;
        } else if(clientes[i].tipo == 2){
            vip++;
        } else{
            empresas++;
        }
    }

    //Muestra por pantalla la cantidad de clientes
    printf("\n\t** N�mero de clientes:");
    printf("\n\tNormales:\t%d", normales);
    printf("\n\tVIP:\t\t%d", vip);
    printf("\n\tEmpresas:\t%d", empresas);
    printf("\n\tTotal:\t%d clientes\n", cont_clientes);

    //Calcula los importes registrados y los muestra por pantalla
    normales = normales * precio_normal;
    vip = vip * precio_vip;
    empresas = empresas * precio_empresas;
    total = normales + vip + empresas;

    //Como el programa no me muestra el s�mbolo � lo he cambiado por "euros"
    printf("\n\t** Importes Registrados:");
    printf("\n\tNormales:\t%d euros", normales);
    printf("\n\tVIP:\t\t%d euros", vip);
    printf("\n\tEmpresas:\t%d euros", empresas);
    printf("\n\tImporte Total: %d euros\n\n", total);
}

/*************************************************************************************************/
/*Subprograma:              Informe Mensual Categor�a Cliente                                    */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array clientes y contador de clientes                                */
/*Par�metros de salida:     ---                                                                  */
/*Prerrequisitos:           ---                                                                  */
/*Objetivo:                 Mostrar por pantalla la cantidad de clientes de cada tipo que hay    */
/*                          registrados en el array y el importe registrado para cada tipo       */
/*************************************************************************************************/
void infOcupHab(tRegCliente clientes[], int cont_clientes, int cont_hab){
    printf("\n\n\t\tINFORME MENSUAL (Ocupaci�n de Habitaciones)\n");
    printf("\n--------------------------------------------------------------------\n");

    //Busca cu�ntas habitaciones est�n ocupadas
    int ocupadas = 0, libres;
    float porcentaje;
    for (int i = 0; i < cont_clientes; i++){
        if(clientes[i].cantReservas != 0){
            for (int j = 0; j < MAX_RESERVAS; j++){
                if(strcmp(clientes[i].reservas[j], "0") != 0){
                    ocupadas++;
                }
            }
        }
    }
    libres = cont_hab - ocupadas;

    //Para calcular el porcentaje, pasamos los int a float para que no haya problemas
    porcentaje = (((float)ocupadas / (float)cont_hab) * 100);

    //Muestra los resultados de ocupaci�n de las habitaci�n
    printf("\n\tTotal de habitaciones: %d\n", cont_hab);
    printf("\n\tOcupadas: %d\n", ocupadas);
    printf("\n\tLibres: %d\n", libres);
    printf("\n\n\tPorcentaje de ocupaci�n: %.1f %%\n\n", porcentaje);
}

/*************************************************************************************************/
/*Subprograma:              Informe Mensual Categor�a Cliente                                    */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array clientes y contador de clientes                                */
/*Par�metros de salida:     ---                                                                  */
/*Prerrequisitos:           ---                                                                  */
/*Objetivo:                 Mostrar por pantalla la cantidad de clientes de cada tipo que hay    */
/*                          registrados en el array y el importe registrado para cada tipo       */
/*************************************************************************************************/
void infIngrReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tINFORME MENSUAL (Ingresos por Reservas)\n");
    printf("\n--------------------------------------------------------------------\n");

    //Busca las habitaciones que est�n ocupadas y luego busca el precio de la habitaci�n para sumarlo al total
    int ocupadas = 0;
    float total = 0;
    for (int i = 0; i < cont_clientes; i++){
        if(clientes[i].cantReservas != 0){
            for (int j = 0; j < MAX_RESERVAS; j++){
                if(strcmp(clientes[i].reservas[j], "0") != 0){
                    ocupadas++;
                    for (int k = 0; k < cont_hab; k++){
                        if(strcmp(clientes[i]. reservas[j], habitaciones[k].codigo) == 0){
                            total = total + habitaciones[k].precio;
                        }
                    }
                }
            }
        }
    }

    //Muestra los resultados
    printf("\n\tN�mero total de reservas: %d\n", ocupadas);
    printf("\n\tIngreso total: %.2f\n\n", total);
}

/*************************************************************************************************/
/*Subprograma:              Importar habitaciones desde fichero                                  */
/*Tipo:                     Procedimiento (funci�n tipo void)                                    */
/*Par�metros de entrada:    Array habitaciones y contador de habitaciones                        */
/*Par�metros de salida:     Array habitaciones y contador de habitaciones                        */
/*Prerrequisitos:           Que haya espacio para m�s habitaciones                               */
/*Objetivo:                 Lee el fichero e importa los datos de las nuevas habitaciones.       */
/*                          Adem�s, genera el c�digo de la habitaci�n autom�ticamente            */
/*************************************************************************************************/
void importHab(tRegHabitacion habitaciones[], int *cont_hab){
    printf("\n\n\t\tIMPORTAR HABITACIONES\n");
    printf("\n-------------------------------------------------------------\n");

    tRegHabitacion nueva;

    FILE *import = fopen("habitacionesNuevas.txt", "r");
    if(import == NULL){
        printf("\n\tERROR al abrir el fichero habitacionesNuevas.txt\n\n");
        return;
    }

    char linea[100];
    while(fgets(linea, sizeof(linea), import) != NULL){
        if(*cont_hab >= MAX_HABITACIONES){
            printf("\n\tNo es posible agregar nuevas habitaciones\n\n");
            return;
        }

        //Quitamos el salto de l�nea
        linea[strcspn(linea, "\n")] = '\0';
        char *tipo = strtok(linea, "#");
        char *precio = strtok(NULL, "#");

        if(tipo != NULL && precio != NULL){
            if(strcmp(tipo, "Individual") == 0){
                nueva.tipo = 1;
            } else if(strcmp(tipo, "Doble") == 0){
                nueva.tipo = 2;
            } else if(strcmp(tipo, "Suite") == 0){
                nueva.tipo = 3;
            }

            nueva.precio = atof(precio);

            //Genera el c�digo de la habitaci�n de forma aleatoria (se repite hasta que el c�digo no exista)
            //Para que no genere siempre el mismo n�mero
            int encontrado = 0;
            do{
                srand(time(NULL));

                //Genera un n�mero del 1 al 1000
                int num = rand() %999 + 1;
                sprintf(nueva.codigo, "HAB_%03d", num);

                //Comprobamos que el c�digo no se encuentra en el array
                int existe = -1;
                for(int i = 0; i < *cont_hab; i++){
                    if(strcmp(nueva.codigo, habitaciones[i].codigo) == 0){
                        existe = i;
                        break;
                    }
                }

                if(existe == -1){
                    encontrado = 1;
                }
            } while(encontrado == 0);
        }

        //Mostramos los datos de la habitaci�n nueva
        printf("\n\tC�digo de la habitaci�n: %s\n", nueva.codigo);
        printf("\n\tTipo de la habitaci�n: %s\n", tipo);
        printf("\n\tPrecio de la habitaci�n: %.2f\n\n", nueva.precio);

        //Agregamos la habitacion al array
        habitaciones[*cont_hab] = nueva;
        (*cont_hab)++;
    }
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
