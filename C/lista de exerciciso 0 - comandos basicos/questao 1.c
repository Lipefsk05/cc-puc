#include <stdio.h>

int main() {
    int numero, centena, dezena, unidade, numero_invertido;

    // Solicita ao usuário que insira um número inteiro de três dígitos
    printf("Digite um número inteiro de três dígitos (no formato CDU): ");
    scanf("%d", &numero);

    // Verifica se o número está no intervalo válido de três dígitos
    if (numero < 100 || numero > 999) {
        printf("O número deve ter exatamente três dígitos.\n");
        return 1; // Sai do programa se o número não for válido
    }

    // Separa o número em centena, dezena e unidade
    centena = numero / 100;
    dezena = (numero / 10) % 10;
    unidade = numero % 10;

    // Forma o número invertido (no formato UDC)
    numero_invertido = unidade * 100 + dezena * 10 + centena;

    // Mostra o número invertido
    printf("O número invertido é: %d\n", numero_invertido);

    return 0;
}
