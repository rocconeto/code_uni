#include "main.h"
#include "informesEconomicos.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/****************************************************************************/
/*Subprograma:              Menú de los informes económicos                 */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    ---                                             */
/*Parámetros de salida:     ---                                             */
/*Prerrequisitos:           ---                                             */
/*Objetivo:                 Presenta por pantalla el menú del subprograma   */
/*                          con todas las opciones disponibles              */
/****************************************************************************/
void menu_infEco(tRegCliente clientes[], int *cont_clientes, tRegHabitacion habitaciones[], int *cont_hab){
    int opc;
    do{
        printf("------------------------------------------------------\n");
        printf("\n\t\tINFORMES ECONÓMICOS\n");
        printf("\n------------------------------------------------------\n");
        printf("\n\t1.- Informe Mensual por Categoría de Cliente\n");
        printf("\n\t2.- Informe Mensual de Ocuapación de Habitaciones\n");
        printf("\n\t3.- Informe Mensual de Ingresos por Reservas\n");
        printf("\n\t0.- Volver al menú principal\n");

        printf("\n\tSelecciona una opción: ");
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
/*Subprograma:              Informe Mensual Categoría Cliente                                    */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Array clientes y contador de clientes                                */
/*Parámetros de salida:     ---                                                                  */
/*Prerrequisitos:           ---                                                                  */
/*Objetivo:                 Mostrar por pantalla la cantidad de clientes de cada tipo que hay    */
/*                          registrados en el array y el importe registrado para cada tipo       */
/*************************************************************************************************/
void infCatCliente(tRegCliente clientes[], int cont_clientes){
    printf("\n\n\t\tINFORME MENSUAL (Por Categoría de Clientes)\n");
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
    printf("\n\t** Número de clientes:");
    printf("\n\tNormales:\t%d", normales);
    printf("\n\tVIP:\t\t%d", vip);
    printf("\n\tEmpresas:\t%d", empresas);
    printf("\n\tTotal:\t%d clientes\n", cont_clientes);

    //Calcula los importes registrados y los muestra por pantalla
    normales = normales * precio_normal;
    vip = vip * precio_vip;
    empresas = empresas * precio_empresas;
    total = normales + vip + empresas;

    //Como el programa no me muestra el símbolo € lo he cambiado por "euros"
    printf("\n\t** Importes Registrados:");
    printf("\n\tNormales:\t%d euros", normales);
    printf("\n\tVIP:\t\t%d euros", vip);
    printf("\n\tEmpresas:\t%d euros", empresas);
    printf("\n\tImporte Total: %d euros\n\n", total);
}

/*************************************************************************************************/
/*Subprograma:              Informe Mensual Categoría Cliente                                    */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Array clientes y contador de clientes                                */
/*Parámetros de salida:     ---                                                                  */
/*Prerrequisitos:           ---                                                                  */
/*Objetivo:                 Mostrar por pantalla la cantidad de clientes de cada tipo que hay    */
/*                          registrados en el array y el importe registrado para cada tipo       */
/*************************************************************************************************/
void infOcupHab(tRegCliente clientes[], int cont_clientes, int cont_hab){
    printf("\n\n\t\tINFORME MENSUAL (Ocupación de Habitaciones)\n");
    printf("\n--------------------------------------------------------------------\n");

    //Busca cuántas habitaciones están ocupadas
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

    //Muestra los resultados de ocupación de las habitación
    printf("\n\tTotal de habitaciones: %d\n", cont_hab);
    printf("\n\tOcupadas: %d\n", ocupadas);
    printf("\n\tLibres: %d\n", libres);
    printf("\n\n\tPorcentaje de ocupación: %.1f %%\n\n", porcentaje);
}

/*************************************************************************************************/
/*Subprograma:              Informe Mensual Categoría Cliente                                    */
/*Tipo:                     Procedimiento (función tipo void)                                    */
/*Parámetros de entrada:    Array clientes y contador de clientes                                */
/*Parámetros de salida:     ---                                                                  */
/*Prerrequisitos:           ---                                                                  */
/*Objetivo:                 Mostrar por pantalla la cantidad de clientes de cada tipo que hay    */
/*                          registrados en el array y el importe registrado para cada tipo       */
/*************************************************************************************************/
void infIngrReservas(tRegCliente clientes[], int cont_clientes, tRegHabitacion habitaciones[], int cont_hab){
    printf("\n\n\t\tINFORME MENSUAL (Ingresos por Reservas)\n");
    printf("\n--------------------------------------------------------------------\n");

    //Busca las habitaciones que están ocupadas y luego busca el precio de la habitación para sumarlo al total
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
    printf("\n\tNúmero total de reservas: %d\n", ocupadas);
    printf("\n\tIngreso total: %.2f\n\n", total);
}
