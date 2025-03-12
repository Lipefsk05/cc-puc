import java.util.*;

class Main {

    static String inverter(String p){
        
        char[] pInv = new char[p.length()];
        int j = p.length() - 1; 

        for(int i = 0 ; i < p.length() ; i++, j--){
            pInv[i] = p.charAt(j); 
        }

        return new String(pInv);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String p = sc.nextLine();

        while (!p.equals("FIM")) {
            
            System.out.println(inverter(p));
            p = sc.nextLine();
            
        }
    }     
}

