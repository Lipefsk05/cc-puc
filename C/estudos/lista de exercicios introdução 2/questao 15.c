#include <stdio.h>

int main()

{
  float precFab, percLuc, percImp, lucro, imp, precFin;

//entrada de dados
  printf("Digite o preço de fabrica do veiculo:\n");
  scanf("%f", &precFab);
  printf("Escreva o percentual de lucro da venda do veiculo:\n");
  scanf("%f", &percLuc);
  printf("Escreva o percentual de impostos:\n");
  scanf("%f", &percImp);

//calculos

  lucro=precFab*(percLuc/100);
  imp=precFab*(percImp/100);
  precFin=precFab+lucro-imp;

//saida de calculo

  printf("\nO lucro da venda foi: R$%.2f\n",lucro);
  printf("\nO valor do imposto foi: R$%.2f\n",imp);
  printf("\nO valor total da venda foi: R$%.2f\n",precFin);

  return 0;
  
}