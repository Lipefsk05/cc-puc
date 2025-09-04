import java.util.*;

public class Main{

    static int substring(String p){
        
        char[] pChar = p.toCharArray();
        int var = 0;

        for(int i = 0 ; i < pChar.length ; i++){        
            
            if (pChar[i] != 0) {
                
                var++;

                for(int j = i+1 ; j < pChar.length ; j++){
                    
                    if(pChar[j] != 0){
                        if(pChar[j] == pChar[i])
                            pChar[j] = 0;
                    }
                    
                }
                pChar[i] = 0;
            }
        }

        return var;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String p = sc.nextLine();

        while (!p.equals("FIM")) { 

            System.out.println(substring(p));
        
            p = sc.nextLine();

        }
    }
}