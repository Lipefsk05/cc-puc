#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *arquivo;
    int n;
    double valor;
    long pos;
    
    // Lendo o número de valores reais a serem armazenados
    scanf("%d", &n);
    
    // Abrindo o arquivo para escrita em modo binário
    arquivo = fopen("dados.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    // Lendo e armazenando os valores reais no arquivo binário
    for (int i = 0; i < n; i++) {
        scanf("%lf", &valor);
        fwrite(&valor, sizeof(double), 1, arquivo);
    }
    
    fclose(arquivo);
    
    // Abrindo o arquivo para leitura reversa em modo binário
    arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    // Indo para o final do arquivo
    fseek(arquivo, 0, SEEK_END);
    pos = ftell(arquivo);
    
    // Lendo de trás para frente
    for (int i = 1; i <= n; i++) {
        pos -= sizeof(double);
        fseek(arquivo, pos, SEEK_SET);
        fread(&valor, sizeof(double), 1, arquivo);
        
        if (fabs(valor - (int)valor) < 1e-6) {
            printf("%d\n", (int)valor);
        } else {
            printf("%g\n", valor);
        }
    }
    
    fclose(arquivo);
    return 0;
}
