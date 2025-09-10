#include <stdio.h>
#include <stdlib.h>

int main()
{
    system("cls");
    char jugador[30];
    int goles, asistencias, partidos;
    float asis;

    /*Pide al usuario los datos*/
    printf("Introduce el nombre del jugador: ");
    fgets(jugador, 30, stdin);
    printf("Introduce el numero de goles: ");
    scanf("%d", &goles);
    printf("Introduce el numero de asistencias: ");
    scanf("%d", &asistencias);
    printf("Introduce el numero de partidos: ");
    scanf("%d", &partidos);

    //Paso las asistencias a float para poder mostrar los dos decimales
    asis = asistencias;

    /*Elabora la ficha*/
    printf("\n\tFICHA DEL JUGADOR\n");
    printf("Nombre:\t\t\t\t %s", jugador);
    printf("Goles:\t\t\t\t %d\n", goles);
    printf("Asistencias:\t\t\t %d\n", asistencias);
    printf("Partidos jugados:\t\t %d\n", partidos);
    printf("Goles en formato de 3 digitos:\t %03d\n", goles);
    printf("Asistencias con 2 decimales:\t %.2f\n", asis);

    printf("Pulse <Intro> para continuar...");
}
