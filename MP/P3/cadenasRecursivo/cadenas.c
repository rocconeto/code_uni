#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "cadenas.h"

/************************************************************************/
/*Subprograma:              Contar Vocales en la cadena V1              */
/*Tipo:                     Procedimiento (función tipo void)           */
/*Parámetros de entrada:    Cadena V1 y contador de vocales             */
/*Parámetros de salida:     Contador de vocales                         */
/*Objetivo:                 Se encarga de contar cuántas vocales hay en */
/*                          la cadena de caracteres de forma recursiva  */
/************************************************************************/
void contarVocales(char *V1, int *vocales){
    const char *v = "aeiouAEIOU";

    //Establecemos el caso base
    if(*V1 == '\0'){
        return;
    }

    if(strchr(v, *V1)){ //Busca el primer caracter en el que coinciden
        (*vocales)++;
    }
    //Hace otra llamada al subprograma
    contarVocales(V1+1, vocales);
}

/****************************************************************************/
/*Subprograma:              Eliminar consonantes en la cadena V2            */
/*Tipo:                     Procedimiento (función tipo void)               */
/*Parámetros de entrada:    Cadenas V2 y vocales, e indice                  */
/*Parámetros de salida:     Cadena de vocales (sin consonantes)             */
/*Objetivo:                 Se encarga de quirtar las consonantes de la     */
/*                          cadena de caracteres dejando solo las vocales   */
/****************************************************************************/
void eliminarConsonantes(char *V2, char *Vocals, int *indice){
    const char *v = "aeiouAEIOU";

    //Establecemos el caso base
    if(*V2 == '\0'){
        Vocals[*indice] = '\0';
        return;
    }

    if(strchr(v, *V2)){ //Busca el primer caracter en el que coinciden
        Vocals[*indice] = *V2;
        (*indice)++;
    }
    //Hace otra llamada al subprograma
    eliminarConsonantes(V2+1, Vocals, indice);
}

/*************************************************************************/
/*Subprograma:              Intercalar letras de cada cadena (V1 y V2)   */
/*Tipo:                     Procedimiento (función tipo void)            */
/*Parámetros de entrada:    Cadenas V1, V2 y V3                          */
/*Parámetros de salida:     Cadena V3                                    */
/*Objetivo:                 Se encarga de intercalar en una nueva cadena */
/*                          los caracteres de las otras dos cadenas      */
/*************************************************************************/
void intercalarCadenas(char *V1, char *V2, char *V3){
    //Caso base
    if(*V1 == '\0' && *V2 == '\0'){
        *V3 = '\0';
        return;
    }

    //Si V2 es más larga
    if(*V1 == '\0'){
        strcpy(V3, V2);
    }

    //Si V1 es más larga
    if(*V2 == '\0'){
        strcpy(V3, V1);
    }

    //Copia los caracteres de cada cadena en la nueva cadena
    *V3 = *V1;
    *(V3 + 1) = *V2;

    //Vuelve a llamar al subprograma
    intercalarCadenas(V1 + 1, V2 + 1, V3 + 2);
}

/**********************************************************************/
/*Subprograma:              Duplicar letras de la cadena V1           */
/*Tipo:                     Procedimiento (función tipo void)         */
/*Parámetros de entrada:    Cadenas V1 y duplicadas                   */
/*Parámetros de salida:     Cadena duplicadas                         */
/*Objetivo:                 Se encarga de duplicar las letras de la   */
/*                          cadena en una nueva cadena                */
/**********************************************************************/
void duplicarLetras(char *V1, char *duplicadas){
    //Caso base
    if(*V1 == '\0'){
        return;
    }

    //Duplica las letras en la nueva cadena
    *duplicadas = *V1;
    *(duplicadas+1) = *V1;

    duplicarLetras(V1+1, duplicadas+2);
}

/****************************************************************************************/
/*Subprograma:              Convierte en minúsculas las letras que están en mayúscula   */
/*Tipo:                     Procedimiento (función tipo void)                           */
/*Parámetros de entrada:    Cadenas V1 y V2                                             */
/*Parámetros de salida:     Cadenas V1 y V2                                             */
/*Objetivo:                 Detecta las letras en mayúscula de cada cadena y las        */
/*                          convierte a minúsculas de forma iterativa                   */
/****************************************************************************************/
void aMinusculas_Iterativo(char *V1, char *V2){
    //Cogemos la longitud de cada cadena
    int n = strlen(V1);
    int m = strlen(V2);

    //Busca las mayusculas en la cadena V1 y las convierte en minusculas
    for(int i = 0; i < n; i++){
        if(isupper(V1[i])){
            V1[i] = tolower(V1[i]);
        }
    }

    //Lo mismo para la otra cadena
    for(int j = 0; j < m; j++){
        if(isupper(V2[j])){
            V2[j] = tolower(V2[j]);
        }
    }
}

/****************************************************************************************/
/*Subprograma:              Convierte en minúsculas las letras que están en mayúscula   */
/*Tipo:                     Procedimiento (función tipo void)                           */
/*Parámetros de entrada:    Cadenas V1 y V2                                             */
/*Parámetros de salida:     Cadenas V1 y V2                                             */
/*Objetivo:                 Detecta las letras en mayúscula de cada cadena y las        */
/*                          convierte a minúsculas de forma recursiva                   */
/****************************************************************************************/
void aMinusculas_Recursivo(char *V1, char *V2){
    //Caso base
    if(*V1 == '\0' && *V2 == '\0'){
        return;
    }

    //Hace los cambios en V1
    if(*V1 != '\0'){
        if(isupper(*V1)){
            *V1 = tolower(*V1);
        }
        aMinusculas_Recursivo(V1+1, V2); //Sigue transformando V1
        return; //Evita que pase a transformar V2 hasta que no haya terminado con V1
    }

    //Hace los cambios en V2
    if(*V2 != '\0'){
        if(isupper(*V2)){
            *V2 = tolower(*V2);
        }
        aMinusculas_Recursivo(V1, V2+1); //Sigue transformando V1
        return; //Evita que pase a transformar V2 hasta que no haya terminado con V1
    }
}

/********************************************************************************************/
/*Algoritmo:                Ordena alfabéticamente las letras de una cadena (recursivamente)*/
/*Tipo:                     Procedimiento (función tipo void)                               */
/*Parámetros de entrada:    Cadena a ordenar y su longitud                                  */
/*Parámetros de salida:     Cadena ordenada                                                 */
/*Objetivo:                 Ordena las letras de una cadena de forma recursiva recorriendo  */
/*                          la cadena y comparando pares adyacentes                         */
/********************************************************************************************/
static void ordenar(char *cad, int n){
    //Caso base, cuando ya no queda nada por ordenar
    if(n<= 1){
        return;
    }

    //Recorre la cadena comparando cada par adyacente
    int cambios = 0;
    for(int i = 0; i < n-1; i++){
        if(cad[i] > cad[i+1]){
            char tmp = cad[i]; //Intercambia los dos caracteres
            cad[i] = cad[i+1];
            cad[i+1] = tmp;
            cambios = 1;
        }
    }

    //Si cambios es igual a cero es que ya está ordenada
    if(cambios != 0){
        ordenar(cad, n-1);
    }
}

/********************************************************************************************/
/*Subprograma:              Concatena las cadenas de caracteres V1 y V2 y ordena las letras */
/*Tipo:                     Procedimiento (función tipo void)                               */
/*Parámetros de entrada:    Cadenas V1, V2 y ordenada                                       */
/*Parámetros de salida:     Cadena ordenada                                                 */
/*Objetivo:                 Concatena las cadenas V1 y V2 en una nueva cadena y después     */
/*                          llama al algoritmo que se encarga de ordenar alfabéticamente    */
/********************************************************************************************/
void ordenarCadena(char *V1, char *V2, char *ordenada){
    //Concatenamos las cadenas
    strcpy(ordenada, V1);
    strcat(ordenada, V2);

    //Llamada al algoritmo recursivo
    ordenar(ordenada, strlen(ordenada));
}
