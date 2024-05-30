#include <stdio.h>

int main()
{
  int nasc, idad, ano, anocinc;

//entrada de dados
  printf("Digite seu ano de nascimento\n");
  scanf("%i", &nasc);
  printf("\nDigite o ano atual\n");
  scanf("%i", &ano);
//calculo
  idad=ano-nasc;
  anocinc=2050-idad-2000;

//saida de dados
  printf("\nAtualmente você tem %i anos", idad);
  printf("\nEm 2050 você tera %i anos de idade", anocinc);

  return 0;
  
}
