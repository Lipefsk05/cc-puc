#include <stdio.h>

int main()
{
  float numr, denom, resul;
  
//entrada de dados
  printf("Digite o Numerador:\n");
  scanf("%f", &numr);
  printf("Digite o Denominador:\n");
  scanf("%f", &denom);

//calculo
resul=numr/denom;
  
//saida de dados
  printf("O resultado em decimal é:%.2f", resul);

  return 0;
  
}