#include <stdio.h>
#include <stdlib.h>

int main()
{
    int tabla1[5];
    int tabla2[5];
    int i, num, e, j;

    //Pide los numeros
    for (i=0; i<5; i++){
        j = i + 1;
        printf("Introduce el número %d: ", j);
        scanf("%d", num);
        tabla1[i] = num;
    }
    for (i=0; i<5; i++){
        printf("%d, ", tabla1[i]);
    }

}
