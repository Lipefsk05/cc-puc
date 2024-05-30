#include <stdio.h>

int main()
{
  float degr, alt, numDegr;

//entrada de dados
  printf("Informe a altura de cada degrau:\n");
  scanf("%f", &degr);
  printf("Informe a altura você deseja chegar:\n");
  scanf("%f", &alt);

//calculos
  degr=degr/100;
  numDegr=alt/degr;

//saida de dados
  printf("Você precisa subir %.0f degraus para alcançar a altura desejada", numDegr);


}