#include <stdio.h>
#include <math.h>

int main(void)
{
  float num1, num2, resp1, resp2;

//entrada de dados 1
  printf("Digite o primeiro numero:");
  scanf("\n%f", &num1);
  if(num1>0)
  {
    
//entrada de dados 2
    printf("Digite o segundo numero:");
    scanf("%f", &num2);
    if(num2>0)
    {

//se as duas entradas forem corretas, ocorre o calculo
    resp1=pow(num1,num2);
    resp2=pow(num2,num1);
      
//saida de dados - correta
    printf("\nO resultado de %.0f ^ %.0f é %.2f\n", num1, num2, resp1);
    printf("\nO resultado de %.0f ^ %.0f é %.2f", num2, num1, resp2);
    }

//saida de dados incorreta referente a entrada 2
    else
    {
      printf("por favor digite um numero positivo maior que 0.");
    }
  }

//saida de dados incorreta referente a entrada 1
  else
  {
    printf("por favor digite um numero positivo maior que 0.");
  }

  return 0;
}