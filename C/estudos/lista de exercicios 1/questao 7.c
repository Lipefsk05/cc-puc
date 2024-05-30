#include <stdio.h>
#include <math.h>

int main()
{
  float raz, term1, termN;

  //entrada de dados
  printf("Digite o primeiro termo da PG:\n");
  scanf("%f", &term1);
  printf("Digite a razão da PG\n");
  scanf("%f", &raz);

  //calculo
  termN=term1*pow(raz,(5-1));

  //saida de dados
  printf("O décimo quinto da PG é:%.2f\n", termN);
  
  return 0;
    
}