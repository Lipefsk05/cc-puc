    import java.util.*;

    class Main {

        static void printa(String s){

            for(int i = 0 ; i < s.length() ; i++){
                System.out.print(s.charAt(i));
            }

            for(int i = s.length()-1 ; i >= 0 ; i--){
                System.out.print(s.charAt(i));
            }
            
        }

        static String CreateString(int n, int m){
            
            String s = "";
            for(int i = n ; i <= m ; i++){
                s += i;
            }
            return s;
        }

        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);

            int n = sc.nextInt();
            int m = sc.nextInt();

            while(sc.hasNextLine()){

                String s = CreateString(n, m);
                printa(s);
                
            }
        }
    }