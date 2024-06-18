#include <stdio.h>

int main(void) {
  int anoN, anoA=2024, idade;
  char conf;

  printf("digite o ano em que voce nasceu:\n");
  scanf("%i", &anoN);
  
  printf("\nvoce ja fez aniversario este ano? S/N\n");
  scanf(" %c", &conf);
  
  idade=anoA-anoN;
  
  if(conf=='S'){
  printf("voce tem %i anos de idade\n", idade);  
  }
  else{
    idade--;
    printf("voce tem %i anos de idade\n", idade);
  }

  if(idade>=18){
    printf("voce ja pode tirar carteira");
  }
  else{
    printf("voce nao pode tirar carteira");
  }

  
  return 0;
}