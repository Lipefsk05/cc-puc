#include <stdio.h>

int main() {

  int m, n, soma;

  scanf("%i", &n);
  scanf("%i", &m);

  soma=m+n;

  if(soma>=10){
    soma+=5;
    printf("%i", soma);
  }
  else{
    soma+=7;
    printf("%i", soma);
  }

  return 0;
}