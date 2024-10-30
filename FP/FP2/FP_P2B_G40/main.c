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

int main()
{
    //Definimos las variables
    int rg1, rg2;

    //Pide los valores del rango
    do{
        printf("Introduce el numero minimo del rango: ");
        scanf("%d", &rg1);
        if (rg1<0) {
            printf("El numero minimo del rango no puede ser menor que 0\n");
        };
    } while (rg1<0);
    do{
        printf("Introduce el numero maximo del rango: ");
        scanf("%d", &rg2);
        if (rg2<=rg1) {
            printf("El numero maximo del rango no puede ser menor/igual que el minimo");
        };
    } while (rg2<=rg1);

    //Test
    printf("rg1 es %d\n", rg1);
    printf("rg2 es %d", rg2);



    //
    return 0;
}
