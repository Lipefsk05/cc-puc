#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdbool.h>
#include <err.h>

typedef struct{
    int day;
    int month;
    int year;
}DATA;

typedef struct{
    char *id;
    char *categoria;
    char *nome;
    char *diretor;
    char **elenco;
    size_t numElenco;
    char *pais;
    DATA data_adicao;
    int ano_lancamento;
    char *classificacao;
    char *duracao;
    char **generos;
    size_t numGeneros;
}PROGRAMA;


PROGRAMA copiarPrograma(PROGRAMA original){
    PROGRAMA copia;

    copia.id = (char *)calloc(strlen(original.id) + 1,sizeof(char));
    strcpy(copia.id,original.id);

    copia.categoria = (char *)calloc(strlen(original.categoria) + 1,sizeof(char));
    strcpy(copia.categoria,original.categoria);

    copia.nome = (char *)calloc(strlen(original.nome) + 1,sizeof(char));
    strcpy(copia.nome,original.nome);

    copia.diretor = (char *)calloc(strlen(original.diretor) + 1,sizeof(char));
    strcpy(copia.diretor,original.diretor);

    copia.numElenco = original.numElenco;

    if(copia.numElenco > 0){
        copia.elenco = (char **)calloc(copia.numElenco, sizeof(char *));
        for(int i = 0; i < copia.numElenco; i++){
            copia.elenco[i] = (char *)calloc(strlen(original.elenco[i]) + 1, sizeof(char));
            strcpy(copia.elenco[i],original.elenco[i]);
        }
    }else{
        copia.elenco = NULL;
    }

    copia.pais = (char *)calloc(strlen(original.pais) + 1,sizeof(char));
    strcpy(copia.pais,original.pais);

    copia.data_adicao = original.data_adicao;

    copia.ano_lancamento = original.ano_lancamento;

    copia.classificacao = (char *)calloc(strlen(original.classificacao) + 1,sizeof(char));
    strcpy(copia.classificacao,original.classificacao);

    copia.duracao = (char *)calloc(strlen(original.duracao) + 1,sizeof(char));
    strcpy(copia.duracao,original.duracao);

    copia.numGeneros = original.numGeneros;

    if(copia.numGeneros > 0){
        copia.generos = (char **)calloc(copia.numGeneros, sizeof(char *));
        for(int i = 0; i < copia.numGeneros; i++){
            copia.generos[i] = (char *)calloc(strlen(original.generos[i]) + 1, sizeof(char));
            strcpy(copia.generos[i],original.generos[i]);
        }
    }else{
        copia.generos = NULL;
    }

    return copia;
}

int converterMesParaNumero(char *mes){
    int resultado = 0;

    if(strcmp(mes,"January") == 0) resultado = 1; 
    if(strcmp(mes,"February") == 0) resultado = 2; 
    if(strcmp(mes,"March") == 0) resultado = 3; 
    if(strcmp(mes,"April") == 0) resultado = 4; 
    if(strcmp(mes,"May") == 0) resultado = 5; 
    if(strcmp(mes,"June") == 0) resultado = 6; 
    if(strcmp(mes,"July") == 0) resultado = 7; 
    if(strcmp(mes,"August") == 0) resultado = 8; 
    if(strcmp(mes,"September") == 0) resultado = 9; 
    if(strcmp(mes,"October") == 0) resultado = 10; 
    if(strcmp(mes,"November") == 0) resultado = 11; 
    if(strcmp(mes,"December") == 0) resultado = 12; 

    return resultado;
}

char *converterNumeroParaMes(int num){
    char *resultado = (char *)malloc(25 * sizeof(char));
    
    switch(num){
        case 1: strcpy(resultado,"January"); break;
        case 2: strcpy(resultado,"February"); break;
        case 3: strcpy(resultado,"March"); break;
        case 4: strcpy(resultado,"April"); break;
        case 5: strcpy(resultado,"May"); break;
        case 6: strcpy(resultado,"June"); break;
        case 7: strcpy(resultado,"July"); break;
        case 8: strcpy(resultado,"August"); break;
        case 9: strcpy(resultado,"September"); break;
        case 10: strcpy(resultado,"October"); break;
        case 11: strcpy(resultado,"November"); break;
        case 12: strcpy(resultado,"December"); break;
        default: printf("ERRO: Mês não encontrado"); break;
    }

    return resultado;
}

char *converterIntParaString(int num){
    char *resultado = (char *)malloc(12 * sizeof(char));

    sprintf(resultado,"%d",num);

    return resultado;
}

char* formatarData(DATA data){
    char *dataFormatada = (char *)calloc(255 , sizeof(char));
    char *mes = converterNumeroParaMes(data.month);
    char *dia = converterIntParaString(data.day);
    char *ano = converterIntParaString(data.year);

    strcat(dataFormatada,mes);
    strcat(dataFormatada," ");
    strcat(dataFormatada,dia);
    strcat(dataFormatada,", ");
    strcat(dataFormatada,ano);

    free(mes);
    free(dia);
    free(ano);

    return dataFormatada;
}

char* formatarArray(char **array,size_t tamanho){
    char *resultado = (char *)calloc(255,sizeof(char));

    for(int i = 0; i < tamanho; i++){
        strcat(resultado,array[i]);
        if(i != tamanho -1)
            strcat(resultado,", ");
    }

    return resultado;
}

void exibir(PROGRAMA *p){
    char *dataAdicaoFormatada;

    bool temMes = (p->data_adicao.month != 0);
    bool temDia = (p->data_adicao.day != 0);
    bool temAno = (p->data_adicao.year != 0);

    if(temMes && temDia && temAno){
        dataAdicaoFormatada = formatarData(p->data_adicao);
    }else{
        dataAdicaoFormatada = (char *)calloc(5,sizeof(char));
        strcpy(dataAdicaoFormatada,"NaN");
    }

    char* elencoFormatado;
    if(p->elenco != NULL){
        elencoFormatado = formatarArray(p->elenco, p->numElenco);
    }else{
        elencoFormatado = (char *)calloc(5,sizeof(char));
        strcpy(elencoFormatado,"NaN");
    }
    
    char* generosFormatados;
    if(p->generos != NULL){
        generosFormatados = formatarArray(p->generos,p->numGeneros);
    }else{
        generosFormatados = (char *)calloc(5,sizeof(char));
        strcpy(generosFormatados,"NaN");
    }

    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           p->id,p->nome,p->categoria,p->diretor,elencoFormatado,
           p->pais,dataAdicaoFormatada, p->ano_lancamento, 
           p->classificacao, p->duracao, generosFormatados);

    free(dataAdicaoFormatada);
    free(generosFormatados);
    free(elencoFormatado);
}

char** separarAtributos(char* linha){
    int tamanho = strlen(linha);
    char **atributos = (char **)malloc(11 * sizeof(char *));
    int k = 0;
    int l = 0;
    for(int i = 0; i < 11; i++){
        atributos[i] = (char *)calloc(1024,sizeof(char));
        strcpy(atributos[i],"NaN");
    }
    for(int i = 0; i < tamanho && k < 11; i++){
        if(linha[i] != ','){
            if(linha[i] == '"'){
                i++;
                while(linha[i] != '"'){
                    atributos[k][l++] = linha[i++];
                }
            }else{
                atributos[k][l++] = linha[i];
            }
        }else{
            atributos[k][l] = '\0';
            l = 0;
            k++;
            while(linha[i + 1] == ','){
                atributos[k][l++] = 'N';
                atributos[k][l++] = 'a';
                atributos[k][l++] = 'N';
                atributos[k][l] = '\0';
                i++;
                if(k < 11)
                    k++;
                l = 0;
            }
        }
    }
    return atributos;
}

void definirId(PROGRAMA *p,char *atributo){
    size_t tamanho = strlen(atributo);
    p->id =(char *)malloc((tamanho + 1) * sizeof(char));
    strcpy(p->id,atributo);
}

void definirCategoria(PROGRAMA *p,char *atributo){
    size_t tamanho = strlen(atributo);
    p->categoria =(char *)malloc((tamanho + 1)* sizeof(char));
    strcpy(p->categoria,atributo);
}

void definirNome(PROGRAMA *p,char *atributo){
    size_t tamanho = strlen(atributo);
    p->nome =(char *)calloc((tamanho + 1) , sizeof(char));
    strcpy(p->nome,atributo);
}

void definirDiretor(PROGRAMA *p,char *atributo){
    size_t tamanho = strlen(atributo);
    p->diretor =(char *)malloc((tamanho + 1) * sizeof(char));
    strcpy(p->diretor,atributo);
}

void definirElenco(PROGRAMA *p, char *atributo){
    if(strcmp(atributo,"NaN") != 0 || strlen(atributo) != 0){
        int qtd = 1;
        int tamanho = strlen(atributo);

        for(int j = 0; j < tamanho; j++)
            if(atributo[j] == ',')
                qtd++;

        p->numElenco = qtd;

        p->elenco = (char **)calloc(qtd , sizeof(char*));
        for(int j = 0; j < qtd;j++){
            *(p->elenco + j) = (char *)calloc(tamanho , sizeof(char));
        }

        for(int j = 0,k = 0,l = 0; j < tamanho; j++){
            if(atributo[j] != ','){
                p->elenco[k][l++] = atributo[j];
            }else if(atributo[j] == ','){
                p->elenco[k++][l] = '\0';
                l = 0;
                if(atributo[j + 1] == ' '){
                    j++;
                }
            }
        }

        size_t s_tamanho = p->numElenco;
        for(int j = 0; j < s_tamanho - 1; j++){
            int menor = j;
            for(int k = j + 1; k < s_tamanho; k++){
                if(strcmp(p->elenco[k],p->elenco[menor]) < 0){
                    menor = k;
                }
            }
            char *temp = p->elenco[j];
            p->elenco[j] = p->elenco[menor];
            p->elenco[menor] = temp;
        }

    }else{
        p->numElenco = 0;
        p->elenco = NULL;
    }
}

void definirPais(PROGRAMA *p, char *atributo){
    size_t tamanho = strlen(atributo);
    p->pais =(char *)malloc((tamanho + 1) * sizeof(char));
    strcpy(p->pais,atributo);
}

void definirDataAdicao(PROGRAMA *p, char *atributo){
    if(strcmp(atributo,"NaN") != 0){
        int tamanho = strlen(atributo);
        char s_mes[tamanho];
        char s_dia[tamanho];
        char s_ano[tamanho];

        int k;
        for(int j = 0; j < tamanho; j++){
            if(atributo[j] != ' '){
                s_mes[j] = atributo[j];
            }else{
                s_mes[j] = '\0';
                k = j + 1;
                j = tamanho;
            }
        }
        for(int j = k,l = 0; j < tamanho; j++){
            if(atributo[j] != ','){
                s_dia[l++] = atributo[j];
            }else{
                s_dia[l] = '\0';
                k = j + 2;
                j = tamanho;
            }
        }
        for(int j = k,l = 0; j < tamanho; j++){
            s_ano[l++] = atributo[j];
            if(j == tamanho - 1)
                s_ano[l] = '\0';
        }

        p->data_adicao.month = converterMesParaNumero(s_mes);
        p->data_adicao.day = atoi(s_dia);
        p->data_adicao.year = atoi(s_ano);
    }else{
        p->data_adicao.month = 3;
        p->data_adicao.day = 1;
        p->data_adicao.year = 1900;
    }
}

void definirAnoLancamento(PROGRAMA *p, char *atributo){
    p->ano_lancamento = atoi(atributo);
}

void definirClassificacao(PROGRAMA *p, char *atributo){
    size_t tamanho = strlen(atributo);
    p->classificacao =(char *)malloc((tamanho + 1) * sizeof(char));
    strcpy(p->classificacao,atributo);
}

void definirDuracao(PROGRAMA *p, char *atributo){
    size_t tamanho = strlen(atributo);
    p->duracao =(char *)malloc((tamanho + 1) * sizeof(char));
    strcpy(p->duracao,atributo);
}

void definirGeneros(PROGRAMA *p, char *atributo){
    if(strcmp(atributo,"NaN") != 0){
        int qtd = 1;
        int tamanho = strlen(atributo);

        for(int j = 0; j < tamanho; j++)
            if(atributo[j] == ',')
                qtd++;

        p->numGeneros = qtd;

        p->generos = (char **)malloc(qtd * sizeof(char*));
        for(int j = 0; j < qtd;j++){
            *(p->generos + j) = (char *)malloc(tamanho * sizeof(char));
        }

        for(int j = 0,k = 0,l = 0; j < tamanho; j++){
            if(atributo[j] != ','){
                p->generos[k][l++] = atributo[j];
            }else if(atributo[j] == ','){
                p->generos[k++][l] = '\0';
                l = 0;
                if(atributo[j + 1] == ' '){
                    j++;
                }
            }
        }

        size_t s_tamanho = p->numGeneros;
        for(int j = 0; j < s_tamanho - 1; j++){
            int menor = j;
            for(int k = j + 1; k < s_tamanho; k++){
                if(strcmp(p->generos[k],p->generos[menor]) < 0){
                    menor = k;
                }
            }
            char *temp = p->generos[j];
            p->generos[j] = p->generos[menor];
            p->generos[menor] = temp;
        }

    }else{
        p->numGeneros = 0;
        p->generos = NULL;
    }
}

void carregarPrograma(PROGRAMA *p, char *linha){
    char **atributos = separarAtributos(linha);

    definirId(p, atributos[0]);
    definirCategoria(p, atributos[1]);
    definirNome(p, atributos[2]);
    definirDiretor(p,atributos[3]);
    definirElenco(p,atributos[4]);
    definirPais(p,atributos[5]);
    definirDataAdicao(p, atributos[6]);
    definirAnoLancamento(p, atributos[7]);
    definirClassificacao(p,atributos[8]);
    definirDuracao(p,atributos[9]);
    definirGeneros(p, atributos[10]);
    
    for(int i = 0; i < 11; i++){
        free(atributos[i]);
    }
    free(atributos);
}

void lerLinha(char *linha,int tamanhoMax, FILE *arquivo){
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: ponteiro de arquivo NULL passado para lerLinha().\n");
        exit(1);
    }

    if (fgets(linha, tamanhoMax, arquivo) == NULL) {
        fprintf(stderr, "Erro ao ler linha do arquivo ou fim do arquivo atingido.\n");
        exit(1);
    }
    size_t tamanho = strlen(linha);
    if(linha[tamanho - 1] == '\n')
        linha[tamanho - 1] = '\0';
}

void liberarPrograma(PROGRAMA *p){
    free(p->id);
    free(p->categoria);
    free(p->nome);
    free(p->diretor);
    free(p->pais);
    free(p->classificacao);
    free(p->duracao);
    if(p->elenco != NULL){
        for(int j = 0; j < p->numElenco; j++){
            free(*(p->elenco + j));
        }
        free(p->elenco);
    }
    if(p->generos != NULL){
        for(int j = 0; j < p->numGeneros; j++){
            free(*(p->generos + j));
        }
        free(p->generos);
    }
}

typedef struct NO{
    PROGRAMA *conteudo;
    struct NO *proximo;
}NO;

NO* criarNo(){
    NO *temp = (NO *)malloc(sizeof(NO));
    temp->conteudo = (PROGRAMA *)malloc(sizeof(PROGRAMA));
    temp->proximo = NULL;
    return temp;
}

NO* criarNoComPrograma(PROGRAMA programa){
    NO *temp = (NO *)malloc(sizeof(NO));
    temp->conteudo = (PROGRAMA *)malloc(sizeof(PROGRAMA));
    *(temp->conteudo) = copiarPrograma(programa);
    temp->proximo = NULL;
    return temp;
}

typedef struct{
    NO *topo;
}PILHA_PROGRAMAS;

PILHA_PROGRAMAS* criarPilha(){
    PILHA_PROGRAMAS *temp = (PILHA_PROGRAMAS *)malloc(sizeof(PILHA_PROGRAMAS));
    temp->topo = criarNo();
    return temp;
}

int obterTamanho(PILHA_PROGRAMAS *pilha){
    int contador = 0;
    NO *i;
    for(i = pilha->topo->proximo; i != NULL; i = i->proximo, contador++);
    return contador;
}

void adicionarPrograma(PILHA_PROGRAMAS *pilha, PROGRAMA programa){
    NO *temp = criarNoComPrograma(programa);
    temp->proximo = pilha->topo->proximo;
    pilha->topo->proximo = temp;
    temp = NULL;
}

PROGRAMA retirarPrograma(PILHA_PROGRAMAS *pilha){
    PROGRAMA resultado;

    if(pilha->topo->proximo == NULL){
        errx(1,"Erro ao remover\n");
    }else{
        NO *temp = pilha->topo->proximo;
        pilha->topo->proximo = pilha->topo->proximo->proximo;
        temp->proximo = NULL;
        resultado = copiarPrograma(*(temp->conteudo));
        free(temp);
    }

    return resultado;
}

void mostrarProgramasRestantes(PILHA_PROGRAMAS *pilha){
    NO *i = pilha->topo->proximo;
    int tamanho = obterTamanho(pilha);
    for(int j = tamanho - 1; j >= 0; j--, i = i->proximo){
        printf("[%d] ",j);
        exibir(i->conteudo);
    }
}

void carregarArquivo(PROGRAMA*);
void preencherPilhaInicial(PILHA_PROGRAMAS*,PROGRAMA*);
int obterIdPrograma();
int obterPosicao();
void processarOperacao(char*, PILHA_PROGRAMAS*, PROGRAMA*);

int main(){
    PROGRAMA *programas = (PROGRAMA *)calloc(1368,sizeof(PROGRAMA));

    carregarArquivo(programas);
    
    PILHA_PROGRAMAS *pilha_programas = criarPilha();

    preencherPilhaInicial(pilha_programas,programas);
    
    int qtdOperacoes;

    scanf("%d",&qtdOperacoes);
    getchar();

    for(int i = 0; i < qtdOperacoes; i++){
        char *operacao = (char *)malloc(255 * sizeof(char));

        scanf("%s",operacao);
        getchar();

        processarOperacao(operacao,pilha_programas,programas);

        free(operacao);
    }

    mostrarProgramasRestantes(pilha_programas);

    for(int i = 0; i < 1368; i++)
        liberarPrograma(programas + i);
    free(programas);

    return 0;
}

void carregarArquivo(PROGRAMA *programas){
    FILE *arquivo = fopen("/tmp/disneyplus.csv", "r");

    char *linha = (char *)malloc(1024*sizeof(char));

    while(fgetc(arquivo) != '\n');

    for(int i = 0; i < 1368; i++){
        lerLinha(linha, 1024,  arquivo);

        carregarPrograma((programas + i),linha);
    }

    free(linha);
    fclose(arquivo);
}

void preencherPilhaInicial(PILHA_PROGRAMAS *pilha,PROGRAMA *programas){
    char *entrada = (char *)malloc(255 * sizeof(char));
    scanf("%s",entrada);

    while(strcmp(entrada,"FIM") != 0){
        int id = atoi((entrada + 1));
        adicionarPrograma(pilha,  programas[--id]);
        scanf("%s",entrada);
    }
}

int obterIdPrograma(){
    char *id = (char *)malloc(255 * sizeof(char));

    scanf("%s",id);
    getchar();

    int resultado = atoi(id + 1);

    free(id);

    return resultado;
}

int obterPosicao(){
    int pos;
    scanf("%d",&pos);
    getchar();
    return pos;
}

void processarOperacao(char *operacao, PILHA_PROGRAMAS *pilha, PROGRAMA *programas){
    if(strcmp(operacao,"I") == 0){
        int id = obterIdPrograma();
        adicionarPrograma(pilha,programas[--id]);
    } else if(strcmp(operacao,"R") == 0){
        PROGRAMA programaRemovido = retirarPrograma(pilha);
        printf("(R) %s\n",programaRemovido.nome);
    }
}