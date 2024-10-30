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

int main()
{

    int opt, lado, alt;

    printf("--------------------------------------------------------------------------\n");
    printf("\n\tBIENVENIDOS A NUESTRA APLICACION DE OPCIONES!\n");
    printf("\n--------------------------------------------------------------------------\n");
    printf("Pulse cualquier tecla para continuar...\n\n\n");

    do {
        system("pause");
        system("cls");

        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tMENU DE OPCIONES\n");
        printf("\n--------------------------------------------------------------------------\n");
        printf("1. Dibujar un cuadrado\n");
        printf("2. Dibujar un triangulo equilatero\n");
        printf("3. Dibujar un rombo\n");
        printf("4. Salir\n");


        do{
            printf("\nSeleccione una opción: ");
            scanf("%d", &opt);
        }while (opt <1 || opt>=5);

        printf("\n\nPulse cualquier tecla para continuar...\n");
        system("pause");
        system("cls");

        switch(opt){
            case 1:
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
                int i, e;
                char dbj[100] = "*";
                for (e=0; e<lado; e++) {
                    printf("\t\t\t");
                    for (i=0; i<lado; i++) {
                        printf("%s", dbj);
                    }
                    printf("\n");
                }
                //int i;
                //char dbj[100] = " ";
                //char addchar[2];
                //addchar[0] = "*";
                //addchar[1] = 0;

                //for (i=0; i<lado; i++) {
                //    strcat (dbj, addchar);
                //};
                //for (i=0; i<lado; i++) {
                //    printf("%s\n", dbj);
                //}

                break;
            case 2:
                printf("\n2. DIBUJAR UN TRIANGULO\n");
                printf("\n************************************************************************\n");
                do{
                    printf("\n\tIntroduzca la altura del triangulo equilatero: ");
                    scanf("%d", &alt);
                    if (alt<=1){
                        printf("\tLa altura debe ser mayor o igual a 2.\n");
                    }
                }while(alt<=1);
                //Tienes que hacer los dibujos
                break;
        };
    } while (opt != 4);
}
