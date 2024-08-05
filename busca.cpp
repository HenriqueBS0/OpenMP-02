#include <stdio.h>
#include <omp.h>

#define N 10  // Tamanho do vetor

int main() {
    int vetor[N];;  // Exemplo de vetor
    int valor_procurado = 5;  // Valor a ser buscado
    int posicao_encontrada = -1;  // Posição do valor encontrado, -1 se não encontrado

    for (int i = 0; i < N; i++) {
        vetor[i] = i + 1;
    }

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            if (vetor[i] == valor_procurado) {
                #pragma omp critical
                {
                    // Atualiza a posição encontrada somente se ainda não foi encontrado
                    if (posicao_encontrada == -1) {
                        posicao_encontrada = i;
                    }
                }
            }
        }

        #pragma omp single
        {
            if (posicao_encontrada != -1) {
                printf("O valor %d foi encontrado na posição %d.\n", valor_procurado, posicao_encontrada);
            } else {
                printf("O valor %d não foi encontrado no vetor.\n", valor_procurado);
            }
        }
    }

    return 0;
}
