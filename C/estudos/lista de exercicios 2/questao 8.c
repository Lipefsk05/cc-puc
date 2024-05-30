#include <stdio.h>

int main()

{
  float dpos, taxJuros, rend, valorTot;

//entrada de dados
  printf("Qual valor você deseja depositar?\nR$");
  scanf("%f", &dpos);
  printf("Digite a taxa de juros em %%\n");
  scanf("%f", &taxJuros);

//calculo
  rend=dpos*(taxJuros/100);
  valorTot=dpos+rend;

//saida de dados
  printf("\nSua renda foi de: R$%.2f", rend);
  printf("\nO valor total é de: R$%.2f", valorTot);
  
  return 0;
}