#include <stdio.h>

int main()
{
  int num, acumulador=0;

  printf("digite um numero de 3 digitos:");
  scanf("%d",&num);
  
  //separação da centena
  acumulador = acumulador+num/100;
  num = num%100;

  //separação de dezena
  acumulador = acumulador+(num/10)*10;
  num = num%10;
  
  //separação da unidade
  acumulador = acumulador+num*100;

  //resposta
  printf("\nNúmero invertido: %d", acumulador);

  return (0);
}
