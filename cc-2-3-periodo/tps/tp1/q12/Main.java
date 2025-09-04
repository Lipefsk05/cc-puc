import java.util.*;


class Main {

    static int verSize(String pass){

        if(pass.length() >= 8){
            return 1;
        }

        return 0;
    }

    static int verUpp(String pass){
        char[] p = pass.toCharArray();
        
        for (char c : p) {

            if (c >= 65 && c <= 90){
                return 1;
            }
        }
        
        return 0;
    }
    
    static int verLow(String pass){

        char[] p = pass.toCharArray();
        
        for (char c : p) {
            
            if (c >= 97 && c <= 122){
                return 1;
            }
        }
        
        return 0;
    }
    
    static int verNum(String pass){
        
        char[] p = pass.toCharArray();
        
        for (char c : p) {
            
            if (c >= 48 && c <= 57){
                return 1;
            }
        }
        
        return 0;
    }
    
    static int verChar(String pass){
    
        char[] p = pass.toCharArray();
    
        for (char c : p) {
    
            if (c >= 33 && c <= 47 || c >= 58 && c <= 64 || c>= 91 && c<= 96 || c>= 123 && c<= 127){
                return 1;
            }
        }
        
        return 0;
    }
    public static void main(String[] args){
        
        Scanner sc = new Scanner(System.in);
        String pass = sc.nextLine();
        
        while (!pass.equals("FIM")) {
            
            int matches = 0;
            
            matches += verSize(pass);
            matches += verUpp(pass);
            matches += verLow(pass);
            matches += verNum(pass);
            matches += verChar(pass);
            
            System.out.println(matches == 5 ? "SIM" : "NAO");
        
            pass = sc.nextLine();
        }
    }     
}
