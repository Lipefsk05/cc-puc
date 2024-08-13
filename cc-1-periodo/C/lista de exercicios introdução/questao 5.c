#include <stdio.h>
#include <math.h>

int main ()
{
  float cat1, cat2, hip;
  
  //entrada de dados
  printf("escreva o valor do primeiro cateto:\n");
  scanf("%f", &cat1);
  printf("escreva o valor do segundo cateto:\n");
  scanf("%f", &cat2);

  //calculo da hipotenusa
  hip=sqrt(pow(cat1,2)+pow(cat2,2));

  //saida de dados
  printf("o valor da hipotenusa é:%.2f", hip);
  return 0;
  
}
