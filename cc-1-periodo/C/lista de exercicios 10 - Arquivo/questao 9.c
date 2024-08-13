#include <stdio.h>
#include <stdlib.h>

#define MAX_ALUNOS 100

// Estrutura para armazenar os dados de cada aluno
typedef struct {
    int matricula;
    char telefone[15]; // Considerando um telefone no formato XXXX-XXXX
} Aluno;

// Função para armazenar dados de alunos em um arquivo
void armazenarDados(Aluno alunos[], int num_alunos) {
    FILE *arquivo;
    arquivo = fopen("alunos.txt", "w");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    for (int i = 0; i < num_alunos; i++) {
        fprintf(arquivo, "%d %s\n", alunos[i].matricula, alunos[i].telefone);
    }
    
    fclose(arquivo);
    printf("Dados dos alunos foram armazenados no arquivo alunos.txt.\n");
}

// Função para ler dados de alunos de um arquivo
void lerDados() {
    FILE *arquivo;
    arquivo = fopen("alunos.txt", "r");
    
    if (arquivo == NULL) {
        printf("Arquivo não encontrado ou erro ao abrir o arquivo.\n");
        return;
    }
    
    Aluno alunos[MAX_ALUNOS];
    int num_alunos = 0;
    
    while (fscanf(arquivo, "%d %s", &alunos[num_alunos].matricula, alunos[num_alunos].telefone) != EOF) {
        num_alunos++;
    }
    
    fclose(arquivo);
    
    if (num_alunos == 0) {
        printf("Nenhum dado de aluno encontrado no arquivo.\n");
    } else {
        printf("Dados dos alunos lidos do arquivo:\n");
        printf("Matrícula   Telefone\n");
        for (int i = 0; i < num_alunos; i++) {
            printf("%8d   %s\n", alunos[i].matricula, alunos[i].telefone);
        }
    }
}

int main() {
    int opcao, num_alunos = 0;
    Aluno alunos[MAX_ALUNOS];
    
    do {
        printf("\n=== Menu ===\n");
        printf("1. Armazenar dados de alunos\n");
        printf("2. Ler dados de alunos\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                // Armazenar dados de alunos
                if (num_alunos >= MAX_ALUNOS) {
                    printf("Limite máximo de alunos atingido (%d).\n", MAX_ALUNOS);
                } else {
                    printf("Digite a matrícula do aluno: ");
                    scanf("%d", &alunos[num_alunos].matricula);
                    printf("Digite o telefone do aluno (formato XXXX-XXXX): ");
                    scanf("%s", alunos[num_alunos].telefone);
                    num_alunos++;
                }
                break;
            case 2:
                // Ler dados de alunos do arquivo
                lerDados();
                break;
            case 3:
                // Sair do programa
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 3);
    
    // Se houver alunos para armazenar, chama a função de armazenamento
    if (num_alunos > 0) {
        armazenarDados(alunos, num_alunos);
    }
    
    return 0;
}
