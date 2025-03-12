import java.util.*;

public class Main{

    static int contagem(String fr){

        char[] frCont = fr.toCharArray();    
        int cont = 1;

        for(int i = 0 ; i < frCont.length ; i++){
            if(frCont[i] == ' ')
                cont++;
        }
        
        return cont;
    }
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            String fr = sc.nextLine();
            
            while (!fr.equals("FIM")) {
                
                System.out.println(contagem(fr));
                
                fr = sc.nextLine();
            }
    }
    
}