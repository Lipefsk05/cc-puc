#include <stdio.h>

int main()
{
  float pesoKg, rGato1, rGato2, pesoFin;

//entrada de dados
  printf("Digite o peso em quilogramas do saco de ração:\n");
  scanf("%f", &pesoKg);
  printf("Digite quantas gramas come o primeiro gato:\n");
  scanf("%f", &rGato1);
  printf("Digite quantas gramas come o segundo gato:\n");
  scanf("%f", &rGato2);

//calculo
  rGato1=(rGato1/1000)*5;
  rGato2=(rGato2/1000)*5;
  pesoFin=pesoKg-(rGato1+rGato2);

//saida de dados
  printf("\nApós 5 dias sobrou %.1fkg no saco de ração. ", pesoFin);

  return 0;
  
}