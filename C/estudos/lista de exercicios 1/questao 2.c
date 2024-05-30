#include <stdio.h>

int main()
{
  double salarioM, kiloW, kiloW1, pagar, desc;

  //entrada de dados
  printf("Digite o valor do salario minimo:\n");
  scanf("%lf", &salarioM);
  printf("Digite a quatidade gasta de Kilowatts:\n");
  scanf("%lf", &kiloW);

  //quanto vale 1 KW
  salarioM = salarioM/7;
  salarioM = salarioM/100;
  kiloW1 = salarioM;
  
  //quanto a pagar
  pagar = kiloW*kiloW1;

  //aplicando o desconto
  desc = pagar*0.9;
  
  printf("O valor do killowatt é: %.2lf", kiloW1);
  printf("\no valor a ser pago é: %.2lf", pagar);
  printf("\no valor com desconto é %.2lf", desc);

  
  return (0);
}









