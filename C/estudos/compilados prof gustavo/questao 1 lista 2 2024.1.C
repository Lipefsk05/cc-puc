#include <stdio.h>
#include <string.h>

int main ()
{
  int pos=0, neg=0, zero=0, num;

  printf("Informe uma sequência numérica para ser analizada. Digite 'FIM' para encerrar.\n");

//leitura de dados
  char leitura[100];
  do
  {
  scanf("%s", leitura);
  if(strcmp(leitura,"FIM")==0)
    {
    break;
    }

//contagem de individuos
  if (sscanf(leitura,"%i", &num))
    {
      if(num>0)
      {
        pos++;
      }
      else if(num<0)
      {
        neg++;
      }
      else
      {
        zero++;
      }
    }
  }
  while(1);
  int t=pos+neg+zero;
//saida
printf("\nPositivos:%i\nNegativos:%i\nZeros:%i\n", pos, neg, zero);
printf("\n%% positivo:%.1f\n %% negativo:%.1f\n%% Zeros:%.1f\n", (float) pos/t*100, (float) neg/t*100, (float) zero/t*100);
  
  return 0;
}