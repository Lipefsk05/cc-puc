#include <stdio.h>

int main()
{
  float horasTr, horasTrM, salMinimo, salReceber, valHorasTr, salBruto, imp;

//entrada de dados
  printf("Digite o valor do salário minimo:\nR$");
  scanf("%f", &salMinimo);
  printf("\nDigite quantas horas você trabalha semanalmente\n");
  scanf("%f", &horasTr);

//calculos
horasTrM=horasTr*4;
valHorasTr=salMinimo/2;
salBruto=horasTrM*valHorasTr;
imp=salBruto*0.3;
salReceber=salBruto-imp;

//saida de dados
printf("\nVocê recebera um salário de: R$%.2f", salReceber);

return 0;
  
}