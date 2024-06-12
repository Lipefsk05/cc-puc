#include <stdio.h>

int main()
{
  float salBase, salRec, imp;

//entrada de dados
  printf("Digite seu salário:\nR$");
  scanf("%f", &salBase);

//cálculo
  imp=salBase*0.1;
  salRec=salBase+50-imp;

//saída de dados
  printf("Seu salário com a gratificação de R$50 e 10%% de imposto\né de R$%.2f", salRec);

  return 0;
  
}
