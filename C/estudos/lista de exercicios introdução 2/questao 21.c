#include <stdio.h>
#include <math.h>

int main()
{
  float distE, tamE, altQ;

//entrada de dados
  
  printf("Informe a altura em que deseja o quadro:\n");
  scanf("%f", &altQ);
  printf("\nInforme um valor mais alto que o quadro para o tamanho escada:\n");
  scanf("%f", &tamE);
  
//validação de dados
  while(tamE<altQ)
  {
    printf("\nInforme um valor mais alto que o quadro para o tamanho escada:\n");
    scanf("%f", &tamE);
  }

//calculos
distE=sqrt(pow(2,tamE)-pow(2,altQ));
  
//saida de dados

  printf("\nA altura que a escada deve estar da parede é: %.2f", distE);
  
  return 0;
}