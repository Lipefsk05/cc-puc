#include <stdio.h>
#include <math.h>

int main()

{
  float val, nquadr, ncubo, nraquad, nracub;

//entrada de dados
  printf("Digite um numero positivo maior que zero:\n");
  scanf("%f", &val);

//calculos
  if (val>0)
  {
    nquadr=pow(val,2);
    ncubo=pow(val,3);
    nraquad=sqrt(val);
    nracub=cbrt(val);

//saida de dados - correto
    printf("\nO numero ao quadrado é: %.2f\n", nquadr);
    printf("\nO numero ao cubo é: %.2f\n", ncubo);
    printf("\nA raiz quadrada do numero é: %.2f\n", nraquad);
    printf("\nA raiz cubica do numero é: %.2f\n", nracub);
  }
//saida de dados - incorreto
  else
  {
    printf("\nNumero invalido, por favor digite um numero positivo\nmaior que zero");
  }

  return 0;

}