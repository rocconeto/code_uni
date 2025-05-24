#include "main.h"
#include "gestionClientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/****************************************************************************/
/*Subprograma:              Menú del subprograma de clientes                */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    Array de clientes y su contador correspondiente */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/*                          con todas sus opciones                          */
/****************************************************************************/
void menu_cliente(tRegCliente clientes[], int *cont_clientes){
    int opc;
    do {
        printf("------------------------------------------------------\n");
        printf("\n\t\tGESTIÓN DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificación\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Listado por Categoría\n");
        printf("\n\t7.- Buscar Cliente\n");
        printf("\n\t8.- Mostrar Cliente\n");
        printf("\n\t0.- Volver al menú principal\n");

        printf("\n\tSelecciona una opción: ");
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
/*Subprograma:              Gestión alta clientes                                               */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array clientes y contador clientes                                  */
/*Parámetros de salida:     Array clientes y contador clientes                                  */
/*Prerrequisitos:           Es necesario que haya espacio para nuevos clientes y que el DNI     */
/*                          introducido no exista en el array                                   */
/*Objetivo:                 Se encarga de añadir nuevos clientes al registro de clientes        */
/************************************************************************************************/
void altaClientes(tRegCliente clientes[], int *cont_clientes){
    printf("\n\n\t\tALTA DE CLIENTES\n");
    printf("\n------------------------------------------------------\n");

    if(*cont_clientes >= MAX_CLIENTES){
        printf("\n\tNo se pueden introducir más clientes.\n\n");
        system("pause");
        system("cls");
        return;
    }

    tRegCliente nuevo;

    //Solicita los datos del cliente al usuario - no tendrá reservas de momento
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
        printf("\n\tERROR: El DNI introducido ya está registrado en el sistema.\n");
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
/*Subprograma:              Gestión baja clientes                                               */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array clientes y contador clientes                                  */
/*Parámetros de salida:     Array clientes y contador clientes                                  */
/*Prerrequisitos:           Es necesario que el cliente esté agregado en el listado y que no    */
/*                          posea reservas asociadas a él                                       */
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

    //Comprobamos que el DNI se corresponde con algún cliente del array
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
    printf("\n\t¿Desea dar de baja a este cliente? (S/N): ");
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
/*Subprograma:              Gestión modificación de datos de clientes                           */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array clientes y contador clientes                                  */
/*Parámetros de salida:     Array clientes                                                      */
/*Prerrequisitos:           Es necesario que el cliente esté agregado en el listado             */
/*Objetivo:                 Se encarga de cambiar datos de los clientes guardados y mantener    */
/*                          los cambios en el fichero. No permite cambiar DNI ni reservas       */
/************************************************************************************************/
void modClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tMODIFICACIÓN DATOS DE CLIENTES\n");
    printf("\n------------------------------------------------------------\n");

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

    if(encontrado != -1){
        printf("\n\t%s - %s - ", clientes[encontrado].dni, clientes[encontrado].nombre);
        if(clientes[encontrado].tipo == 1){
            printf("Normal\n");
        }else if(clientes[encontrado].tipo == 2){
            printf("VIP\n");
        }else{
            printf("Empresa\n");
        }

        //Selección de qué se quiere ejecutar
        int opc;
        do{
            printf("\n\n\tSELECCIONE UNA OPCIÓN");
            printf("\n\t1- Cambiar nombre\n");
            printf("\n\t2- Cambiar tipo de cliente\n");
            printf("\n\t0- Salir\n");

            printf("\n\tSeleccione una opción: ");
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
                            printf("\n\tERROR: El tipo introducido no es válido. Intente de nuevo.\n");
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
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array clientes y contador clientes                                  */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           Es necesario que el cliente esté agregado en el listado             */
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

    //Comprobamos que el DNI se corresponde con algún cliente del fichero
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
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array clientes y contador clientes                                  */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de mostrar los datos de los clientes                     */
/************************************************************************************************/
void listadoGrlClientes(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tLISTADO GENERAL DE CLIENTES\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tNombre y apellidos\tDNI\t\tCategoría\n");
    printf("      |······················|·············|················|");

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
/*Subprograma:              Mostrar listado de clientes por categoría                                     */
/*Tipo:                     Procedimiento (función tipo void)                                             */
/*Parámetros de entrada:    Array clientes y contador clientes                                            */
/*Parámetros de salida:     ---                                                                           */
/*Prerrequisitos:           ---                                                                           */
/*Objetivo:                 Se encarga de mostrar los datos de los clientes de la categoría seleccionada  */
/**********************************************************************************************************/
void listadoClientesCat(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tLISTADO DE CLIENTES - Categorías\n");
    printf("\n--------------------------------------------------------------------\n");

    int cat, cont = 0;
    do{
        printf("\n\tTipo de cliente: 1 = Normal, 2 = VIP, 3 = Empresa");
        printf("\n\tSeleccione una categoría: ");
        scanf("%d", &cat);
    } while(cat < 1 || cat > 3);

    system("pause");
    system("cls");

    if(cat == 1){
        printf("\n\tLISTADO DE CLIENTES - Categoría Normal\n");
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
        printf("\n\tLISTADO DE CLIENTES - Categoría VIP\n");
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
        printf("\n\tLISTADO DE CLIENTES - Categoría Empresa\n");
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
/*Tipo:                     Procedimiento (función tipo void)                         */
/*Parámetros de entrada:    Array de clientes y contador de clientes                  */
/*Parámetros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Solicita un DNI al usuario y lo busca en el array,        */
/*                          devolviendo su posición o -1 si no está en el array       */
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

    //Muestra la posición del cliente en el array
    if(encontrado == -1){
        printf("\n\tEl cliente %s se encuentra en la posición %d\n", select, encontrado);
        printf("\n\tEse DNI no se encuentra en nuestro sistema.\n\n");
    } else {
        printf("\n\tEl cliente %s se encuentra en la %dª posición\n\n", select, encontrado + 1);
    }
}

/**************************************************************************************/
/*Subprograma:              Mostrar clientes                                          */
/*Tipo:                     Procedimiento (función tipo void)                         */
/*Parámetros de entrada:    Array de clientes y contador de clientes                  */
/*Parámetros de salida:     ---                                                       */
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
        printf("\n\n\n\t································\n");
    }
}
