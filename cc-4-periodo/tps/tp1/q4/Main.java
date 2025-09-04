import java.util.*;

class Main {

    static String alterar(String s, char c1, char c2){

        char[] sChar = s.toCharArray();

        for(int i = 0 ; i < s.length() ; i++){
            
            if(sChar[i] == c1)
                sChar[i] = c2;
        }

        return new String(sChar);
    }
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        Random gerador = new Random();
        gerador.setSeed(4);
        
        
        String s = sc.nextLine();

        while (!s.equals("FIM")) {


            char c1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
            char c2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26)); 

            s = alterar(s, c1, c2);
            System.out.println(s);
            
            s = sc.nextLine();
        }



    }     
}