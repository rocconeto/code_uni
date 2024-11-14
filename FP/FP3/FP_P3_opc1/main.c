#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int leerCateto(void);
void calcularHipotenusa(int c1, int c2, int *h);
void calcularArea(int c1, int c2, float *A);
void calcularPerimetro(int c1, int c2, int h, int *P);
void mostrarResultado(int c1, int c2, int h, float A, int P);

int main()
{
    int c1, c2, h, P;
    float A;
    setlocale(LC_ALL, "spanish");
    c1 = leerCateto();
    c2 = leerCateto();
    calcularHipotenusa(c1, c2, &h);
    calcularArea(c1, c2, &A);
    calcularPerimetro(c1, c2, h, &P);
    mostrarResultado(c1, c2, h, A, P);

    return 0;
}

int leerCateto(void){
    int c;
    do{
        printf("Introduce el valor del cateto: ");
        scanf("%d", &c);
    }while(c<=0);
}
void calcularHipotenusa(int c1, int c2, int *h){
    *h = sqrt((c1*c1)+(c2*c2));
}

void calcularArea(int c1, int c2, float *A){
    *A = (c1*c2)/2;
}

void calcularPerimetro(int c1, int c2, int h, int *P){
    *P = h + c1 + c2;
}

void mostrarResultado(int c1, int c2, int h, float A, int P){
    printf("\nEl valor de los catetos es: %d y %d.", c1, c2);
    printf("\nEl valor de la hipotenusa es: %d.", h);
    printf("\nEl área del triángulo es: %.2f.", A);
    printf("\nEl perímetro del triángulo es de: %d.", P);
}
