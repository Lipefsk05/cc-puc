import java.util.*;
import java.io.*;

public class Main{

    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);

        String nome = "arquivo.dat";
        int n = sc.nextInt();

        try(RandomAccessFile aqv = new RandomAccessFile(nome, "rw")){
            
            for(int i = 0 ; i < n ; i++){

                double num = sc.nextDouble();
                aqv.writeDouble(num);
            }
            
        }
        catch(IOException e){
            e.getMessage();
        }

        try(RandomAccessFile aqv = new RandomAccessFile(nome, "r")){
            
            for(int i = n-1 ; i >= 0 ; i--){
                
                long pos = i * 8;
                aqv.seek(pos);
                double num = aqv.readDouble();
                System.out.println(num);

            }
        }
        catch(IOException e){
            e.getMessage();
        }
    
        sc.close();
    }
}
