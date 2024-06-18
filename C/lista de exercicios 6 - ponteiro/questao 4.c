#include <stdio.h>

#define TAMANHO_VETOR 31

// Procedimento para preencher o vetor com as temperaturas de janeiro
void preencherTemperaturas(float temperaturas[]) {
    printf("Digite as temperaturas de cada dia de janeiro:\n");
    for (int i = 0; i < TAMANHO_VETOR; ++i) {
        printf("Dia %d: ", i + 1);
        scanf("%f", &temperaturas[i]);
    }
}

// Função para encontrar a menor temperatura
float encontrarMenorTemperatura(float temperaturas[]) {
    float menor = temperaturas[0];
    for (int i = 1; i < TAMANHO_VETOR; ++i) {
        if (temperaturas[i] < menor) {
            menor = temperaturas[i];
        }
    }
    return menor;
}

// Função para encontrar a maior temperatura
float encontrarMaiorTemperatura(float temperaturas[]) {
    float maior = temperaturas[0];
    for (int i = 1; i < TAMANHO_VETOR; ++i) {
        if (temperaturas[i] > maior) {
            maior = temperaturas[i];
        }
    }
    return maior;
}

// Função para calcular a média das temperaturas
float calcularMedia(float temperaturas[]) {
    float soma = 0;
    for (int i = 0; i < TAMANHO_VETOR; ++i) {
        soma += temperaturas[i];
    }
    return soma / TAMANHO_VETOR;
}

// Função para contar quantos dias tiveram temperatura inferior à média
int contarDiasInferioresMedia(float temperaturas[]) {
    float media = calcularMedia(temperaturas);
    int count = 0;
    for (int i = 0; i < TAMANHO_VETOR; ++i) {
        if (temperaturas[i] < media) {
            count++;
        }
    }
    return count;
}

int main() {
    float temperaturas[TAMANHO_VETOR];
    float menor, maior, media;
    int diasInferioresMedia;

    // Preenche o vetor com as temperaturas de janeiro
    preencherTemperaturas(temperaturas);

    // Encontra a menor e a maior temperatura
    menor = encontrarMenorTemperatura(temperaturas);
    maior = encontrarMaiorTemperatura(temperaturas);

    // Calcula a média das temperaturas
    media = calcularMedia(temperaturas);

    // Conta quantos dias tiveram temperatura inferior à média
    diasInferioresMedia = contarDiasInferioresMedia(temperaturas);

    // Exibe os resultados
    printf("\nMenor temperatura: %.2f°C\n", menor);
    printf("Maior temperatura: %.2f°C\n", maior);
    printf("Temperatura média: %.2f°C\n", media);
    printf("Dias com temperatura inferior à média: %d\n", diasInferioresMedia);

    return 0;
}
