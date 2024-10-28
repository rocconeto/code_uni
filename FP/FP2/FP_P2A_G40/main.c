/********************************************************
Programa:           peticion_datos.c
Tarea que realiza:  Pide dos numeros y calcula varias relaciones entre ambos.

Autores:            Daniel Atanasov y Raul Sanz
Fecha:              23/10/2024
********************************************************/

#include <stdio.h>
#include <locale.h>

int main()
{
    int x, y;
    int suma, resta, producto; //almacenan los resultados de los cálculos
    int i, sumaTotal;

    setlocale(LC_ALL, "spanish");

    //Pedimos los números al usuario
    printf("\n\t\t PETICIÓN DE DATOS ");
    printf("\n\t\t ================== \n\n");
    printf("\n\t\t Introduzca dos números enteros: ");
    scanf("%d %d", &x, &y);

    //Realizamos cálculos
    suma = x + y;
    resta = x - y;
    producto = x * y;

    //Suma los primeros x números enteros
    sumaTotal = 0;
    for (i = 1; i<= x; i++)
        sumaTotal = sumaTotal + i;

    //Mostramos resultados en pantalla
    printf("\n\t\t RESULTADOS ");
    printf("\n\t\t =========== ");

    printf("\n\t\t La suma es %d", suma);
    printf("\n\t\t La resta es %d", resta);
    printf("\n\t\t El producto es %d", producto);
    printf("\n\t\t La suma de los %d primeros números naturales es: %d", x, sumaTotal);

    printf("\n\n\t\t Pulse <Intro> para finalizar... \n\n");
    getchar();
}
