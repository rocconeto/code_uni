********************************************************
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

int main(){

    int opt;
    setlocale(LC_ALL, "spanish");

    do {
        system("pause");
        system("cls");

        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tMENU PRINCIPAL\n");
        printf("\n--------------------------------------------------------------------------\n");
        printf("\t1. Calculos sobre triangulo\n");
        printf("\t2. Dibujar triangulo de Pascal\n");
        printf("\t3. Procesar cadena de caracteres\n");
        printf("\t0. Salir\n");


        do{
            printf("\n\tSeleccione una opcion: ");
            scanf("%d", &opt);
        }while (opt <0 || opt>=4);

        system("pause");
        system("cls");

        switch(opt){
            case 1:
                cuadrado();
                break;
            case 2:
                triangulo();
                break;
            case 3:
                rombo();
                break;
            case 4:
                printf("\tSaliendo del programa...\n");
                break;
        }
    } while (opt != 0);

    return 0;
}

// Programas principales
void triangulo() {
    int subopt;

    do {
        system("pause");
        system("cls");

        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tCALCULOS SOBRE UN TRIANGULO");
        printf("\n--------------------------------------------------------------------------\n");
        printf("\t1. Leer cateto\n");
        printf("\t2. Leer calcular hipotenusa\n");
    }

}

void pascal() {

}

void caracteres() {

}

// SUBPROGRAMAS DEL TRIANGULO
void leerCateto() {
    /**********************************************************************
    Subprograma: Leer Cateto
    Tarea que realiza: Solicita al usuario que introduzca un número real
                       "c" y devuelve al pñunto de llamada el valor leido.

    ***********************************************************************/
}

void calcularHipotenusa() {ç
    /**********************************************************************
    Subprograma: Calcular Hipotenusa
    Tarea que realiza: Pasandole los catetos haciendo uso de la función
                       anterior calcula el valor de la hipotenusa de la
                       siguiente forma, y, devuelve al punto de llamada
                       el resultado obtenido.

    ***********************************************************************/
}

void calcularArea() {
    /**********************************************************************
    Subprograma: Calcular Area
    Tarea que realiza: Calcula el area con los valores de los catetos que
                       recibe como parametros y devuelve al punto de llamada
                       el resultado obtenido.

    ***********************************************************************/
}

void calcularPerimetro() {
    /**********************************************************************
    Subprograma: Calcular Perimetro
    Tarea que realiza: Calcula el perimetro (siendo h, c1 y c2 parametros de
                       este subprograma) y devuelve al puhnto de llamada el
                       resultado obtenido.

    ***********************************************************************/
}

void mostrarResultados() {
    /**********************************************************************
    Subprograma: Mostrar Resultados
    Tarea que realiza: Recibe el resultado obtenido al ejecutar los
                       subprogramas anteriores ymuestra dicho resultado del
                       area, hipotenusa y perimetro en pantalla, así como
                       los catetos considerados.

    ***********************************************************************/
}

// SUBPROGRAMAS DEL TRIÁNGULO DE PASCAL
void pedirNumero() {
    /**********************************************************************
    Subprograma: Pedir Numero
    Tarea que realiza: Solicita al usuario un número entero mayor que 2
                       y será el número de filas del triángulo de Pascal.

    ***********************************************************************/
}

void dibujarTrianguloPascal() {
    /**********************************************************************
    Subprograma: Dibujar Triangulo de Pascal
    Tarea que realiza: Dibuja un triangulo de Pascal con el numero de filas
                       que haya introducido el usuario en el subprograma
                       pedirNumero()
    ***********************************************************************/
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
