#include <stdio.h>

int main(void)
{
  float n1, n2, n3, p1, p2, p3, sm, md, pt, nt;
  
//entrada de dados
  printf("Digite a primeira nota:\n");
  scanf("%f", &n1);
  printf("Digite o peso da primeira nota:\n");
  scanf("%f", &p1);
  printf("Digite a segunda nota:\n");
  scanf("%f", &n2);
  printf("Digite o peso da segunda nota:\n");
  scanf("%f", &p2);
  printf("Digite a terceira nota:\n");
  scanf("%f", &n3);
  printf("Digite o peso da terceira nota:\n");
  scanf("%f", &p3);

//calculo
  pt=p1+p2+p3;
  nt=(n1*p1)+(n2*p2)+(n3*p3);
  md=nt/pt;

//saida de dados
  printf("\nA media total ponderada é %.2f", md);
  
}


