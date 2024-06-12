#include <stdio.h>

int main ()
{
  int a, b, c, d, resp;

//entrada de dados
  printf("Digite o valor de a:\n");
  scanf("%d", &a);
  printf("Digite o valor de b:\n");
  scanf("%d", &b);
  printf("Digite o valor de c:\n");
  scanf("%d", &c);
  printf("Digite o valor de d:\n");
  scanf("%d", &d);
  
//calculos
  resp=a+b+c+d;

//saida de dados
  printf("\nA soma dos valores é: %d", resp);

  return 0;
}