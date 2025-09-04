import java.util.*;

class Main{

    static String inverter(String s){
        
        char[] invS = new char[s.length()];

        for(int i = 0, j = s.length() - 1 ; i < s.length() ; i++, j--){
            invS[i] = s.charAt(j); 
        }

        return new String(invS);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String s = sc.nextLine();

        while (!s.equals("FIM")) {
            System.out.println(inverter(s));        
            s = sc.nextLine();
        }
    }
}