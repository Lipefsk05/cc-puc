import java.util.Scanner;

public class palindromo{

    static boolean palin(String palavra){
        
        int tam = ((palavra.length())-1);
        int j = tam;

        char[] pa = palavra.toCharArray();

        for(int i = 0 ; i <=tam/2 ; i++){
            if(pa[i] != pa[j-i])
                return false;
        }
        
        return true;

    }
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);

        String palavra;

        do{
            palavra = sc.nextLine();
            
            if(!palavra.equals("FIM")){

                if(palin(palavra))
                System.out.println("SIM");
                else
                System.out.println("NAO");
            }
            } 
            while(!palavra.equals("FIM"));
        }

}