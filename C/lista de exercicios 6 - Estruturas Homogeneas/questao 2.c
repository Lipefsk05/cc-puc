int main() {
    int vetorX[TAMANHO_VETOR];
    int *vetorNegativos;
    int qtdNegativos;

    // Preenche o vetor X
    preencherVetor(vetorX);

    // Copia os valores negativos para um novo vetor
    vetorNegativos = copiarNegativos(vetorX, TAMANHO_VETOR, &qtdNegativos);

    // Exibe o vetor original
    printf("\nVetor original:\n");
    exibirVetor(vetorX, TAMANHO_VETOR);

    // Exibe o vetor de negativos, se houver
    if (vetorNegativos != NULL) {
        printf("\nVetor de negativos:\n");
        exibirVetor(vetorNegativos, qtdNegativos);
        free(vetorNegativos); // Libera a memória alocada dinamicamente
    } else {
        printf("\nNão foram encontrados valores negativos.\n");
    }

    return 0;
}
