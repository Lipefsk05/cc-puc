#include <stdio.h>
#include <math.h>

int main()
{
  float num, pFrac;
  int arred;
  int pInt=0;
//entrada de dados
  printf("Insira um numero real:\n");
  scanf("%f", &num);

//calculo
  pInt+=num;
  pFrac=num-pInt;
  arred=round(num);
//saida de dados
  printf("\nA parte inteira desse numero é: %.i", pInt);
  printf("\nA parte fracionaria desse numero é: %.1f", pFrac);
  printf("\nEsse numero arrendondado é: %i", arred);
  
  return 0;
}