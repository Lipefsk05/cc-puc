#include <stdio.h>

int main() {
    int voto;
    int votosCandidato1 = 0, votosCandidato2 = 0, votosCandidato3 = 0, votosCandidato4 = 0;
    int votosNulos = 0, votosBrancos = 0;

    printf("Digite o código do candidato (1 a 4), 5 para voto nulo, 6 para voto em branco, ou 0 para encerrar:\n");

    while (1) {
        printf("Código do candidato (1 a 6, 0 para encerrar): ");
        scanf("%d", &voto);

        if (voto == 0) {
            break;
        }

        switch (voto) {
            case 1:
                votosCandidato1++;
                break;
            case 2:
                votosCandidato2++;
                break;
            case 3:
                votosCandidato3++;
                break;
            case 4:
                votosCandidato4++;
                break;
            case 5:
                votosNulos++;
                break;
            case 6:
                votosBrancos++;
                break;
            default:
                printf("Código inválido. Por favor, digite novamente.\n");
        }
    }

    printf("\nResultado da apuração dos votos:\n");
    printf("Votos para o Candidato 1: %d\n", votosCandidato1);
    printf("Votos para o Candidato 2: %d\n", votosCandidato2);
    printf("Votos para o Candidato 3: %d\n", votosCandidato3);
    printf("Votos para o Candidato 4: %d\n", votosCandidato4);
    printf("Votos nulos: %d\n", votosNulos);
    printf("Votos em branco: %d\n", votosBrancos);

    return 0;
}
