/********************************************************
Programa:           convertir_unidades.c
Tarea que realiza:  Convierte las unidades de la
                    elección del usuario, le pide
                    introducir cantidades y devuelve
                    el equivalente en otras unidades.

Autores:            Daniel Atanasov y Raúl Sanz
Fecha:              09/10/2024
********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("cls");

    int chosen;
    printf("Bienvenido/a a este programa de conversión de unidades de medida\n");
    printf("1. Convertir km a mi\n2. Convertir litros a galones\n3. Convertir kg a libras\n0. Para salir\n");
    scanf("%d", &chosen);

    if (chosen == 1) {
        float km;
        float mi;
        printf("\nIntroduce una cantidad de km para pasarla a millas: ");
        scanf("%f", &km);
        mi = km * 0.621;
        printf("%f km corresponden a %f mi", km, mi);

    } else if (chosen == 2) {
        float lt;
        float gal;
        printf("\nIntroduce una cantidad de litros para pasarla a galones: ");
        scanf("%f", &lt);
        gal = lt * 0.264;
        printf("%f litros corresponden a %f galones", lt, gal);

    } else if (chosen == 3) {
        float kg;
        float lb;
        printf("\nIntroduce una cantidad de kg para pasarla a lb: ");
        scanf("%f", &kg);
        lb = kg * 2.204;
        printf("%f kg corresponden a %f lb", kg, lb);


    } else if (chosen == 0) {
        printf("Gracias por usar esta aplicación!");
        system("exit");
    };

    return 0;
}
