#include <stdio.h>
#include <math.h>
  
int main()
{
  float ang, alt, medEsc, rad; 
  
//entrada de dados
  printf("Digite o valor do angulo que a escada forma com o chão:\n");
  scanf("%f", &ang);
  printf("Digite a altura que a escada está enconstada na parede:\n");
  scanf("%f", &alt);  

//calculo
  rad=ang*(3.14/180);
  medEsc=alt/sin(rad);

//saida de dados
  printf("O valor da escada é:\n%.2f", medEsc);
  
  return 0;
}