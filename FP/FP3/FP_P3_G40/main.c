/********************************************************
Programa:           subprogramas.c
Tarea que realiza:  Un menu principal que da acceso a
                    programas que a su vez contienen a
                    otros programas.
Autores:            Daniel Atanasov y Raul Sanz
Fecha:              13/11/2024
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void triangulo();
void pascal();
void caracteres();
void arrays();

int main(){

    int opt;
    setlocale(LC_ALL, "spanish");

    do {
        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tMENÚ PRINCIPAL\n");
        printf("\n--------------------------------------------------------------------------\n");
        printf("\t1. Cálculos sobre un triángulo\n");
        printf("\t2. Dibujar triángulo de Pascal\n");
        printf("\t3. Procesar cadena de caracteres\n");
        printf("\t4. Procesar arrays de números enteros\n");
        printf("\t0. Salir\n");


        do{
            printf("\n\tSeleccione una opción: ");
            scanf("%d", &opt);
        }while (opt <0 || opt >4);

        system("pause");
        system("cls");

        switch(opt){
            case 1:
                triangulo();
                break;
            case 2:
                pascal();
                break;
            case 3:
                caracteres();
                break;
            case 4:
                arrays();
                break;
            case 0:
                printf("\tSaliendo del programa...\n");
                break;
        }
    } while (opt != 0);

    return 0;
}

// SUBPROGRAMA TRIÁNGULO
void triangulo() {
    //Definimos los subprogramas de esta opción
    void leerCateto(int *c1, int *c2);
    void calcularHipotenusa(int c1, int c2, float *h);
    void calcularArea(int c1, int c2, float *A);
    void calcularPerimetro(int c1, int c2, float h, int *P);
    void mostrarResultado(int c1, int c2, float h, float A, int P);

    //Muestra el menú del subprograma
    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tCÁLCULOS SOBRE UN TRIANGULO");
    printf("\n--------------------------------------------------------------------------\n");

    //Definimos variables y llamamos a los subprogramas
    int c1, c2, P;
    float A, h;
    leerCateto(&c1, &c2);
    calcularHipotenusa(c1, c2, &h);
    calcularArea(c1, c2, &A);
    calcularPerimetro(c1, c2, h, &P);
    mostrarResultado(c1, c2, h, A, P);

    system("pause");
    system("cls");
}

//SUBPROGRAMAS DEL TRIÁNGULO
/***************************************
Subprograma: leerCateto
Tarea: Pide un número que será el valor del cateto.
Parámetros de S/: c1 (entero) y c2(entero)
***************************************/
void leerCateto(int *c1, int *c2){
    do{
        printf("\tIntroduce el valor del primer cateto: ");
        scanf("%d", c1);
    }while(c1<=0);
    do{
        printf("\tIntroduce el valor del segundo cateto: ");
        scanf("%d", c2);
    }while(c2<=0);
}

/*****************************************************
Subprograma:        calcularHipotenusa
Tarea:              Calcula y devuelve el valor de la
                    hipotenusa del triangulo
Parámetros de E/:   c1 (entero) y c2(entero)
Parámetros de S/:   h(real)
*****************************************************/
void calcularHipotenusa(int c1, int c2, float *h){
    *h = sqrt((c1*c1)+(c2*c2));
}

/*****************************************************
Subprograma:        calcularArea
Tarea:              Calcula y devuelve el valor del área
                    del triangulo
Parámetros de E/:   c1 (entero) y c2(entero)
Parámetros de S/:   A(real)
*****************************************************/
void calcularArea(int c1, int c2, float *A){
    *A = (c1*c2)/2;
}

/*****************************************************
Subprograma:        calcularPerimetro
Tarea:              Calcula y devuelve el valor del
                    perímetro del triangulo
Parámetros de E/:   c1 (entero), c2(entero) y h(real)
Parámetros de S/:   P(entero)
*****************************************************/
void calcularPerimetro(int c1, int c2, float h, int *P){
    *P = h + c1 + c2;
}

/*****************************************************
Subprograma:        mostrarResultados
Tarea:              Obtiene los datos de los otros subprogramas
                    y los muestra por pantalla
Parámetros de E/:   c1 (entero), c2(entero), h(real),
                    A(real) y P(entero)
*****************************************************/
void mostrarResultado(int c1, int c2, float h, float A, int P){
    printf("\n\tEl valor de los catetos es: %d y %d.", c1, c2);
    printf("\n\tEl valor de la hipotenusa es: %.2f.", h);
    printf("\n\tEl área del triángulo es: %.2f.", A);
    printf("\n\tEl perímetro del triángulo es de: %d.\n\n", P);
}

// SUBPROGRAMA TRIÁNGULO DE PASCAL
void pascal() {
    //Declaramos los subprogramas
    void pedirNumero(int *filas);
    void dibujarTrianguloPascal(int filas);

    //Muestra el menú del subprograma
    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tDIBUJAR TRIÁNGULO DE PASCAL");
    printf("\n--------------------------------------------------------------------------\n");


    int filas;
    pedirNumero(&filas);
    dibujarTrianguloPascal(filas);

    system("pause");
    system("cls");
}


// SUBPROGRAMAS DEL TRIÁNGULO DE PASCAL
/**********************************************************************
    Subprograma: Pedir Numero
    Tarea que realiza: Solicita al usuario un número entero mayor que 2
                       y será el número de filas del triángulo de Pascal.
    Parámetros de S/: filas(entero)
***********************************************************************/
void pedirNumero(int *filas) {
    printf("Introduce la cantidad de filas para el triángulo de Pascal: ");
    scanf("%d", filas);
}

/**********************************************************************
    Subprograma: Dibujar Triangulo de Pascal
    Tarea que realiza: Dibuja un triangulo de Pascal con el numero de filas
                       que haya introducido el usuario en el subprograma
                       pedirNumero()
    Parámetros de E/: filas(entero)
    ***********************************************************************/
void dibujarTrianguloPascal(int filas) {
    for (int i = 0; i < filas; i++) {
        int valor = 1;

        for (int j = 0; j < filas -i - 1; j++) {
            printf("   ");
        }

        for (int j = 0; j <= i; j++) {
            printf("%6d", valor);
            valor = valor * (i - j) / (j + 1);
        }
        printf("\n");
    }
    printf("\n\n");
}

void caracteres() {

}

void arrays(){

}


// SUBPROGRAMAS PARA PROCESAR CARACTERES
void anagramaCadenas() {
    /**********************************************************************
    Subprograma: Anagrama
    Tarea que realiza: Recibe dos palabras (string) y retorna si son o no
                       anagramas.

    ***********************************************************************/
}

void convertirMayuscConsonantes() {
    /**********************************************************************
    Subprograma: Convertir Mayusculas a Consonantes
    Tarea que realiza: Solicita al usuario introducir una palabra y se crea
                       una nueva cadena de caracteres formada por los de la
                       solicitada al usuario pero con las consonantes en
                       mayuscula.

    ***********************************************************************/
}

void crearCadenaInvertida() {
    /**********************************************************************
    Subprograma: Crear Cadena Invertida
    Tarea que realiza: A partir de una cadena que recibe como parámetro el
                       subprograma, crea una nueva cadena que contiene la
                       cadena invertida y muestra la cadena resultantes en
                       pantalla.

    ***********************************************************************/
}

void convertirCadenas() {
    /**********************************************************************
    Subprograma: Convirtiendo Cadenas
    Tarea que realiza: El subprograma recibira dos cadenas como parametro
                       (cad1, cad2) e imprimirá otras dos cadenas como salida
                       (cad3, cad4)

    ***********************************************************************/
}
