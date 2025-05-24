#ifndef CADENAS
#define CADENAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "cadenas.h"

void contarVocales(char *V1, int *vocales);
void eliminarConsonantes(char *V2, char *Vocals, int *indice);
void intercalarCadenas(char *V1, char *V2, char *V3);
void duplicarLetras(char *V1, char *duplicadas);
void aMinusculas_Iterativo(char *V1, char *V2);
void aMinusculas_Recursivo(char *V1, char *V2);
void ordenarCadena(char *V1, char *V2, char *ordenada);

#endif // CADENAS
