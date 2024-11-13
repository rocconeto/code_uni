#include <stdio.h>

int main() {
    int filas;

    // Solicitar al usuario la cantidad de filas
    printf("Introduce la cantidad de filas para el triángulo de Pascal: ");
    scanf("%d", &filas);

    // Generar cada fila del triángulo de Pascal
    for (int i = 0; i < filas; i++) {
        int valor = 1;  // El primer valor de cada fila es siempre 1

        // Espacios para centrar el triángulo
        for (int j = 0; j < filas - i - 1; j++) {
            printf("   ");
        }

        // Imprimir los valores de la fila `i`
        for (int j = 0; j <= i; j++) {
            printf("%6d", valor);  // Imprimir el valor actual
            // Calcular el siguiente valor en la fila usando el valor actual
            valor = valor * (i - j) / (j + 1);
        }
        printf("\n");  // Nueva línea para la siguiente fila
    }

    return 0;
}
