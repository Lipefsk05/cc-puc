import java.io.IOException;
import java.util.Scanner;

public class Main {
    
    public static void main(String[] args) throws IOException {
        
        Scanner sc = new Scanner(System.in);
        
        
        while (sc.hasNext()) {

            int ni = sc.nextInt();
            int nf = sc.nextInt();
            
            for(int i = ni ; i <= nf ; i++){
                System.out.print(i);
            }
            for(int i = nf; i >= ni ; i-- ){
                StringBuilder sb = new StringBuilder();

                sb.append(i);
                sb.reverse();
                
                System.out.print(sb.toString());
            }

            System.out.println();
        }

        sc.close();
    }    
}












