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
#include <ctype.h>

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
        printf("\n\t1. Cálculos sobre un triángulo\n");
        printf("\n\t2. Dibujar triángulo de Pascal\n");
        printf("\n\t3. Procesar cadena de caracteres\n");
        printf("\n\t4. Procesar arrays de números enteros\n");
        printf("\n\t0. Salir\n");


        do{
            printf("\n\n\tSeleccione una opción: ");
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
                printf("\n\tSaliendo del programa...\n");
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
    printf("\n\t\tCÁLCULOS SOBRE UN TRIANGULO\n");
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
/****************************************************
Subprograma:        leerCateto
Tarea:              Pide un número que será el valor
                    del cateto.
Parámetros de S/:   c1 (entero) y c2(entero)
*****************************************************/
void leerCateto(int *c1, int *c2){
    do{
        printf("\n\tIntroduce el valor del primer cateto: ");
        scanf("%d", c1);
    }while(c1<=0);
    do{
        printf("\n\tIntroduce el valor del segundo cateto: ");
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
    printf("\n\n\tEl valor de los catetos es: %d y %d.\n", c1, c2);
    printf("\n\tEl valor de la hipotenusa es: %.2f.\n", h);
    printf("\n\tEl área del triángulo es: %.2f.\n", A);
    printf("\n\tEl perímetro del triángulo es de: %d.\n\n", P);
}

// SUBPROGRAMA TRIÁNGULO DE PASCAL
void pascal() {
    //Declaramos los subprogramas
    void pedirNumero(int *filas);
    void dibujarTrianguloPascal(int filas);

    //Muestra el menú del subprograma
    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tDIBUJAR TRIÁNGULO DE PASCAL\n");
    printf("\n--------------------------------------------------------------------------\n");


    int filas;
    pedirNumero(&filas);
    dibujarTrianguloPascal(filas);

    system("pause");
    system("cls");
}


// SUBPROGRAMAS DEL TRIÁNGULO DE PASCAL
/**********************************************************************
Subprograma:        pedirNumero
Tarea que realiza:  Solicita al usuario un número entero mayor que 2
                    y será el número de filas del triángulo de Pascal.
Parámetros de S/:   filas(entero)
***********************************************************************/
void pedirNumero(int *filas) {
    printf("\n\tIntroduce la cantidad de filas para el triángulo de Pascal: ");
    scanf("%d", filas);
}

/**********************************************************************
Subprograma:        dibujarTrianguloPascal
Tarea que realiza:  Dibuja un triangulo de Pascal con el numero de filas
                    que haya introducido el usuario en el subprograma
                    pedirNumero()
Parámetros de E/:   filas(entero)
***********************************************************************/
void dibujarTrianguloPascal(int filas) {
    printf("\n");
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


// SUBPROGRAMA CARACTERES
void caracteres() {
    char c1[50];
    char c2[50];

    //Declaramos subprogramas
    void anagramaCadenas();
    void convertirMayuscConsonantes();
    void cadena(char *c1[50]);
    void crearCadenaInvertida(char c1[50]);
    void cadenas(char *c1[50], char *c2[50]);
    void convertirCadenas(char c1[50], char c2[50]);
    int opc;

    //Mostramos el menú
    do {
        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tPROCESAR CADENA DE CARACTERES\n");
        printf("\n--------------------------------------------------------------------------\n");
        printf("\n\t1. Anagrama\n");
        printf("\n\t2. Convertir a mayúscula las consonantes\n");
        printf("\n\t3. Invertir cadena\n");
        printf("\n\t4. Convirtiendo cadenas\n");
        printf("\n\t0. Salir\n");


        do{
            printf("\n\n\tSeleccione una opción: ");
            scanf("%d", &opc);
        }while (opc <0 || opc >4);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                anagramaCadenas();
                break;
            case 2:
                convertirMayuscConsonantes();
                break;
            case 3:
                cadena(&c1);
                crearCadenaInvertida(c1);
                break;
            case 4:
                cadenas(&c1, &c2);
                convertirCadenas(c1, c2);
                break;
            case 0:
                system("cls");
                break;
        }
    } while (opc != 0);
}


// SUBPROGRAMAS PARA PROCESAR CARACTERES
/**********************************************************************
Subprograma:        anagramaCadena
Tarea que realiza:  Solicita al usuario dos palabras, comprueba si son
                    anagramas y muestra por pantalla el resultado.
Parámetros de E/:   word1(cadena caracateres) y word2(cadena caracteres)
***********************************************************************/
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
void anagramaCadenas() {
    char word1[50];
    char word2[50];
    int long1, long2, i, e, j;

    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tAnagrama\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Hacer que si no tienen la misma longitud o si es la misma palabra
    //vuelva a pedir introducirlas.
    fflush(stdin);
    do{
        //Pide la primera palabra y quita el salto de línea
        printf("\n\tIntroduce la primera palabra: ");
        fgets(word1, sizeof(word1), stdin);
        word1[strcspn(word1, "\n")] = '\0';

        //Pide la segunda palabra y quita el salto de línea
        printf("\tIntroduce la segunda palabra: ");
        fgets(word2, sizeof(word2), stdin);
        word2[strcspn(word2, "\n")] = '\0';

        //Calcula la longitud de cada palabra
        long1 = strlen(word1);
        long2 = strlen(word2);

        if (long1 != long2){
            printf("\n\tLas palabras tienen que tener la misma longitud.\n");
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
        printf("\n\tDos palabras iguales no son anagramas\n\n");
    } else if(anagramas(word1, word2)){
        printf("\n\tSon anagramas\n\n");
    } else{
        printf("\n\tNo son anagramas\n\n");
    }

    system("pause");
    system("cls");

    return 0;
}


/**********************************************************************
Subprograma:        convertirMayusculasConsonantes
Tarea que realiza:  Solicita al usuario una palabras y pasa las
                    consonantes a mayúscula
Parámetros de E/:   word1(cadena caracateres)
***********************************************************************/
void convertirMayuscConsonantes() {
    fflush(stdin);
    //Declaramos variables
    char vocales[5] = ("AEIOU");
    char word1[50], word2[50];
    int i, e;

    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tConvertir a Mayúsculas las Consonantes\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Solicita la palabra al usuraio y la pasa a mayúsculas
    printf("\n\tIntroduce una palabra: ");
    fgets(word1, sizeof(word1), stdin);
    word1[strcspn(word1, "\n")] = '\0';

    strupr (word1);

    //Pasa a mayúsculas las consonantes
    for (i=0; word1[i]; i++){
        for (e=0; vocales[e]; e++){
            if (word1[i] == vocales[e]){
                word1[i] = tolower(word1[i]);
                break;
            }
        }
    }

    //Muestra la palabra con las consonantes en mayúscula
    printf("\n\t%s\n", word1);

    system("pause");
    system("cls");
}

/**********************************************************************
Subprograma:        cadena
Tarea que realiza:  Solicita al usuario una cadena de caracteres y la
                    almacena como parámetro
Parámetros de S/:   c1(cadena caracateres)
***********************************************************************/
void cadena(char *c1[50]){
    fflush(stdin);

    //Pide una cadena de caracteres
    printf("\n\tIntroduce una cadena de caracteres: ");
    fgets(c1, 50, stdin);

    system("pause");
    system("cls");
}

/**********************************************************************
Subprograma:        crearCadenaInnvertida
Tarea que realiza:  Recibe una cadena como parámtero, la invierte y
                    la muestra por pantalla
Parámetros de E/:   c1(cadena caracateres)
***********************************************************************/
void crearCadenaInvertida(char c1[50]) {
    //Declaramos variables y quitamos el salto de línea a la cadena de caracteres
    int i, longitud;
    c1[strcspn(c1, "\n")] = '\0';

    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tInvertir Cadena Caracteres\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Solicita la palabra al usuraio y la pasa a mayúsculas
    printf("\n\tCadena original: %s\n", c1);

    longitud = strlen(c1);

    //Invierte la cadena
    printf("\n\tCadena invertida: ");
    for (i= longitud - 1; i >= 0; i--){
        printf("%c", c1[i]);
    }
    printf("\n\n");

    system("pause");
    system("cls");
}


/**********************************************************************
Subprograma:        cadenas
Tarea que realiza:  Solicita al usuario dos cadenas de caracteres y las
                    almacena como parámetros
Parámetros de S/:   c1(cadena caracateres) y c2(cadena de caracteres)
***********************************************************************/
void cadenas(char *c1[50], char *c2[50]){
    fflush(stdin);

    //Pide las cadenas de caracteres
    printf("\n\tIntroduce una cadena de caracteres: ");
    fgets(c1, 50, stdin);

    printf("\n\tIntroduce otra cadena de caracteres: ");
    fgets(c2, 50, stdin);

    system("pause");
    system("cls");
}

/**********************************************************************
Subprograma:        convertirCadenas
Tarea que realiza:  Recibe dos cadenas de caracteres como parámteros y las
                    convierte teniendo en cuenta los caracteres que están
                    en una de ellas pero no en la otra, también muestra
                    los caracteres omitidos.
Parámetros de S/:   c1(cadena caracateres) y c2(cadena de caracteres)
***********************************************************************/
void convertirCadenas(char c1[50], char c2[50]) {


    //Declaramos las cadenas resultantes y otras variables
    char c3[50], c4[50];
    int o = 0, p = 0; //Para las cantidades de caracteres omitidos
    int c = 0, d = 0;

    //Quita los saltos de línea a las cadenas de caracteres
    c1[strcspn(c1, "\n")] = '\0';
    c2[strcspn(c2, "\n")] = '\0';

    //Muestra el título del programa
    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\tConvertir Cadenas de CAracteres\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Muestra las cadenas originales calcula y muestra los caracteres omitidos
    printf("\n\tCADENA ORIGINAL\t\t\tCADENA CONVERTIDA\t\tCARACTERES OMITIDOS\n");

    //Muestra la cadena 1, luego la convierte y muestra la cadena convertida y los elementos omitidos
    printf("\n\tCadena 1: %s\t", c1);

    for (int i=0; c1[i]; i++){
        int presente = 0; //Si encuentra un caracter en c2 igual al de c1 cambia su valor
        //si no encuentra ninguno, sirve para añadir a c3 los caracteres
        for (int e=0; c2[e]; e++){
            if (c1[i] == c2[e]){
                o++;
                presente = 1;
                break;
            }
        }
        if (presente == 0){
            c3[c++] = c1[i];
        }
    }
    printf("\t%s\t\t\t\t%d elementos omitidos\n", c3, o);

    //Hace lo mismo con la cadena 2
    printf("\n\tCadena 2: %s", c2);

    for (int i=0; c2[i]; i++){
        int presente = 0; //Si encuentra un caracter en c2 igual al de c1 cambia su valor
        //si no encuentra ninguno, sirve para añadir a c3 los caracteres
        for (int e=0; c1[e]; e++){
            if (c2[i] == c1[e]){
                p++;
                presente = 1;
                break;
            }
        }
        if (presente == 0){
            c4[d++] = c2[i];
        }
    }
    printf("\t%s\t\t\t\t%d elementos omitidos\n\n", c4, p);

    system("pause");
    system("cls");
}

//SUBPROGRAMA ARRAYS DE NÚMEROS ENTEROS
void arrays(){
    //Declaramos los arrays necesarios y los subprogramas
    int tabla1 [5], tabla2[5], tablaSuma[5], opc;
    void sumaArrays(int tabla1[5], int tabla2[5], int tablaSuma[5]);
    void multiplicacionArrays(int tabla1[5], int tabla2[5]);
    void interseccionArrays(int tabla1[5], int tabla2[5]);

    //Comienza la ejecución pidiendo los 10 números
    for (int i = 0; i < 5; i++){
        printf("\n\tIntroduce un número: ");
        scanf("%d", &tabla1[i]);
    }
    for (int i = 0; i < 5; i++){
        printf("\n\tIntroduce un número: ");
        scanf("%d", &tabla2[i]);
    }

    system("pause");
    system("cls");

    do {
        printf("--------------------------------------------------------------------------\n");
        printf("\n\t\tPROCESAR ARRAYS DE NÚMEROS ENTEROS\n");
        printf("\n--------------------------------------------------------------------------\n");
        printf("\n\t1. Suma\n");
        printf("\n\t2. Multiplicación\n");
        printf("\n\t3. Intersección\n");
        printf("\n\t0. Salir\n");


        do{
            printf("\n\n\tSeleccione una opción: ");
            scanf("%d", &opc);
        }while (opc <0 || opc >3);

        system("pause");
        system("cls");

        switch(opc){
            case 1:
                sumaArrays(tabla1, tabla2, tablaSuma);
                printf("--------------------------------------------------------------------------\n");
                printf("\n\t\tSUMA DE ARRAYS\n");
                printf("\n--------------------------------------------------------------------------\n");

                //Muestra el resultado de la ejecución del subprograma
                printf("\n\ttablaSuma = [");
                for (int i = 0; tablaSuma[i]; i++){
                    printf(" %d", tablaSuma[i]);
                }
                printf("]\n");

                system("pause");
                system("cls");
                break;
            case 2:
                multiplicacionArrays(tabla1, tabla2);
                break;
            case 3:
                interseccionArrays(tabla1, tabla2);
                break;
            case 0:
                system("cls");
                break;
        }
    } while (opc != 0);


}

//SUBPROGRAMAS PARA PROCESAR ARRAYS
/**********************************************************************
Subprograma:        sumaArrays
Tarea que realiza:  Recibe dos arrays de números enteros y suma ambos
                    arrays. Guarda la suma en un parámetro llamado
                    tablaSuma.
Parámetros de E/:   tabla1(array de enteros) y tabla2(array de enteros)
Parámetros de S/:   tablaSuma(array de enteros)
***********************************************************************/
void sumaArrays(int tabla1[5], int tabla2[5], int tablaSuma[5]){
    //Mostramos un título
    printf("\n\tSUMA\n");
    printf("----------------------\n");

    //Ejecuta las operaciones
    for (int i = 0; i < 5; i++) {
        tablaSuma[i] = tabla1[i] + tabla2[i];
    }

    system("pause");
    system("cls");
}

/**********************************************************************
Subprograma:        multiplicacionArrays
Tarea que realiza:  Recibe dos arrays de números enteros y multiplica ambos
                    arrays. Después, muestra el resultado por pantalla.
Parámetros de E/:   tabla1(array de enteros) y tabla2(array de enteros)
***********************************************************************/
void multiplicacionArrays(int tabla1[5], int tabla2[5]){
    //Declaramos un array para la multiplicación de los dos arrays
    int tablaMultiplicacion[5];

    //Mostramos el título
    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\MULTIPLICACIÓN DE ARRAYS\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Ejecuta la multiplicación
    for (int e = 0; e < 5; e++){
        tablaMultiplicacion[e] = tabla1[e] * tabla2[e];
    }

    //Muestra los resultados
    printf("\n\ttablaMultiplicación = [");
    for (int i = 0; tablaMultiplicacion[i]; i++){
        printf(" %d", tablaMultiplicacion[i]);
    }
    printf("]\n");

    system("pause");
    system("cls");
}

/**********************************************************************
Subprograma:        interseccionArrays
Tarea que realiza:  Recibe dos arrays de números enteros y calcula la
                    la intersección de ambos arrays. Después, muestra
                    el resultado por pantalla.
Parámetros de E/:   tabla1(array de enteros) y tabla2(array de enteros)
***********************************************************************/
void interseccionArrays(int tabla1[5], int tabla2[5]){
    //Declaramos una variable para la intersección
    int tablaInterseccion[5];
    int k = 0; //Contador para el array tablaInterseccion

    //Mostramos el título
    printf("--------------------------------------------------------------------------\n");
    printf("\n\t\INTERSECCIÓN DE ARRAYS\n");
    printf("\n--------------------------------------------------------------------------\n");

    //Calcula la intersección y después la muestra
    for (int i = 0; tabla1[i]; i++){
        for (int e = 0; tabla2[e]; e++){
            if(tabla1[i] == tabla2[e]){
                tablaInterseccion[k] = tabla1[i];
                k++;
                break;
            }
        }
    }

    printf("\n\ttablaInterseccion = [");
    for (int i = 0; tablaInterseccion[i]; i++){
        printf(" %d", tablaInterseccion[i]);
    }
    printf("]\n");

    system("pause");
    system("cls");
}
