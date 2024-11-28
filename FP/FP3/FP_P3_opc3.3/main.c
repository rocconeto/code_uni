#include <stdio.h>
#include <stdlib.h>

int main()
{
    fflush(stdin);
    //Declaramos variables
    char c1[50];
    int i, longitud;

    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tInvertir Cadena Caracteres\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Solicita la palabra al usuraio y la pasa a mayúsculas
    printf("\n\tCadena: ");
    fgets(c1, sizeof(c1), stdin);
    c1[strcspn(c1, "\n")] = '\0';

    longitud = strlen(c1);
    //Invierte la cadena
    printf("\n\tCadena invertida: ");
    for (i= longitud - 1; i >= 0; i--){
        printf("%c", c1[i]);
    }
}
