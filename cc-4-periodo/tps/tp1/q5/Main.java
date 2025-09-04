import java.util.*;

class Main {

    static Boolean isVog(String s){
        
        for(int i = 0 ; i < s.length() ; i++){

            String vog = "aeiou";

            char c = s.charAt(i);

            if(!vog.contains(c + ""))
                return false;
        }

        return true;
    }    

    static Boolean isCon(String s){
        
        for(int i = 0 ; i < s.length() ; i++){

            String con = "bcdfghjklmnpqrstvwxyz";

            char c = s.charAt(i);

            if(!con.contains(c + ""))
                return false;
        }

        return true;
    }    

    static Boolean isInt(String s){
        return s.matches("\\d+");
    }
    
    static Boolean isRea(String s){
        return s.matches("\\d+[.,]\\d+") || s.matches("\\d+[.,]") || s.matches("[.,]\\d+");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        boolean v;
        String s = sc.nextLine();
        s.toLowerCase();

        while (!s.equals("FIM")) {
            
            System.out.print(isVog(s) ? "SIM " : "NAO ");
            System.out.print(isCon(s) ? "SIM " : "NAO ");
            System.out.print(isInt(s) ? "SIM " : "NAO ");
            System.out.println(isRea(s) ? "SIM" : "NAO");

            s = sc.nextLine();
            s.toLowerCase();
        }
        

    }
     
}