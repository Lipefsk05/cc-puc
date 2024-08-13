#include <stdio.h>

char determinar_categoria(int idade) {
    if (idade >= 5 && idade <= 7) {
        return 'F';
    } else if (idade >= 8 && idade <= 10) {
        return 'E';
    } else if (idade >= 11 && idade <= 13) {
        return 'D';
    } else if (idade >= 14 && idade <= 15) {
        return 'C';
    } else if (idade >= 16 && idade <= 17) {
        return 'B';
    } else {
        return 'A';
    }
}

int main() {
    int idade;
    printf("Digite a idade do nadador: ");
    scanf("%d", &idade);
    
    char categoria = determinar_categoria(idade);
    
    printf("A categoria do nadador é: %c\n", categoria);
    
    return 0;
}
