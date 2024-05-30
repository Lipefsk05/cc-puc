#include <stdio.h>
#include <math.h>

int main ()
{
  int A, B, var;

//entrada de dados
  printf("Digite um valor para A\n");
  scanf("%d", &A);
  printf("Digite um valor para B\n");
  scanf("%d", &B);

//inversão dos valores
  var=B;
  B=A;
  A=var;

//saida de dados
  printf("O novo valor de A é:%d\n", A);
  printf("O novo valor de B é:%d", B);
  
  return 0;
  
}