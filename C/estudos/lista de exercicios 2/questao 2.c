#include <stdio.h>

int main()
{
  float n1, n2, n3, sm, md;

//entrada de dados
  printf("Digite a primeira nota:\n");
  scanf("%f", &n1);
  printf("Digite a segunda nota:\n");
  scanf("%f", &n2);
  printf("Digite a terceira nota:\n");
  scanf("%f", &n3);

//calculo
  sm=n1+n2+n3;
  md=sm/2;

//saida de dados
  printf("\nA média das notas é: %.2f", md);

;}