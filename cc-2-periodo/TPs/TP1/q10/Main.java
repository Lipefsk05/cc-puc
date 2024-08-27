import java.util.Scanner;

public class Main{

    static boolean palin(int i, char[] pa, int tam){
        
        if(i >= tam)
            return true; 
        else if(pa[i] == pa[tam])
            return palin(i + 1, pa, tam - 1);
        else
            return false;


    }
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);

        String palavra;

        do{
            palavra = sc.nextLine();
            
            if(!palavra.equals("FIM")){

                int tam = ((palavra.length() - 1));
                char[] pa = palavra.toCharArray();

                if(palin(0, pa, tam))
                System.out.println("SIM");
                else
                System.out.println("NAO");
            }
        } 
        while(!palavra.equals("FIM"));

        sc.close();
    }
}