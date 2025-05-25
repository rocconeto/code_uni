/*  Asigantura: Metodología de la programación Curso: 1
    Tarea que realiza el programa: Ejercicios recursivos e iterativos con cadenas de caracteres
    Alumno 1: Atanasov Angelov, Daniel
    Alumno 2: Sanz Tomé, Raúl
    Grupo de laboratorio: 30
    Fecha: 15/05/2025 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "cadenas.h"

int main()
{
    setlocale(LC_ALL, "spanish");
    int opc;
    char V1[30] = "murcielago", V2[30] = "ordenador", Vocals[30], V3[60], duplicadas[30], ordenada[60];

    do {
        int indice = 0, vocales = 0; //Para evitar errores, cada vez que se muestra el menú se reestablecen sus valores
        printf("-------------------------------------------------------------------------------\n");
        printf("\n\t\tMENÚ DEL PROGRAMA\n");
        printf("\n-------------------------------------------------------------------------------\n");
        printf("\n\t1.- Contar vocales en V1 (Recursivo)\n");
        printf("\n\t2.- Eliminar todas las consonantes de V2 (Recursivo)\n");
        printf("\n\t3.- Intercalar letras de V1 y V2 en un nuevo string V3 (Recursivo)\n");
        printf("\n\t4.- Duplicar cada letra de V1 (Recursivo)\n");
        printf("\n\t5.- Convertir mayúsculas de V1 y V2 a minúsculas (versión iterativa)\n");
        printf("\n\t6.- Convertir mayúsculas de V1 y V2 a minúsculas (versión recursiva)\n");
        printf("\n\t7.- Ordenar alfabéticamente la cadena V1+V2 (Recursivo)\n");
        printf("\n\t0.- Salir\n");

        printf("\n\tSelecciona una opción: ");
        scanf("%d", &opc);
        getchar();

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                contarVocales(V1, &vocales);
                printf("\n\tV1: %s\n", V1);
                printf("\n\tNúmero de vocales en V1: %d\n\n", vocales);
                system("pause");
                system("cls");
                break;
            case 2:
                eliminarConsonantes(V2, Vocals, &indice);
                printf("\n\tV2 original: %s\n", V2);
                printf("\n\tV2 sin consonantes: %s\n\n", Vocals);
                system("pause");
                system("cls");
                break;
            case 3:
                intercalarCadenas(V1, V2, V3);
                printf("\n\tV1: %s\n", V1);
                printf("\n\tV2: %s\n", V2);
                printf("\n\tCadena intercalada V3: %s\n\n", V3);
                system("pause");
                system("cls");
                break;
            case 4:
                duplicarLetras(V1, duplicadas);
                printf("\n\tV1: %s\n", V1);
                printf("\n\tV1 duplicado: %s\n", duplicadas);
                system("pause");
                system("cls");
                break;
            case 5:
                printf("\n\tV1: %s\n", V1);
                printf("\n\tV2: %s\n", V2);
                aMinusculas_Iterativo(V1, V2);
                printf("\n\tV1 en minusculas: %s\n", V1);
                printf("\n\tV2 en minusculas: %s\n\n", V2);
                system("pause");
                system("cls");
                break;
            case 6:
                printf("\n\tV1: %s\n", V1);
                printf("\n\tV2: %s\n", V2);
                aMinusculas_Recursivo(V1, V2);
                printf("\n\tV1 en minusculas: %s\n", V1);
                printf("\n\tV2 en minusculas: %s\n\n", V2);
                system("pause");
                system("cls");
                break;
            case 7:
                ordenarCadena(V1, V2, ordenada);
                printf("\n\tV1: %s\n", V1);
                printf("\n\tV2: %s\n", V2);
                printf("\n\tCadena combinada ordenada: %s\n\n", ordenada);
                system("pause");
                system("cls");
                break;
            case 0:
                printf("\n\t¡Gracias por usar nuestro programa!\n\n");
                break;
        }
    }while(opc != 0);

    return 0;
}
