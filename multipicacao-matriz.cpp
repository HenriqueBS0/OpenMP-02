#include <stdio.h>
#include <omp.h>

#define N 4  // Dimensão das matrizes

void print_matrix(int matriz[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matriz_a[N][N], matriz_b[N][N], matriz_resultado[N][N];
    int i, j, k;

    // Inicialização das matrizes
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matriz_a[i][j] = i + 1;  // Exemplo de valores para matriz_a
            matriz_b[i][j] = j + 1;  // Exemplo de valores para matriz_b
            matriz_resultado[i][j] = 0;
        }
    }

    // Multiplicação das matrizes com seções
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                // Paraleliza o cálculo da primeira metade das linhas da matriz resultado
                #pragma omp parallel for
                for (i = 0; i < N/2; i++) {
                    for (j = 0; j < N; j++) {
                        matriz_resultado[i][j] = 0;
                        for (k = 0; k < N; k++) {
                            matriz_resultado[i][j] += matriz_a[i][k] * matriz_b[j][k];
                        }
                    }
                }
            }

            #pragma omp section
            {
                // Paraleliza o cálculo da segunda metade das linhas da matriz resultado
                #pragma omp parallel for
                for (i = N/2; i < N; i++) {
                    for (j = 0; j < N; j++) {
                        matriz_resultado[i][j] = 0;
                        for (k = 0; k < N; k++) {
                            matriz_resultado[i][j] += matriz_a[i][k] * matriz_b[j][k];
                        }
                    }
                }
            }
        }
    }

    // Impressão das matrizes
    printf("Matriz A:\n");
    print_matrix(matriz_a);

    printf("\nMatriz B:\n");
    print_matrix(matriz_b);

    printf("\nMatriz Resultado:\n");
    print_matrix(matriz_resultado);

    return 0;
}
