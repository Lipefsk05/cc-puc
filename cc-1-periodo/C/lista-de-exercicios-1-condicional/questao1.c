#include <stdio.h>

int main() {

  int n, m;

  scanf("%i", &n);
  scanf("%i", &m);

  if(n<m){
    printf("\n%i", m);
  }
  else{
    printf("\n%i", n);
  }
  return 0;
}