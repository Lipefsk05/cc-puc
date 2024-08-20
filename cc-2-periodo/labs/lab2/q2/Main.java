import java.io.IOException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        
        Scanner scanner = new Scanner(System.in);
        
            int ni = scanner.nextInt();
            int nf = scanner.nextInt();
        
            for(int i = ni ; i <= nf ; i++){
                System.out.print(i);
            }
            for(int i = nf ; i >= ni ; i--){
                // int j = i;
                int j  = i%10;
                int k = i/10;
                System.out.print(k);
                System.out.print(j);
            }
    }

}