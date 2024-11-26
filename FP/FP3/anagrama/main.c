#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************
    subPrograma: anagrama
    Función: recoge 2 palabras y comprueba si son anagramas
             devolviendo si lo son o no por pantalla.
***********************************************************/

//Función para comprobar si dos palabras son anagramas
int anagramas(char word1[], char word2[]) {
    int conteo1[256] = {0};
    int conteo2[256] = {0};

    for (int i = 0; word1[i]; i++) {
        conteo1[(unsigned char)word1[i]]++;
    }
    for (int i = 0; word2[i]; i++) {
        conteo2[(unsigned char)word2[i]]++;
    }

    // Comparar los contadores de caracteres
    for (int i = 0; i < 256; i++) {
        if (conteo1[i] != conteo2[i]) {
            return 0; // No son anagramas si los contadores no coinciden
        }
    }
    return 1;
}

int main()
{
    char word1[50];
    char word2[50];
    int long1, long2, i, e, j;

    //Hacer que si no tienen la misma longitud o si es la misma palabra
    //vuelva a pedir introducirlas.
    do{
        //Pide la primera palabra y quita el salto de línea
        printf("Introduce la primera palabra: ");
        fgets(word1, sizeof(word1), stdin);
        word1[strcspn(word1, "\n")] = '\0';

        //Pide la segunda palabra y quita el salto de línea
        printf("Introduce la segunda palabra: ");
        fgets(word2, sizeof(word2), stdin);
        word2[strcspn(word2, "\n")] = '\0';

        //Calcula la longitud de cada palabra
        long1 = strlen(word1);
        long2 = strlen(word2);

        if (long1 != long2){
            printf("Las palabras tienen que tener la misma longitud.\n");
        }
    }while(long1 != long2);

    //Comprueba si las dos palabras son iguales
    j = 0;
    for (i=0; i < long1; i++){
        if ((word1[i] != "\0") && (word2[i] != "\0") && (word1[i]==word2[i])){
            j = j+1;
        }
    }

    if (j == long1){
        printf("Dos palabras iguales no son anagramas");
    }

    //Comprueba si las palabras son anagramas
    //Las palabras ya son de la misma longitud y no son iguales
    if (anagramas(word1, word2)){
        printf("Son anagramas");
    } else{
        printf("No son anagramas");
    }
    return 0;
}
