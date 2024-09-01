import java.util.*;

public class Main {

  static char[] atribuirValor(String str){
    char[] vetor = new char[4];

    if (str.charAt(0) == '2') {
      vetor[0] = str.charAt(1);
      vetor[1] = str.charAt(2);
    }
    else{
      vetor[0] = str.charAt(0);
      vetor[1] = str.charAt(1);
      vetor[2] = str.charAt(2);
    }

    return vetor; 

  }

  static String dividir(String str){
    String dividir = "";
    if (str.charAt(0) == '2'){
        dividir = str.substring(3);
      } else {
        dividir = str.substring(4);
      }

    return dividir;
  }

  public static void main(String[] args) {
    // Scanner sc = new Scanner(System.in);
    char[] vetor = new char[4];
    String divStr = "";
    
    String str = "2 0 0 and(not(A) , not(B))";
    str = str.replaceAll(" ", "");
    
    vetor = atribuirValor(str); 

    divStr = dividir(str);

    System.out.println(divStr);

  }
}


/*
  Primeiro Passo +
  Segundo Passo {
    
  
  }

*/













/*
 * 200and(not(A),not(B))
 * 
 * 
 * 
 * 
 * 
 */

/*
 * 01º Verificar Primeiro Número da String
 * Primeiro Número: 2 ou 3
 * Se for 2: Terá duas variáveis A e B
 * Se for 3: Terá três variáveis A, B e C
 * Se for 0: Terminar Programa
 * 
 * Segundo, Verificar próxima string:
 * Se for AND:
 * AND
 * OR
 * NOT
 * VALOR A ou B ou C
 * 
 * 
 * 
 * Se for NOT:
 * Se for OR:
 * 
 * 
 * 
 */
  