  #include <stdio.h>

  int main() {
      int velMax, velMotorista;
      printf("Digite a velocidade máxima permitida (em km/h): ");
      scanf("%d", &velMax);

      printf("Digite a velocidade do motorista (em km/h): ");
      scanf("%d", &velMotorista);

      if (velMotorista <= velMax) {
          printf("Motorista respeitou a lei.\n");
      } else {
          int diferencaVel = velMotorista - velMax;
          if (diferencaVel <= 10) {
              printf("Multa a ser cobrada: R$ 50\n");
          } else if (diferencaVel <= 30) {
              printf("Multa a ser cobrada: R$ 100\n");
          } else {
              printf("Multa a ser cobrada: R$ 200\n");
          }
      }

      return 0;
  }
