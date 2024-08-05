#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <ctime>

#define ROWS 10
#define COLS 10

int main() {
    int matriz[ROWS][COLS];
    int i, j;

    // Inicialização do gerador de números aleatórios
    #pragma omp parallel
    {
        #pragma omp single
        {
            srand(time(NULL));
        }

        // Preenchimento da matriz em paralelo
        #pragma omp for collapse(2)
        for (i = 0; i < ROWS; i++) {
            for (j = 0; j < COLS; j++) {
                matriz[i][j] = rand();
            }
        }
    }

    // Impressão da matriz para verificar os valores
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
