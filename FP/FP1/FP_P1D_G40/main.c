/***********++++++++++++++++++++++*******************************
Programa:           distancia_coordenadas.c
Tarea que realiza:  Tras introducir las coordenadas de dos
                    puntos y, tras validar los datos, calcula
                    la distancia entre ellos y la muestra por 
                    pantalla.
Autores:            Daniel Atanasov y Ra�l Sanz
Fecha:              9/10/2024
*****************************************+++++++++++++++++++++++*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    //Definimos las variables
    int x1, x2, y1, y2;
    float dist;

    //Pide las coordenadas de los puntos
    printf("Introduce las coordenadas del primer punto:\n");
    do{
        printf("x1: ");
        scanf("%d", &x1);
    }while(x1<0 || x1 >= 20);
    do{
        printf("y1: ");
        scanf("%d", &y1);
    }while(y1<0 || y1 >= 20);

    do{
        printf("Introduce las coordenadas del segundo punto:\n");
        printf("x2: ");
        scanf("%d", &x2);
    }while(x2<0 || x2 >= 20);
    do{
        printf("y2: ");
        scanf("%d", &y2);
    }while(y2<0 || y2 >= 20);

    system("pause");
    system("cls");

    //Calcula la distancia si los datos son mayores que 0
    dist = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    printf("La distancia entre los dos puntos es de: %.2f\n", dist);

    return 0;
}
