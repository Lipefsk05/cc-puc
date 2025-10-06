import java.util.Scanner;

class Main {

    static String inverter(String s) {
        if (s.isEmpty()) {
            return s;
        }
        return inverter(s.substring(1)) + s.charAt(0);
    }

    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);
        
        String entrada = sc.nextLine();
        System.out.println(inverter(entrada));
    }
}
