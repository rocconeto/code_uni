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

    int opt, lado, alt, rombo;
    int i, e;

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
                char dbj[100] = "*";
                for (e=0; e<lado; e++) {
                    printf("\t\t");
                    for (i=0; i<lado; i++) {
                        printf("%s", dbj);
                    }
                    printf("\n");
                }

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

                char dbj_tr[100] = "*";
                char addchar[10] = "**";
                for (i=0; i<alt; i++) {
                    printf("\t\t");
                    for (e=0; e<alt-i; e++) {
                        printf(" ");
                    };
                    printf("%s\n", dbj_tr);
                    strcat(dbj_tr, addchar);
                }


                break;

            case 3:
                printf("\n2. DIBUJAR UN ROMBO\n");
                printf("\n************************************************************************\n");
                do{
                    printf("\n\tIntroduzca un número impar y positivo igual o mayor que 3: ");
                    scanf("%d", &rombo);
                    if (rombo<3){
                        printf("\tEl número debe ser mayor o igual a 3.\n");
                    } else if (rombo % 2 == 0); {
                        printf("\tEl número debe ser impar");
                    }
                }while(rombo<=3 || rombo/2 == 0);

                 int mitad = rombo / 2;

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


                break;
        };
    } while (opt != 4);
}
