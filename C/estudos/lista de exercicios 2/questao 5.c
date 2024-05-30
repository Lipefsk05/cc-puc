#include <stdio.h>

int main() {
  float sal, per, perDeci, aum, nsal;

  // entrada de dados
  printf("Digite seu salário:\n");
  scanf("%f", &sal);
  printf("Digite o percentual de aumento:\n");
  scanf("%f", &per);

  // calculo
  perDeci=(per/100)+1;
  nsal=sal*perDeci;
  aum=nsal-sal;

  // saida de dados
  printf("\n O seu aumento foi de: R$%.2f", aum);
  printf("\n O seu novo salário é: R$%.2f", nsal);

  return 0;
}