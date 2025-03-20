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

#define MAX_CLIENTES = 100

typedef struct{
    int dni;
    char nombre[50];
    int tipo;
    char reservas[7];
}Clientes

void menu_princ();
void gest_clientes();
void gest_hab();
void gest_reservas();

int main()
{
    setlocale(LC_ALL, "spanish");
    printf("\n\t�Bienvenido a la aplicaci�n GEST_HOTEL!\n");
    printf("\n--------------------------------------------------------\n\n");
    system("pause");
    system("cls");

    //Cargamos los datos de los ficheros
    int cont_clientes = 0;
    FILE *fich;
    fich = fopen("clientes.dat", "r");
    if(fich == NULL){
        printf("Error al abrir el fichero");
        exit(1);
    }else{
        while (fscanf(fich, "%d%s%d%s", &clientes[cont_clientes].dni, &clientes[cont_clientes].nombre, &clientes[cont_clientes].tipo, &clientes[cont_clientes].reservas) == 4){
            cont_clientes ++;
            if(cont_clientes >= MAX_CLIENTES){
                break;
            }
        }
        fclose(clientes);
    }

    menu_princ();
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
void menu_princ(){
    int opc;
    do{
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
                printf("\n\tGuardando los datos...\n");
                printf("\n--------------------------------------------------------\n\n");

                //Guarda los cambios realizados en los registros
                FILE *fich
                fich = fopen("clientes.dat", "w");
                if(fich == NULL){
                    printf("Error al guardar los clientes.");
                    return 1;
                }
                for(int i=0; i<cont_clientes; i++){
                    fprintf(fich, "\n\t%d%s%d%s\n", &clientes[i].dni, &clientes[i].nombre, &clientes[i].tipo, &clientes[i].reservas);
                }

                fclose(fich);
                printf("\n\tDatos guardados correctamente.\n");
                printf("�Gracias por usar nuestro programa!");

                break;
        }
    }while(opc != 0);
}

/********************************************************************************************/
/*Subprograma:              Gesti�n clientes                                                */
/*Tipo:                     Procedimiento (funci�n tipo void)                               */
/*Par�metros de entrada:    ---                                                             */
/*Par�metros de salida:     ---                                                             */
/*Prerrequisitos:           ---                                                             */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con los clientes  */
/********************************************************************************************/
void gest_clientes(){
    void submenu_cl();

    submenu_cl();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Men� del subprograma                            */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/****************************************************************************/
void submenu_cl(){
    int opc;
    do{
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
/*Subprograma:              Gesti�n habitaciones                                                */
/*Tipo:                     Procedimiento (funci�n tipo void)                                   */
/*Par�metros de entrada:    ---                                                                 */
/*Par�metros de salida:     ---                                                                 */
/*Prerrequisitos:           ---                                                                 */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con las habitaciones  */
/************************************************************************************************/
void gest_hab(){
    void submenu_hab();

    submenu_hab();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Men� del subprograma                            */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/****************************************************************************/
void submenu_hab(){
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

/********************************************************************************************/
/*Subprograma:              Gesti�n reservas                                                */
/*Tipo:                     Procedimiento (funci�n tipo void)                               */
/*Par�metros de entrada:    ---                                                             */
/*Par�metros de salida:     ---                                                             */
/*Prerrequisitos:           ---                                                             */
/*Objetivo:                 Se encarga de todas las opciones relacionadas con las reservas  */
/********************************************************************************************/
void gest_reservas(){
    void submenu_res();

    submenu_res();

    system("cls");
}

/****************************************************************************/
/*Subprograma:              Men� del subprograma                            */
/*Tipo:                     Procedimiento (funci�n tipo void)               */
/*Par�metros de entrada:    ---                                             */
/*Par�metros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Muestra por pantalla el men� del subprograma    */
/****************************************************************************/
void submenu_res(){
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
