import java.util.*;

class Main{

    static boolean isAna(String s){
        char[] c = s.toCharArray();

        int matches = 0;
        boolean is = false;

        int t1 = 0;
        for(int i = 0; c[i] != ' ' ; i++){
            t1 += 1;
        }

        int t2 = 0;
        for(int i = t1+3; i < c.length ; i++){
            t2 += 1;
        }

        if(t1 == t2){

            for(int i = 0; i < t1 ; i++){
                for(int j = t1 + 3 ; j < s.length() ; j++){
                    if(c[i] == c[j]){
                        matches++;
                        // System.out.println("[ " + c[i]+ " ]" + " " + "[ " + c[j] + " ]");
                        c[i] = c[j] = ' ';
                        j = s.length();
                    }
                }
            }
        }

        if(matches == t1){
            is = true;
        }

        return is;
    }

    public static void main(String[] args){
        
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();
        
        while (!s.equals("FIM")) {
            
            s = s.toLowerCase();
            System.out.println(isAna(s) ? "SIM" : "N\u00C3O");
            s = sc.nextLine();


        }

    }
}