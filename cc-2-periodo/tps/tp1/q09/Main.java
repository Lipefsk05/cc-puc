import java.util.*;

class Main {

    static boolean verAnag(String p){
        
        char[] pArr = p.toCharArray();
        
        if(pArr.length % 2 > 0 ){

            int tam =  (p.length() - 3) / 2;
            char[] s1 = new char[tam];
            char[] s2 = new char[tam];
            int matches = 0;

            for(int i = 0, j = tam + 3 ; i < tam ; i ++, j++){
                s1[i] = pArr[i];
                s2[i] = pArr[j];
            }

            // for(char l : s1)
            //     System.out.print(l);
        
            // System.out.print(" - ");

            // for(char l : s2)
            //     System.out.print(l);

            // System.out.println("");

            for(int i = 0 ; i < tam ; i++){
                for(int j = 0 ; j < tam ; j++){
                    if(s1[i] == s2[j]){
                        matches += 1;
                        s2[j] = 0;
                    }
                    
                }
            }

            // System.out.println(matches);

            if(matches == tam)
                return true;
            else
                return false;
        }
        
        return false;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String p = sc.nextLine();

        
        while (!p.equals("FIM")) {
            
            p = p.toLowerCase();

            System.out.println(verAnag(p) ? "SIM" : "N\u00C3O");

            p = sc.nextLine();
            
        }
    }     
}