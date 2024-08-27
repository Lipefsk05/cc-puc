import java.util.Scanner;

public class Main{

static String cfm(int cont, char[] cifrado, int tam){
    
    if(!(cont == 3)){

        for(int i = 0; i < tam ; i++){

            if(cifrado[i] == '\uFFFD'){
                cifrado[i] = '\uFFFD';
            }
            else{
                int j = cifrado[i]+1;
                if(j == 127)
                j = 32;
                else
                if(j == 128)
                j = 33;
                else
                if(j == 129)
                j = 34;
                cifrado[i] = (char) j;
            }
        }
        return cfm(cont + 1, cifrado, tam);
    }
    return new String(cifrado);
}
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        String frase;

        
        do{
            frase = sc.nextLine();
            int tam = frase.length();
            char[] cifrado = frase.toCharArray();

            if(!frase.equals("FIM"))
            System.out.println(cfm(0, cifrado, tam));
        }
        while(!frase.equals("FIM"));

        sc.close();
        // int x = '�';
        // System.out.println(x);
    }
}