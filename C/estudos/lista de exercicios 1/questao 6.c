#include <stdio.h>
#include <math.h>

int main ()
{
  float term1, termN, num, raz;

  //entrada de dados
  printf("digite o primeiro termo da PA\n");
  scanf("%f,", &term1);
  printf("digite a razão da PA\n");
  scanf("%f", &raz);

  //calculo do décimo termo
  termN=term1+(10-1)*raz;

  //saida de dados
  printf("o décimo termo da PA é:%.2f\n",termN);

  return 0;
}