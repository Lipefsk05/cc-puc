import java.util.*;

public class Main {

    static String cifrar(char[] cifrado, int tam, int i){


        if(i >= tam)
            return new String(cifrado);

        
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

        return cifrar(cifrado, tam, i + 1);

    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String cif = sc.nextLine();
        char[] cifrado = cif.toCharArray();
        
        while(!cif.equals("FIM")){

            System.out.println(cifrar(cifrado, cif.length(),0));
            
            cif = sc.nextLine();
            cifrado = cif.toCharArray();

        }
        
        sc.close();

    }
}
