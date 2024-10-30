/********************************************************
Programa:           validacion_de_rango.c
Tarea que realiza:  Pide al usuario dos numeros enteros
                    para estipular un rango y el programa
                    validara que sea correcto.

Autores:            Daniel Atanasov y Raul Sanz
Fecha:              23/10/2024
********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    //Definimos las variables
    int rg1, rg2, i;
    setlocale(LC_ALL, "spanish");

    //Pide los valores del rango
    printf("--------------------------------------------------------------------------\n");
    printf("\n\tPETICIÓN MÍNIMO Y MÁXIMO DEL RANGO\n");
    printf("\n--------------------------------------------------------------------------\n");
    do{
        printf("\tIntroduce el numero minimo del rango: ");
        scanf("%d", &rg1);
        if (rg1<0) {
            printf("\tEl numero minimo del rango no puede ser menor que 0\n");
        };
    } while (rg1<0);
    do{
        printf("\tIntroduce el numero maximo del rango: ");
        scanf("%d", &rg2);
        if (rg2<=rg1) {
            printf("\tError: el numero minimo debe ser menor que el maximo\n\n");
        }
    } while (rg2<=rg1);

    system("pause");
    system("cls");

    //Validacion de numeros dentro del rango
    printf("--------------------------------------------------------------------------\n");
    printf("\n\tPETICIÓN: VALIDAR NÚMERO DENTRO DEL RANGO [%d-%d]\n", rg1, rg2);
    printf("\n--------------------------------------------------------------------------\n");
    printf("\n\tIntroduzca cuantos números quiere probar si están en el rango: ");
    scanf("%d", &i);
    return 0;
}
