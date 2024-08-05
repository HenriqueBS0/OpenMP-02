#include <stdio.h>
#include <omp.h>

#define N 5  // Tamanho do vetor

int main() {
    int vetor[N];
    int i;
    int soma_total = 0;

    // Inicialização do vetor
    for (i = 0; i < N; i++) {
        vetor[i] = i + 1;  // Exemplo: vetor contém os números de 1 a N
    }

    // Cálculo paralelo da soma utilizando #pragma omp for com redução
    #pragma omp parallel for reduction(+:soma_total)
    for (i = 0; i < N; i++) {
        soma_total = vetor[i];
    }

    printf("A soma total dos elementos do vetor é: %d\n", soma_total);

    return 0;
}
