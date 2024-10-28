/**********************************************************
Revisar el pdf de guía de estilo
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    long int lg_int;
    float flt;
    double dbl;
    long double lg_dbl;
    int sz_char, sz_int, sz_sh_int, sz_lg_int, sz_float, sz_double, sz_lg_double; // Declaramos las variables

    // Mostramos los resultados por pantalla
    printf("TIPO \t  TAMAÑO(en bytes))\n");
    printf("----- \t -----------------\n");
    printf("char:\t\t%d\n", sizeof(char));
    printf("int:\t\t%d\n", sizeof(int));
    printf("short int:\t%d\n", sizeof(short));
    printf("long int:\t%d\n", sizeof(lg_int));
    printf("float:\t\t%d\n", sizeof(flt));
    printf("double:\t\t%d\n", sizeof(dbl));
    printf("long double:\t%d\n", sizeof(lg_dbl));

    return 0;
}
