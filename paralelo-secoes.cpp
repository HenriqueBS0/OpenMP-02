#include <stdio.h>
#include <omp.h>

#define N 4  // Tamanho dos vetores

int main() {
    int vetor_soma[N], vetor_produto[N];
    int soma = 0;
    int produto = 1;

    // Inicialização dos vetores
    for (int i = 0; i < N; i++) {
        vetor_soma[i] = i + 1;  // Vetor de 1 a N
        vetor_produto[i] = i + 1;  // Vetor de 1 a N
    }

    // Processamento paralelo com seções
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                // Cálculo da soma
                #pragma omp parallel for reduction(+:soma)
                for (int i = 0; i < N; i++) {
                    soma += vetor_soma[i];
                }
            }

            #pragma omp section
            {
                // Cálculo do produto
                #pragma omp parallel for reduction(*:produto)
                for (int j = 0; j < N; j++) {
                    produto *= vetor_produto[j];
                }
            }
        }
    }

    // Impressão dos resultados
    printf("A soma dos elementos do vetor é: %d\n", soma);
    printf("O produto dos elementos do vetor é: %d\n", produto);

    return 0;
}
