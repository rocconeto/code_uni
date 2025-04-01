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

#define MAX_CLIENTES 100
#define MAX_RESERVAS 5

typedef struct{
    char dni[10];
    char nombre[50];
    int tipo;
    int cantReservas; //Para saber cu�ntas reservas tiene
    char reservas[MAX_RESERVAS][7];
}tRegCliente;

void menu_princ(tRegCliente clientes[], int *cont_clientes);
void menu_cliente(tRegCliente clientes[], int *cont_clientes);
void altaClientes(tRegCliente clientes[], int *cont_clientes);
void bajaClientes(tRegCliente clientes[], int *cont_clientes);
void modClientes(tRegCliente clientes[], int cont_clientes);
void consultaDatosClientes(tRegCliente clientes[], int cont_clientes);
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes);
void listadoClientesCat(tRegCliente clientes[], int cont_clientes);
void menu_hab();
void menu_reservas();
void guardar_clientes(tRegCliente clientes[], int *cont_clientes);

int main(){
    setlocale(LC_ALL, "spanish");

    tRegCliente clientes[MAX_CLIENTES];
    int cont_clientes = 0;

    printf("\n\t�Bienvenido a la aplicaci�n GEST_HOTEL!\n");
    printf("\n--------------------------------------------------------\n");
    printf("\n\tCargando datos...\n\n");

    //Cargamos los datos del fichero
    FILE *archivo = fopen("clientes.dat", "r");
    if (archivo == NULL) {
        printf("Error al abrir el fichero clientes.dat\n\n");
        exit(1);
    }

    while (fscanf(archivo, "%s", clientes[cont_clientes].dni) == 1) {
        fgetc(archivo); // Consumir salto de l�nea
        fgets(clientes[cont_clientes].nombre, sizeof(clientes[cont_clientes].nombre), archivo);
        clientes[cont_clientes].nombre[strcspn(clientes[cont_clientes].nombre, "\n")] = '\0'; // Eliminar salto de l�nea
        fscanf(archivo, "%d %d", &clientes[cont_clientes].tipo, &clientes[cont_clientes].cantReservas);
        for (int j = 0; j < MAX_RESERVAS; j++) {
            fscanf(archivo, "%s", clientes[cont_clientes].reservas[j]);
        }
        cont_clientes++;

        if (cont_clientes >= MAX_CLIENTES) {
            printf("L�mite de clientes alcanzado.\n");
            break;
        }
    }
    fclose(archivo);

    system("pause");
    system("cls");

    menu_princ(clientes, &cont_clientes);
    return 0;
}

/********************************************************************************/
/*Subprograma:              Men� principal                                      */
/*Tipo:                     Procedimiento (funci�n tipo void)                   */
/*Par�metros de entrada:    ---                                                 */
/*Par�metros de salida:     ---                                                 */
/*Prerrequisitos:           ---                                                 */
/*Objetivo:                 Muestra por pantalla el men� principal del programa */
/********************************************************************************/
void menu_princ(tRegCliente clientes[], int *cont_clientes){
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
                menu_cliente(clientes, cont_clientes);
                break;
            case 2:
                menu_hab();
                break;
            case 3:
                menu_reservas();
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
                printf("\n\t�Gracias por usar nuestro programa!\n\n");

                break;
        }
    }while(opc != 0);
}


/****************************************************************************/
/*Subprograma:              Submen� de la opci�n clientes                   */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/*                          con todas sus opciones                          */
/****************************************************************************/
void menu_cliente(tRegCliente clientes[], int *cont_clientes){
    int opc;
    do {
        printf("\n------------------------------------------------------\n");
        printf("\n\t\tGESTI�N DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificaci�n\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Listado por Categor�a\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);
        getchar();

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
            case 0:
                break;
        }
    }while(opc != 0);
}

/************************************************************************************************/
/*Subprograma:              Gesti�n alta clientes                                               */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     Attay clientes y contador clientes                                  */
/*Prerrequisitos:           Es necesario que haya espacio para nuevos clientes y que el DNI     */
/*                          introducido no exista en el array                                   */
/*Objetivo:                 Se encarga de a�adir nuevos clientes al registro de clientes        */
/************************************************************************************************/
void altaClientes(tRegCliente clientes[], int *cont_clientes){
    printf("\n------------------------------------------------------\n");
    printf("\n\tALTA DE CLIENTES\n");
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

    printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
    printf("\n\tIntroduzca el tipo de cliente: ");
    scanf("%d", &nuevo.tipo);
    fflush(stdin);

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
/*                          el nombre del cliente en otro fichero de texto                      */
/************************************************************************************************/
void bajaClientes(tRegCliente clientes[], int *cont_clientes){
    printf("\n------------------------------------------------------\n");
    printf("\n\tBAJA DE CLIENTES\n");
    printf("\n------------------------------------------------------\n");

    char cl[10], r[2];
    printf("\n\tIntroduce el dni del cliente: ");
    fgets(cl, sizeof(cl), stdin);
    cl[strcspn(cl, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con alg�n cliente del fichero
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
    printf("\n------------------------------------------------------------\n");
    printf("\n\tMODIFICACI�N DATOS DE CLIENTES\n");
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
                    printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
                    printf("\n\tIntroduzca el tipo de cliente: ");
                    scanf("%d", &clientes[encontrado].tipo);
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
    printf("\n------------------------------------------------------------\n");
    printf("\n\tCONSULTA DE DATOS DE UN CLIENTE\n");
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
                    printf("%s", clientes[encontrado].reservas[j]);
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
/*Objetivo:                 Se encarga de a�adir nuevos clientes al registro de clientes        */
/************************************************************************************************/
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n--------------------------------------------------------------------\n");
    printf("\n\tLISTADO GENERAL DE CLIENTES\n");
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

/************************************************************************************************/
/*Subprograma:              Mostrar listado de clientes por categor�a                           */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    Array clientes y contador clientes                                  */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de a�adir nuevos clientes al registro de clientes        */
/************************************************************************************************/
void listadoClientesCat(tRegCliente clientes[], int cont_clientes){
    printf("\n--------------------------------------------------------------------\n");
    printf("\n\tLISTADO DE CLIENTES - Categor�as\n");
    printf("\n--------------------------------------------------------------------\n");

    int cat, cont = 0;
    printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
    printf("\n\tSeleccione una categor�a: ");
    scanf("%d", &cat);

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

/****************************************************************************/
/*Subprograma:              Men� de las habitaciones                        */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/*                          el cual muestra todas las opciones con las      */
/*                          habitaciones                                    */
/****************************************************************************/
void menu_hab(){
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
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                printf("\n\tAltas\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                printf("\n\tBajas\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("\n\tModificaci�n\n\n");
                system("pause");
                system("cls");
                break;
            case 4:
                printf("\n\tConsulta\n\n");
                system("pause");
                system("cls");
                break;
            case 5:
                printf("\n\tListado\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/****************************************************************************/
/*Subprograma:              Men� de las reservas                            */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/*                          el cual muestra todas las opciones relacionadas */
/*                          con las reservas                                */
/****************************************************************************/
void menu_reservas(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTI�N DE RESERVAS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Realizar Reserva\n");
        printf("\n\t2.- Cancelar Reserva\n");
        printf("\n\t3.- Consultar Reservas de un Cliente\n");
        printf("\n\t4.- Listado General de Reservas\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opci�n: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                printf("\n\tRealizar reservas\n\n");
                system("pause");
                system("cls");
                break;
            case 2:
                printf("\n\tCancelar reservas\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("\n\tConsultar reservas\n\n");
                system("pause");
                system("cls");
                break;
            case 4:
                printf("\n\tListado\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

void guardar_clientes(tRegCliente clientes[], int *cont_clientes) {
    FILE *fich = fopen("clientes.dat", "w");

    if (fich == NULL) {
        printf("Error al guardar los clientes.\n");
        return;
    }

    for (int i = 0; i < *cont_clientes; i++) {
        fprintf(fich, "%s\n%s\n%d\n%d", clientes[i].dni, clientes[i].nombre, clientes[i].tipo, clientes[i].cantReservas);
        for (int j = 0; j < MAX_RESERVAS; j++) {
            fprintf(fich, " %s", clientes[i].reservas[j]);
        }
        fprintf(fich, "\n");
    }

    fclose(fich);
}

