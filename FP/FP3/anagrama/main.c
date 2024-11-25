#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************
    subPrograma: anagrama
    Función: recoge 2 palabras y comprueba si son anagramas
             devolviendo si lo son o no por pantalla.
***********************************************************/

int main()
{
    char word1[50], word2[50];
    int stop, i, e, j, k;

    //Hacer que si no tienen la misma longitud o si es la misma palabra
    //vuelva a pedir introducirlas.
    do{
        printf("\nIntroduce la palabra 1: ");
        fgets(word1, sizeof(word1), stdin);

        word1[strcspn(word1, "\n")] = '\0';

        printf("\nIntroduce la palabra 2: ");
        fgets(word2, sizeof(word2), stdin);

        word2[strcspn(word2, "\n")] = '\0';

        printf("%s, %s", word1, word2);

        for (i = 0; i <= sizeof(word1); i++) {
            e = word1[i];
            printf("\%d", e);
            if (e = '\0'){
                break;
            }
        }
        printf("%d", i);

        for (j = 0; j <= sizeof(word2); j++) {
            k = word2[j];
            printf("\%d", k);
            if (k = '\0'){
                break;
            }
        }
        printf("%d", j);
    }while(i != j);

    return 0;
}
