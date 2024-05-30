
#include <stdio.h>

int main() 
{
  float salin, salfin, aum;

//entrada de dados
  printf("Digite seu salario:\n");
  scanf("%f", &salin);

//calculo
aum=salin*0.75;
salfin=salin+aum;

//saida de dados
  printf("\nParabéns, você recebeu um aumento de 25%%!!!\nAgora seu salário é: R$%.2f", salfin);

  return 0;
}