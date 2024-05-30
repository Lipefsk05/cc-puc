#include <stdio.h>

int main()
{
  int hr, mint;
  float min, hrmin;
//entrada de dados
  printf("Digite a hora no formato hr.min:\n");
  scanf("%f", &hrmin);
  
//calculo
hr=hrmin;
min=(hrmin-hr)*100;
hr*=60;
mint=min+hr;
  
//saida de dados
  printf("%.2f horas em minutos são: %i", hrmin, mint);
  // printf("\n%ihr")
  return 0;
}