#include <stdio.h>
#include <math.h>
#define pi 3.1415

int main()

{
 float area, raio;
  
//entrada de dados
  printf("Digite o raio do cículo:\n");
  scanf("%f", &raio);

//calculo
area=pi*pow(raio,2);

//saida de dados
  printf("\nA area do circulo é: %.1f", area);

  return 0;
  
}