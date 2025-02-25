/*  Asigantura: Metodología de la programación Curso: 1
    Tarea que realiza el programa: Gestión de clientes, habitaciones y reservas de un hotel
    Alumno 1: Atanasov Angelov, Daniel
    Alumno 2: Sanz Tomé, Raúl
    Grupo de laboratorio: 30
    Fecha: 24/02/2025 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void menu_princ();
void gest_clientes();
void gest_hab();
void gest_reservas();

int main()
{
    setlocale(LC_ALL, "spanish");
    printf("\n\t¡Bienvenido a la aplicación GEST_HOTEL!\n");
    printf("\n--------------------------------------------------------\n\n");
    system("pause");
    system("cls");
    menu_princ();
    return 0;
}

/********************************************************************************/
/*Subprograma:              Menú principal                                      */
/*Tipo:                     Procedimiento (función tipo void)                   */
/*Parámetros de entrada:    ---                                                 */
/*Parámetros de salida:     ---                                                 */
/*Prerrequisitos:           ---                                                 */
/*Objetivo:                 Muestra por pantalla el menú principal del programa */
/********************************************************************************/
void menu_princ(){
    int opc;
    do{
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

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                gest_clientes();
                break;
            case 2:
                gest_hab();
                break;
            case 3:
                gest_reservas();
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
                printf("\n\tGracias por usar nuestro programa\n");
                printf("\n--------------------------------------------------------\n\n");
                break;
        }
    }while(opc != 0);
}

/********************************************************************************************/
/*Subprograma:              Gestión clientes                                                */
/*Tipo:                     Procedimiento (función tipo void)                               */
/*Parámetros de entrada:    ---                                                             */
/*Parámetros de salida:     ---                                                             */
/*Prerrequisitos:           ---                                                             */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con los clientes  */
/********************************************************************************************/
void gest_clientes(){
    void submenu_cl();

    submenu_cl();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Menú del subprograma                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/****************************************************************************/
void submenu_cl(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\t\tGESTIÓN DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificación\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t6.- Listado por Categoría\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
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
                printf("\n\tModificación\n\n");
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
            case 6:
                printf("\n\tListado-categoria\n\n");
                system("pause");
                system("cls");
                break;
            case 0:
                break;
        }
    }while(opc != 0);
}

/************************************************************************************************/
/*Subprograma:              Gestión habitaciones                                                */
/*Tipo:                     Procedimiento (función tipo void)                                   */
/*Parámetros de entrada:    ---                                                                 */
/*Parámetros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con las habitaciones  */
/************************************************************************************************/
void gest_hab(){
    void submenu_hab();

    submenu_hab();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Menú del subprograma                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/****************************************************************************/
void submenu_hab(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTIÓN DE CLIENTES\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Alta\n");
        printf("\n\t2.- Baja\n");
        printf("\n\t3.- Modificación\n");
        printf("\n\t4.- Consulta\n");
        printf("\n\t5.- Listado General\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
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
                printf("\n\tModificación\n\n");
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

/********************************************************************************************/
/*Subprograma:              Gestión reservas                                                */
/*Tipo:                     Procedimiento (función tipo void)                               */
/*Parámetros de entrada:    ---                                                             */
/*Parámetros de salida:     ---                                                             */
/*Prerrequisitos:           ---                                                             */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con las reservas  */
/********************************************************************************************/
void gest_reservas(){
    void submenu_res();

    submenu_res();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Menú del subprograma                            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el menú del subprograma    */
/****************************************************************************/
void submenu_res(){
    int opc;
    do{
        printf("\n------------------------------------------------------\n");
        printf("\n\tGESTIÓN DE RESERVAS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Realizar Reserva\n");
        printf("\n\t2.- Cancelar Reserva\n");
        printf("\n\t3.- Consultar Reservas de un Cliente\n");
        printf("\n\t4.- Listado General de Reservas\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
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
