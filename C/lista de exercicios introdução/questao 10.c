#include <stdio.h>
#include <math.h>

int main() 
{
  float hora, min, hm, mm;

  //entrada de dados
  printf("Digite a hora atual no formato hora minuto\n");
  scanf("%f %f", &hora, &min);
  
  //calculo do tempo
  hm=hora*60;
  mm=hm+min;
  
  //saida de dados
  printf("Ja se passaram %.0f minutos des de o inicio do dia",mm);

  return 0;
}