#include <stdio.h>
#include <math.h>
#define pi 3.14
 //const float pi=3.14; (outra ooção do define)

int main ()
{
  float raio, perimetro, area;
  
  // entrada de dados
  printf("digite o raio do circulo:\n");
  scanf("%f", &raio);
 
  // calculo do perimetro
  perimetro = 2*pi*raio;

  // calculo da area
  area = pi*pow(raio,2);

  // saida de dados
  printf("a area do circulo é: %.2f\n", area);
  printf("o perimetro do circulo é: %.2f", perimetro);
  return (0);
  
}