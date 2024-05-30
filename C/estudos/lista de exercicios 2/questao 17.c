#include <stdio.h>
#include <math.h>
int main()
{
  float saldo=0, cheque1, cheque2, dep;

//entrada de dados
  printf("Qual o valor do seu deposito?\nR$");
  scanf("%f", &dep);
  printf("\nDigite o valor do seu primeiro Cheque:\nR$");
  scanf("%f", &cheque1);
  printf("\nDigite o valor do seu segundo Cheque:\nR$");
  scanf("%f", &cheque2);

//calculo
  saldo=saldo+dep;
  cheque1=(cheque1+(cheque1*0.38));
  saldo=saldo-cheque1;
  cheque2=(cheque2+(cheque2*0.38));
  saldo=saldo-cheque2;

//saida de dados
  printf("\nSeu saldo atual é:\nR$%.2f", saldo);

return 0;
  
}