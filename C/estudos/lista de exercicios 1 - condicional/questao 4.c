#include <stdio.h>

int main() {

  int nota;
  
  printf("Informe sua nota\n");
  scanf("%i", &nota);
  printf("\n");
  
  if(nota>=8 && nota<=10){
    printf("Otimo");
  }
  else if(nota>=7 && nota<8){
    printf("Bom");
  }
  else if(nota>=5 && nota<7){
    printf("Regular");
  }
  else{
    printf("Insatisfatorio");
  }
  return 0;
}