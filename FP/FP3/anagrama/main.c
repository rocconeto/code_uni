#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************
    Programa: anagrama
    Función: recoge 2 palabras y comprueba si son anagramas
             devolviendo si lo son o no por pantalla.
***********************************************************/

int main()
{
    char word1[50], word2[50];
    int stop, i, e;

    //Hacer que si no tienen la misma longitud o si es la misma palabra
    //vuelva a pedir introducirlas.
    printf("\nIntroduce la palabra 1: ");
    fgets(word1, sizeof(word1), stdin);

    printf("\nIntroduce la palabra 2: ");
    fgets(word2, sizeof(word2), stdin);

    for (int i = 0; i <= sizeof(word1); i++) {

    }

    return 0;
}
