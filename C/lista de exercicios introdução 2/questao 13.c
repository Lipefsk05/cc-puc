#include <stdio.h>

int main()
{
  float pe, jard, pol, milh;

//entrada de dados
  printf("Digite a distancia em pés:\n");
  scanf("\n%f", &pe);

//calculo
  pol=pe/12;
  jard=pe*3;
  milh=jard*1.760;

//saida de dados
  printf("\na converção de %.2f pés para\n\npolegadas é:%.2f\njardas é:%.2f\nmilhas é:%.2f",pe, pol, jard, milh);

  return 0;

}
  