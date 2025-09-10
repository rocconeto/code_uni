#include <stdio.h>

// Función para sumar dos arrays y guardar el resultado en tablaSuma
void sumarArrays(int tabla1[], int tabla2[], int tablaSuma[], int size) {
    for (int i = 0; i < size; i++) {
        tablaSuma[i] = tabla1[i] + tabla2[i];
    }
}

int main() {
    int tabla1[5], tabla2[5], tablaSuma[5];

    // Solicitar los números para tabla1
    printf("Introduce 5 números para tabla1:\n");
    for (int i = 0; i < 5; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &tabla1[i]);
    }

    // Solicitar los números para tabla2
    printf("Introduce 5 números para tabla2:\n");
    for (int i = 0; i < 5; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &tabla2[i]);
    }

    // Mostrar ambos arrays en una sola línea
    printf("\nTabla1 y Tabla2:\n");
    for (int i = 0; i < 5; i++) {
        printf("Tabla1[%d]: %d\tTabla2[%d]: %d\n", i, tabla1[i], i, tabla2[i]);
    }

    // Llamar a la función para sumar los arrays
    sumarArrays(tabla1, tabla2, tablaSuma, 5);

    // Mostrar el resultado de la suma
    printf("\nArray resultante (tablaSuma):\n");
    for (int i = 0; i < 5; i++) {
        printf("Elemento %d de tablaSuma: %d\n", i + 1, tablaSuma[i]);
    }

    return 0;
}

