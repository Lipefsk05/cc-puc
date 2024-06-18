#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para validar e corrigir o número de telefone
void validarCorrigirTelefone(char *telefone) {
    int tamanho = strlen(telefone);
    char telefoneCorrigido[15]; // Máximo de 14 caracteres + 1 para o '\0'
    int pos = 0; // Posição atual no telefone corrigido

    // Remover traços e espaços do número de telefone
    for (int i = 0; i < tamanho; i++) {
        if (isdigit(telefone[i])) {
            telefoneCorrigido[pos++] = telefone[i];
        }
    }
    telefoneCorrigido[pos] = '\0'; // Adiciona o caractere nulo ao final da string

    // Verifica o tamanho do número
    tamanho = strlen(telefoneCorrigido);

    if (tamanho == 8) {
        // Se o número tem 8 dígitos, adiciona '9' na frente
        printf("Telefone possui 8 dígitos. Vou acrescentar o dígito '9' na frente.\n");
        strcpy(telefoneCorrigido + 1, telefoneCorrigido); // Move os caracteres uma posição para a direita
        telefoneCorrigido[0] = '9';
        tamanho = 9; // Atualiza o tamanho do número corrigido
    }

    // Imprime o telefone corrigido sem formatação
    printf("Telefone corrigido sem formatação: %s\n", telefoneCorrigido);

    // Imprime o telefone corrigido com formatação (se possível)
    if (tamanho == 9) {
        printf("Telefone corrigido com formatação: %c%c%c%c%c-%c%c%c%c\n",
               telefoneCorrigido[0], telefoneCorrigido[1], telefoneCorrigido[2],
               telefoneCorrigido[3], telefoneCorrigido[4], telefoneCorrigido[5],
               telefoneCorrigido[6], telefoneCorrigido[7], telefoneCorrigido[8]);
    } else {
        printf("Não é possível formatar o telefone.\n");
    }
}

int main() {
    char telefone[20];

    printf("Digite o número de telefone (com ou sem traço separador): ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = '\0'; // Remover o caractere de nova linha, se presente

    // Validar e corrigir o telefone
    validarCorrigirTelefone(telefone);

    return 0;
}
