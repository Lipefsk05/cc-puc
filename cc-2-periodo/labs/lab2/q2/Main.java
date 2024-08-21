import java.io.IOException;
import java.util.Scanner;

public class Main {
    
    public static void main(String[] args) throws IOException {
        
        Scanner scanner = new Scanner(System.in);
        
        
        while (scanner.hasNext()) {

            int ni = scanner.nextInt();
            int nf = scanner.nextInt();
            
            for(int i = ni ; i <= nf ; i++){
                System.out.print(i);
            }
            for(int i = nf; i >= ni ; i-- ){
                int j = i;
                
                if(j != 10 && j != 100 && j != 1000 && j != 101 && j!= 1001){
                    if (j>10) {   
                        j = (j%10)*10 + j/10;
                        System.out.print(j);
                    }
                    else{
                        System.out.print(j);
                    }
                }
                else
                if(j == 10){
                    System.out.print("01");
                }
                else
                if(j == 100){
                    System.out.print("001");
                }
                else
                if(j == 1000){
                    System.out.print("0001");
                }
                else
                if(j == 101){
                    System.out.print("101");
                    
                }
                else
                if(j == 1001){
                    System.out.print("1001");
                }
            }
            System.out.println();
        }
    }    
}












