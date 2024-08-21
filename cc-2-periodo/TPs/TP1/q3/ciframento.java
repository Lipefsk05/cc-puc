    import java.util.Scanner;

    public class ciframento{

    static String cfm(String frase){
        
        int tam = frase.length()-1;
        char[] cifrado = frase.toCharArray();

        for( int i = 0 ; i <= tam; i++){
            
            if(cifrado[i] == '\uFFFD'){
                cifrado[i] = '\uFFFD';
            }
            else{
                int j = cifrado[i]+3;
                if(j == 127)
                    j = 32;
                else
                if(j == 128)
                    j = 33;
                else
                if(j == 129)
                    j = 34;
                cifrado[i] = (char) j;
            }
        }

        return new String(cifrado);

        
    }
    // 32 126

        public static void main(String[] args) {
            
            Scanner sc = new Scanner(System.in);
            String frase;

            
            do{
                frase = sc.nextLine();
                if(!frase.equals("FIM"))
                System.out.println(cfm(frase));
            }
            while(!frase.equals("FIM"));

            sc.close();
            // int x = '�';
            // System.out.println(x);
        }
    }