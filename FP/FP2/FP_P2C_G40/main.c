/********************************************************
Programa:           menuOpciones.c
Tarea que realiza:  Muestra un mensaje de bienvenida y después
                    da distintas opciones: dibujar un triangulo,
                    cuadrado o rombo.
Autores:            Daniel Atanasov y Ra�l Sanz
Fecha:              23/10/2024
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void cuadrado();
void triangulo();
void rombo();

int main()
{

    int opt;
    setlocale(LC_ALL, "spanish");

    printf("--------------------------------------------------------------------------\n");
    printf("\n\tBIENVENIDOS A NUESTRA APLICACION DE OPCIONES!\n");
    printf("\n--------------------------------------------------------------------------\n");

    do {
        system("pause");
        system("cls");

        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tMENU DE OPCIONES\n");
        printf("\n--------------------------------------------------------------------------\n");
        printf("\t1. Dibujar un cuadrado\n");
        printf("\t2. Dibujar un triangulo equilatero\n");
        printf("\t3. Dibujar un rombo\n");
        printf("\t4. Salir\n");


        do{
            printf("\n\tSeleccione una opcion: ");
            scanf("%d", &opt);
        }while (opt <1 || opt>=5);

        system("pause");
        system("cls");

        switch(opt){
            case 1:
                cuadrado();
                break;
            case 2:
                triangulo();
                break;
            case 3:
                rombo();
                break;
            case 4:
                printf("\tSaliendo del programa...\n");
                break;
        }
    } while (opt != 4);

    return 0;
}

void cuadrado(){
    int lado, e, i;
    printf("\n1. DIBUJAR UN CUADRADO\n");
    printf("\n************************************************************************\n");
    do{
        printf("\n\tIntroduzca el tamaño del lado del cuadrado: ");
        scanf("%d", &lado);
        if (lado<0 || lado == 0){
            printf("\tEl tamaño debe ser un numero positivo o distinto de 0\n");
        }
    }while(lado <0 || lado == 0);

    //Realizamos el dibujo
    char dbj[100] = "*";
    for (e=0; e<lado; e++) {
        printf("\t\t");
        for (i=0; i<lado; i++) {
            printf("%s", dbj);
        }
        printf("\n");
        }
}

void triangulo(){
    int alt, i, e;
    printf("\n2. DIBUJAR UN TRIANGULO\n");
    printf("\n************************************************************************\n");
    do{
        printf("\n\tIntroduzca la altura del triangulo equilatero: ");
        scanf("%d", &alt);
        if (alt<=1){
            printf("\tLa altura debe ser mayor o igual a 2.\n");
        }
    }while(alt<=1);

    char dbj_tr[100] = "*";
    char addchar[10] = "**";
    for (i=0; i<alt; i++) {
        printf("\t\t");
        for (e=0; e<alt-i; e++) {
            printf(" ");
        }
        printf("%s\n", dbj_tr);
        strcat(dbj_tr, addchar);
    }
}

void rombo(){
    int rmb, i, e;
    printf("\n2. DIBUJAR UN ROMBO\n");
    printf("\n************************************************************************\n");
    do{
        printf("\n\tIntroduzca un número impar, positivo y mayor que 3: ");
        scanf("%d", &rmb);
        if (rmb<3){
            printf("\tEl numero debe ser mayor o igual a 3.\n");
        } else if (rmb % 2 == 0) {
            printf("\tEl numero debe ser impar");
        }
    }while(rmb<=3 || rmb % 2 == 0);

    int mitad = rmb / 2;

    printf("\n\n");

    // Parte superior del rombo
    for (i = 0; i <= mitad; i++) {
        // Espacios a la izquierda
        printf("\t\t");
        for (e = 0; e < mitad - i; e++) {
            printf(" ");
        }
        // Asteriscos
        for (e = 0; e < 2 * i + 1; e++) {
            printf("*");
        }
        printf("\n");
    }

    // Parte inferior del rombo
    for (i = mitad - 1; i >= 0; i--) {
        // Espacios a la izquierda
        printf("\t\t");
        for (e = 0; e < mitad - i; e++) {
            printf(" ");
        }
        // Asteriscos
        for (e = 0; e < 2 * i + 1; e++) {
            printf("*");
        }
        printf("\n");
    }
}
