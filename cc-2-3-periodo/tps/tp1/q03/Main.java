import java.util.*;

public class Main {

    static String cifrar(String cif){
        int tam = cif.length();

        char[] cifrado = cif.toCharArray();

        for(int i = 0 ; i < tam ; i++){
            if(cifrado[i] == '\uFFFD')
                cifrado[i] = '\uFFFD';
            else{
                int j = cifrado[i]+3;

                if(j == 127)
                    j = 32;

                if(j == 128)
                    j = 33;

                if(j == 129)
                    j = 34;

                cifrado[i] = (char) j;
                
            }
        }

        return new String(cifrado);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String cif = sc.nextLine();
        
        while(!cif.equals("FIM")){

            System.out.println(cifrar(cif));
            
            cif = sc.nextLine();

        }
        
        sc.close();

    }
}
