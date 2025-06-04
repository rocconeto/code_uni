#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nombre[30];
    int edad;
    float sueldo;
}tRegPersona;

int main(){
    int contador = 0;

    //tRegPersona persona[3];

    FILE *personas = fopen("Personas.dat", "r");

    /*strcpy(persona[0].nombre, "Pablo Marcos Sanz");
    persona[0].edad = 23;
    persona[0].sueldo = 1500;

    strcpy(persona[1].nombre, "Maria Garcia Perez");
    persona[1].edad = 45;
    persona[1].sueldo = 2560;

    strcpy(persona[2].nombre, "Javier Lagos Mas");
    persona[2].edad = 57;
    persona[2].sueldo = 3780;

    fwrite(persona, sizeof(tRegPersona), 3, personas);
    fclose(personas);*/

    if(personas == NULL){
        printf("\n\tERROR: al abrir el fichero 'Personas.dat'\n");
        system("pause");
        exit(1);
    }

    tRegPersona persona;

    printf("\n\t\tFichero Personas.dat ORIGINAL");
    printf("\n\t\t-----------------------------\n");
    printf("\n\tNombre\t\tEdad\t\tSueldo\n");

    while(fread(&persona, sizeof(tRegPersona), 1, personas) == 1){
        contador++;
        printf("\n\t%s\t%d\t\t%.2f\n", persona.nombre, persona.edad, persona.sueldo);
    }

    printf("\n\n\t\tFichero Personas.dat INVERTIDO");
    printf("\n\t\t-----------------------------\n");
    printf("\n\tNombre\t\tEdad\t\tSueldo\n");

    //Calculamos la longitud del fichero
    fseek(personas, 0, SEEK_END);

    long tamano_archivo = ftell(personas);
    int registros = tamano_archivo/sizeof(tRegPersona);

    for(int i = registros-1; i >= 0; i--){
        fseek(personas, i*sizeof(tRegPersona), SEEK_SET);
        fread(&persona, sizeof(tRegPersona), 1, personas);
        printf("\n\t%s\t%d\t\t%.2f\n", persona.nombre, persona.edad, persona.sueldo);
    }

    fclose(personas);

    system("pause");

    return 0;
}
