#include "main.h"
#include "gestionHabitaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/**************************************************************************************/
/*Subprograma:              Menú de las habitaciones                                  */
/*Tipo:                     Procedimiento (función tipo void)                         */
/*Parámetros de entrada:    Array de las habitaciones y contador de las habitaciones  */
/*Parámetros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Muestra por pantalla el menú del subprograma con          */
/*                          todas sus opciones de las habitaciones                    */
/**************************************************************************************/
void menu_hab(tRegHabitacion habitaciones[], int *cont_hab, tRegCliente clientes[], int *cont_clientes){
    int opc;
    do{
        printf("------------------------------------------------------\n");
        printf("\n\t\tGESTIÓN DE HABITACIONES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificación\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Buscar Habitación\n");
        printf("\n\t7.- Mostrar Habitación\n");
        printf("\n\t0.- Volver al menú principal\n");

        printf("\n\tSelecciona una opción: ");
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
/*Subprograma:              Gestión alta habitaciones                                           */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array habitaciones y contadores de habitaciones                     */
/*Parámetros de salida:     Array habitaciones y contador de habitaciones                       */
/*Prerrequisitos:           Es necesario que haya espacio para nuevas habitaciones              */
/*Objetivo:                 Se encarga de añadir nuevas reservas al array de reservas           */
/************************************************************************************************/
void altaHab(tRegHabitacion habitaciones[], int *cont_hab){
    printf("\n\n\t\tALTA DE HABITACIONES\n");
    printf("\n------------------------------------------------------\n");

    if (*cont_hab >= MAX_HABITACIONES){
        printf("\n\tNo es posible añadir nuevas habitaciones.\n");
        return;
    }

    tRegHabitacion nueva;

    //Genera el código de la habitación de forma aleatoria (se repite hasta que el código no exista)
    //Para que no genere siempre el mismo número
    int encontrado = 0;
    do{
        srand(time(NULL));

        //Genera un número del 1 al 1000
        int num = rand() %999 + 1;
        sprintf(nueva.codigo, "HAB_%03d", num);

        //Comprobamos que el código no se encuentra en el array
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
    printf("\n\tCódigo de la habitación: %s", nueva.codigo);

    //Solicita el resto de información de la habitación
    printf("\n\tTipo de habitación: 1 = Individual, 2 = Doble, 3 = Suite");
    do{
        printf("\n\tIntroduzca el tipo de la nueva habitación: ");
        scanf("%d", &nueva.tipo);
        fflush(stdin);
    }while(nueva.tipo < 1 || nueva.tipo > 3);

    printf("\n\tIntroduzca el precio de la nueva habitación: ");
    scanf("%f", &nueva.precio);
    fflush(stdin);

    //Agregamos la habitación al array
    habitaciones[*cont_hab] = nueva;
    (*cont_hab)++;
}

/************************************************************************************************/
/*Subprograma:              Gestión baja habitacioens                                           */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Arrays habitaciones y clientes y contadores clientes y habitaciones */
/*Parámetros de salida:     Array habitaciones y contador habitaciones                          */
/*Prerrequisitos:           Es necesario que la habitación esté agregada en el listado y que no */
/*                          esté ocupada por ningún cliente                                     */
/*Objetivo:                 Se encarga de eleminar habitaciones del registro de habitaciones    */
/*                          y guardar los datos de la habitación borrada en un fichero de texto */
/************************************************************************************************/
void bajaHab(tRegHabitacion habitaciones[], int *cont_hab , tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tBAJA DE HABITACIONES\n");
    printf("\n------------------------------------------------------\n");

    char cod[8];
    printf("\n\tIntroduce el código de la habitación: ");
    fgets(cod, sizeof(cod), stdin);
    cod[strcspn(cod, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el código se corresponde con alguna habitación del array
    int encontrado = -1;
    for(int i=0; i < *cont_hab; i++){
        if(strcmp(cod, habitaciones[i].codigo) == 0){
                encontrado = i;
                break;
        }
    }
    if(encontrado == -1){
        printf("\n\tERROR: Esta habitación no figura en nuestro registro de datos.\n\n");
        return;
    }

    //Comprobamos que no está ocupada por ningún cliente
    for (int i = 0; i < cont_clientes;  i++){
        if(clientes[i].cantReservas != 0){
            for (int j = 0; j < MAX_RESERVAS; j++){
                if(strcmp(habitaciones[encontrado].codigo, clientes[i].reservas[j]) == 0){
                    printf("\n\tERROR: No se puede dar de baja a la habitación %s ya que tiene reservas asociadas.\n", habitaciones[encontrado].codigo);
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

    //Eliminamos a la habitación del fichero de habitaciones - primero del array tRegHabitacion
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

    printf("\n\tHabitación eliminada correctamente.\n\n");
}

/*************************************************************************************************/
/*Subprograma:              Gestión modificación de datos de habitaciones                        */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Array habitaciones y contador habitaciones                           */
/*Parámetros de salida:     Array habitaciones                                                   */
/*Prerrequisitos:           Es necesario que la habitación esté agregada en el listado           */
/*Objetivo:                 Se encarga de cambiar datos de las habitaciones guardadas y mantener */
/*                          los cambios en el fichero. No permite cambiar el código              */
/*************************************************************************************************/
void modHabitaciones(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tMODIFICACIÓN DATOS DE HABITACIONES\n");
    printf("\n------------------------------------------------------------\n");

    char select[8];
    printf("\n\tIntroduce el código de la habitación: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que el DNI se corresponde con algún cliente del fichero
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

        //Selección de qué se quiere ejecutar
        int opc;
        do{
            printf("\n\n\tSELECCIONE UNA OPCIÓN");
            printf("\n\t1- Cambiar tipo de habitación\n");
            printf("\n\t2- Cambiar precio\n");
            printf("\n\t0- Salir\n");

            printf("\n\tSeleccione una opción: ");
            scanf("%d", &opc);
            fflush(stdin);

            switch(opc){
                case 1:
                    do{
                        printf("\n\tTipo de cliente: 1 = Individual, 2 = Doble, 3 = Suite");
                        printf("\n\tIntroduzca el nuevo tipo de habitación: ");
                        scanf("%d", &habitaciones[encontrado].tipo);

                        if(habitaciones[encontrado].tipo < 1 || habitaciones[encontrado].tipo > 3){
                            printf("\n\tERROR: El tipo introducido no es válido. Intente de nuevo.\n");
                        }
                    } while(habitaciones[encontrado].tipo < 1 || habitaciones[encontrado].tipo > 3);

                    break;
                case 2:
                    printf("\n\tIntroduzca el nuevo precio de la habitación: ");
                    scanf("%f", &habitaciones[encontrado].precio);
                    break;
                case 0:
                    break;
            }
        }while(opc != 0);
    }else{
        printf("\n\tLa habitación %s no se encuentra en nuestro sistema.\n\n", select);
    }
}

/************************************************************************************************/
/*Subprograma:              Consulta de datos de una habitación                                 */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array habitaciones y contador habitaciones                          */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           Es necesario que la habitación esté agregada en el listado          */
/*Objetivo:                 Se encarga de mostrar los datos de la habitación seleccionada       */
/************************************************************************************************/
void consultaDatosHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tCONSULTA DE DATOS DE UNA HABITACIÓN\n");
    printf("\n------------------------------------------------------------\n");

    char select[8];
    printf("\n\tIntroduce el código de la habitación: ");
    fgets(select, sizeof(select), stdin);
    select[strcspn(select, "\n")] = '\0';
    fflush(stdin);

    //Comprobamos que la habitación se corresponde con alguna del fichero
    int encontrado = -1;
    for(int i=0; i < cont_hab; i++){
        if(strcmp(select, habitaciones[i].codigo) == 0){
                encontrado = i;
                break;
        }
    }

    if(encontrado != -1){
        printf("\n\tCódigo: %s\n\n\tTipo de habitación: ", habitaciones[encontrado].codigo);
        if(habitaciones[encontrado].tipo == 1){
            printf("Individual");
        }else if(habitaciones[encontrado].tipo == 2){
            printf("Doble");
        }else{
            printf("Suite");
        }
        printf("\n\n\tPrecio: %.2f\n\n", habitaciones[encontrado].precio);
    }else{
        printf("\n\tLa habitación %s no se encuentra en nuestro sistema.\n\n", select);
        system("pause");
        system("cls");
        consultaDatosHab(habitaciones, cont_hab);
    }
}

/************************************************************************************************/
/*Subprograma:              Mostrar listado de habitaciones                                     */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    Array habitaciones y contador habitaciones                          */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de mostrar los datos de las habitaciones                 */
/************************************************************************************************/
void listadoHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tLISTADO GENERAL DE HABITACIONES\n");
    printf("\n--------------------------------------------------------------------\n");

    printf("\n\tCódigo\t\tTipo\t\tPrecio\n");
    printf("      |············|················|··············|");

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
/*Subprograma:              Buscar habitación en el array                             */
/*Tipo:                     Procedimiento (función tipo void)                         */
/*Parámetros de entrada:    Array de habitaciones y contador de habitaciones          */
/*Parámetros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Solicita un código al usuario y lo busca en el array,     */
/*                          devolviendo su posición o -1 si no está en el array       */
/**************************************************************************************/
void buscarHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tBUSCAR HABITACIÓN\n");
    printf("\n--------------------------------------------------------------------\n");

    char select[8];
    int encontrado = -1;
    printf("\n\tIntroduzca el código de la habitación que quiere buscar: ");
    fgets(select, sizeof(select), stdin);

    //Busca el DNI en el array de clientes
    for(int i = 0; i < cont_hab; i++){
        if(strcmp(select, habitaciones[i].codigo) == 0){
            encontrado = i;
        }
    }

    //Muestra la posición del cliente en el array
    if(encontrado == -1){
        printf("\n\tLa habitación %s se encuentra en la posición %d\n", select, encontrado);
        printf("\n\tEsa habitación no se encuentra en nuestro sistema.\n\n");
    } else {
        printf("\n\tLa habitación %s se encuentra en la %dª posición\n\n", select, encontrado + 1);
    }
}

/**************************************************************************************/
/*Subprograma:              Mostrar habitaciones                                      */
/*Tipo:                     Procedimiento (función tipo void)                         */
/*Parámetros de entrada:    Array habitaciones y contador habitaciones                */
/*Parámetros de salida:     ---                                                       */
/*Prerrequisitos:           ---                                                       */
/*Objetivo:                 Muestra todos los datos de las habitaciones               */
/**************************************************************************************/
void mostrarHab(tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tMOSTRAR HABITACIONES\n");
    printf("\n--------------------------------------------------------------------\n");

    for(int i = 0; i < cont_hab; i++){
        printf("\n\n\tCódigo: %s\n\n\tTipo de Habitación: ", habitaciones[i].codigo);
        if(habitaciones[i].tipo == 1){
            printf("Individual");
        }else if(habitaciones[i].tipo == 2){
            printf("Doble");
        }else{
            printf("Suite");
        }
        printf("\n\n\tPrecio: %.2f", habitaciones[i].precio);
        printf("\n\n\n\t································\n");
    }
}
