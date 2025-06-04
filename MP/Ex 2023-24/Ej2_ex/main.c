#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
    char **colores;
    int NumeroColores;
}tRegSari;

void insertarColor(tRegSari *sari, char *color);
void liberarMemoria(tRegSari *sari);

int main()
{
    setlocale(LC_ALL, "spanish");
    tRegSari sari;
    sari.colores = NULL;
    sari.NumeroColores = 0;

    char liberar, color[20], r;

    insertarColor(&sari, "rojo");
    insertarColor(&sari, "verde");
    insertarColor(&sari, "azul");
    insertarColor(&sari, "rojo");

    printf("\n\n\tColores del sari: ");
    for(int i =0; i < sari.NumeroColores; i++){
        printf("%s ", sari.colores[i]);
    }

    do{
        printf("\n\n\n\t¿Desea introducir otro color? (S/N):");
        fflush(stdin);
        scanf("%c", &r);
        if(r == 's' || r == 'S'){
            printf("\n\tIntroduzca el color que desea introducir: ");
            fflush(stdin);
            fgets(color, sizeof(color), stdin);
            color[strcspn(color, "\n")] = '\0';

            insertarColor(&sari, color);
            printf("\n\n\n\tColores del sari: ");
            for(int i =0; i < sari.NumeroColores; i++){
                printf("%s ", sari.colores[i]);
            }
        }
    }while(r == 's' || r == 'S');

    fflush(stdin);
    printf("\n\n\t¿Desea liberar la memoria? (S/N):");
    scanf("%c", &liberar);

    if(liberar == 'S' || liberar == 's'){
        liberarMemoria(&sari);
        printf("\n\tMemoria liberada.");
    }

    printf("\n\n");
    system("pause");

    return 0;
}

void insertarColor(tRegSari *sari, char *color){
    for(int i=0; i < sari->NumeroColores; i++){
        if(strcmp(sari->colores[i], color) == 0){
            printf("\n\n\tEl color '%s' ya está añadido en el Sari.", color);
            return;
        }
    }

    char **nuevaLista = realloc(sari->colores, (sari->NumeroColores+1)*sizeof(char *));
    if(nuevaLista == NULL){
        printf("\n\tERROR: Error al asignar la memoria\n");
        system("pause");
        return;
    }

    sari->colores = nuevaLista;
    sari->colores[sari->NumeroColores] = malloc((strlen(color)+1)*sizeof(char));

    if(sari->colores == NULL){
        printf("\n\tERROR: Error al asignar la memoria\n");
        system("pause");
        return;
    }

    strcpy(sari->colores[sari->NumeroColores], color);
    sari->NumeroColores++;
}

void liberarMemoria(tRegSari *sari){
    for(int i = 0; i < sari->NumeroColores; i++){
        free(sari->colores[i]);
    }

    free(sari->colores);
}
