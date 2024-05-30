#include <stdio.h>
#include <math.h>

int main()
{
  //entrada de dados
  float base, altura, perimetro, area, diagonal;
  printf("digite a base do retangulo\n");
  scanf("%f", &base);
  printf("digite a altura do retangulo\n");
  scanf("%f", &altura);
  
  //calculo do perimetro
  perimetro = base*2 + altura*2;

  //calculo da area
  area = base*altura;

  //calculo da diagonal
  diagonal = sqrt(pow(base, 2) + pow(altura, 2));

  //saida de dados
  printf("o perimetro é: %.2f", perimetro);
  printf("\na area é: %.2f", area);
  printf("\na diagonal é: %.2f", diagonal);
  
  return (0);
}