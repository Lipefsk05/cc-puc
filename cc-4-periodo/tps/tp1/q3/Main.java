import java.util.*;


public class Main {

    static String cifrar(String s){

        char[] sChar = s.toCharArray();

        for(int i = 0 ; i < s.length() ; i++){

            if(!(sChar[i] == '\uFFFD')){

                int n = sChar[i];
                n += 3;

                if(n > 127){

                    n -= 96;
                    sChar[i] = (char) n;
                }
                else{
                    sChar[i] = (char) n;
                }
            }
        }

        return new String(sChar);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String s = sc.nextLine();
    
        while (!s.equals("FIM")) {
            
            s = cifrar(s);
            System.out.println(s);

            s = sc.nextLine();

        }
    }
}
