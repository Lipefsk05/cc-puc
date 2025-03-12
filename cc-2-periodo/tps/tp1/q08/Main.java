import java.util.*;

class Main {

    static int inverter(String p){
        
        char[] pInv = new char[p.length()];
        int j = 0;

        for(int i = 0 ; i < p.length() ; i++){
            
            j += p.charAt(i) - '0'; 
        }

        return j;
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

