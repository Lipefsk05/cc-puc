#include <stdio.h>

double calcular_media_aprovados(int num_alunos) {
    double soma_notas = 0.0;
    int count_aprovados = 0;
    
    for (int i = 0; i < num_alunos; i++) {
        double nota;
        printf("Digite a nota do aluno %d: ", i + 1);
        scanf("%lf", &nota);
        
        if (nota >= 6.0) {
            soma_notas += nota;
            count_aprovados++;
        }
    }
    
    if (count_aprovados > 0) {
        return soma_notas / count_aprovados;
    } else {
        return 0.0;
    }
}

int main() {
    int num_alunos;
    printf("Digite o número de alunos: ");
    scanf("%d", &num_alunos);
    
    double media_aprovados = calcular_media_aprovados(num_alunos);
    
    printf("A média das notas dos alunos aprovados é: %.2lf\n", media_aprovados);
    
    return 0;
}
