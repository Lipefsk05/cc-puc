#include <stdio.h>

int main()
{
  float salBase, salRec, Grat, Imp;

//entrada de dados
  printf("Digite o salário base:\nR$");
  scanf("%f", &salBase);

//calculo
  Grat=salBase*0.05;
  Imp=salBase*0.07;
  salRec=salBase+Grat-Imp;

//saida de dados
  printf("\nO salário a receber com a gratificação e o imposto é R$%.2f", salRec);

  return 0;
  
}
