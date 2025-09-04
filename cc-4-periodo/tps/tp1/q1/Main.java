import java.util.*;

public class Main {

    static Boolean pali(String s) {
        boolean ver = pali(s, 0, s.length() - 1);
        return ver;
    }

    static boolean pali(String s, int esq, int dir) {

        if( esq >= dir )
            return true;

        if (s.charAt(esq) == s.charAt(dir))
            return pali(s, esq+1, dir-1);
            
        return false;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        String s = sc.nextLine();

        while (!s.equals("FIM")) {

            System.out.println(pali(s) ? "SIM" : "NAO");

            s = sc.nextLine();

        }

        sc.close();
    }
}

