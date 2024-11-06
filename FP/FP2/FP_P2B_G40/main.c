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
    int rg1, rg2, i, n, num, p, np, cant, summedia, iteraciones;
    float media;
    setlocale(LC_ALL, "spanish");

    //Pide los valores del rango
    printf("--------------------------------------------------------------------------\n");
    printf("\n\tPETICI�N M�NIMO Y M�XIMO DEL RANGO\n");
    printf("\n--------------------------------------------------------------------------\n");
    do{
        printf("\n\tIntroduce el numero minimo del rango: ");
        scanf("%d", &rg1);
        if (rg1<0) {
            printf("\n\tEl numero minimo del rango no puede ser menor que 0\n");
        };
    } while (rg1<0);
    do{
        printf("\n\tIntroduce el numero maximo del rango: ");
        scanf("%d", &rg2);
        if (rg2<=rg1) {
            printf("\n\tError: el numero maximo debe ser mayor que el minimo\n\n");
        }
    } while (rg2<=rg1);

    printf("\n\n");
    system("pause");
    system("cls");

    //Validacion de numeros dentro del rango
    printf("--------------------------------------------------------------------------\n");
    printf("\n\tPETICI�N: VALIDAR N�MERO DENTRO DEL RANGO [%d-%d]\n", rg1, rg2);
    printf("\n--------------------------------------------------------------------------\n");
    printf("\n\tIntroduzca cuantos n�meros quiere probar si est�n en el rango: ");
    scanf("%d", &n);

    //Ejecuta tantas veces como n�meros se quieren comprobar
    media = 0;
    summedia = 0;
    iteraciones = 0;
    for (i=0; i<n; i++){
        printf("\n\n\tIntroduce el n�mero a validar: ");
        scanf("%d", &num);
        if (num>rg1 && num<rg2){
            printf("\n\tEl n�mero est� dentro del rango\n");
            //Calcula los numeros pares menores que el numero dado que estan dentro de la lista
            p = rg1%2;
            if (p==0){ //Comprueba si el primer numero es par para empezar la lista
                np = rg1+2;
                cant = 0;
                printf("\n\tConjunto de pares inferiores a %d:[", num);
                for (np; np<num; np++){
                    if(np%2 == 0){
                        printf("%d,", np);
                        cant = cant + 1;
                    }
                }
                printf("]\n");
                printf("\n\tEl n�mero de pares en el rango inferiores a %d es: %d\n", num, cant);
            } else {
                np = rg1+1;
                cant = 0;
                printf("\n\tConjunto de pares inferiores a %d:[", num);
                for (np; np<num; np++){
                    if(np%2 == 0){
                        printf("%d,", np);
                        cant = cant + 1;
                    }
                }
                printf("]\n");
                printf("\n\tEl n�mero de pares en el rango inferiores a %d es: %d\n", num, cant);
            }
            summedia = summedia + num;
            iteraciones = iteraciones + 1;
        } else{
            printf("\n\tEl n�mero est� fuera del rango\n");
        }
    }
    media = summedia/iteraciones;
    printf("\n\n\tLa media de los n�meros dentro del rango es: %.2f\n", media);
    return 0;
}
