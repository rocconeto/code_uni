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

int main()
{
    setlocale(LC_ALL, "spanish");
    printf("¡Bienvenido a la aplicación GEST_HOTEL!\n");
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
        printf("\tMENÚ PRINCIPAL\n");
        printf("-----------------------------");
        printf("\n\t1.- Gestión de Clientes");
        printf("\n\t2.- Gestión de Habitaciones");
        printf("\n\t3.- Gestión de Reservas");
        printf("\n\t4.- Informes Económicos");
        printf("\n\t5.- Importar Habitaciones desde Fichero");
        printf("\n\t0.- Salir\n");

        printf("\nSelecciona una opción: ");
        scanf("%d", &opc);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                gest_clientes();
                break;
            case 2:
                printf("\n\tHabitaciones\n\n");
                system("pause");
                system("cls");
                break;
            case 3:
                printf("\n\tReservas\n\n");
                system("pause");
                system("cls");
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
                printf("\n\tGracias por usar nuestro programa\n\n");
                printf("-------------------------");
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
    void submenu();

    submenu();

    system("pause");
    system("cls");
}

void submenu(){
    int opc;
    do{
        printf("\GESTIÓN DE CLIENTES\n");
        printf("-----------------------------");
        printf("\n\t1.- Alta");
        printf("\n\t2.- Baja");
        printf("\n\t3.- Modificación");
        printf("\n\t4.- Consulta");
        printf("\n\t5.- Listado General");
        printf("\n\t6.- Listado por Categoría");
        printf("\n\t0.- Salir\n");

        printf("\nSelecciona una opción: ");
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
                printf("\n\Listado\n\n");
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
