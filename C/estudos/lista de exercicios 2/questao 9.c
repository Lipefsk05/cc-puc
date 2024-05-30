#include <stdio.h>

int main()
{
  float base, altura, area;

//entrada de dados
  printf("Informe a base do triangulo:\n");
  scanf("%f", &base);
  printf("Informe a altura do triangulo:\n");
  scanf("%f", &altura);

//calculo
  area=(base*altura)/2;

//saida de dados

  printf("\nA area do triangulo é: %.1f", area);

  return 0;
  
}