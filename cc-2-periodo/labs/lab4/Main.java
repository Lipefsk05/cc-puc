import java.util.Scanner;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int tam;
        int div;

        do {
            tam = sc.nextInt();
            div = sc.nextInt();

            int[] vector = new int[tam];

            if (tam != 0 && div != 0) {

                //-----------------------------------------------------------------------------------
                // ATRIBUIR AO VETOR
                for (int i = 0; i < tam; i++) {
                    vector[i] = sc.nextInt();
                }

                //-----------------------------------------------------------------------------------
                // ORDENAR POR MODULO
                for (int i = 1; i < tam; i++) {

                    int tmp = vector[i];
                    int j = i - 1;

                    while ((j >= 0) && (vector[j] % div) > (tmp % div)) {

                        // Verifica se os dois são iguais
                        if ((vector[j] % div) == (tmp % div)) {

                            // Verifica se os dois são ímpares, caso seja, troca pelo maior
                            if ((vector[j] % 2 != 0) && (tmp % 2 != 0)) {
                                if (vector[j] < tmp) { // Troca pelo maior ímpar
                                    vector[j + 1] = vector[j];
                                    vector[j] = tmp;
                                }
                            }

                            // Verifica se os dois são pares, caso seja, troca pelo menor
                            else if ((vector[j] % 2 == 0) && (tmp % 2 == 0)) {
                                if (vector[j] > tmp) { // Troca pelo menor par
                                    vector[j + 1] = vector[j];
                                    vector[j] = tmp;
                                }
                            }

                        } else {
                            vector[j + 1] = vector[j]; // Move o valor atual
                        }
                        j--;
                    }
                    vector[j + 1] = tmp; // Insere o valor atual na posição correta
                }

                // Exibir tamanho e divisor
                System.out.println(tam + " " + div);

                // Exibir o vetor ordenado
                for (int i = 0; i < tam; i++) {
                    System.out.println(vector[i]);
                }
            }
        } while (tam != 0 && div != 0);
    }
}
