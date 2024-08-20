import java.util.Scanner;

public class programa{
    public static void main(String[] args){
        
        System.out.println("Qual seu nome?");

        String name = MyIO.readString();

        MyIO.println(name);
    }
}