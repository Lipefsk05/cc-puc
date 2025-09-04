import java.nio.channels.Pipe.SourceChannel;
import java.util.*;

public class Main {

    static void fillLet(char []let){
        
        for(int i = 0 ; i < let.length ; i++){
            let[i] = (char) (65 + i);
        }


        for(char i : let)
            System.out.print(i);
        System.out.println();

    }
            
    static void fillVal(String p, int[] val){
        
        for (int i = 1, j = 0; i < p.length() && j < val.length; i++) {
            
            if (p.charAt(i) >= '0' && p.charAt(i) <= '9') {
                
                val[j] = p.charAt(i) - '0';
                
                j++;

                if(j>=val.length)
                    i = p.length();

            }
        }

        for(int i : val)
            System.out.print(i);
        System.out.println();
    }
    
    static void swapNum(String p, int[] val, char[] pArr, char[] let){

        for(int i = 0, j = (val.length * 2) + 2 ; i < p.length() - ((val.length * 2) + 2) ; i++, j++){
            pArr[i] = p.charAt(j);
        }

        for(int i = 0 ; i < pArr.length ; i++){
            
            if(pArr[i] >= 65 && pArr[i] <= 90){
                for(int j = 0 ; j < let.length ; j++){
                    if(pArr[i] == let[j]){
                        pArr[i] = (char) (val[j] + '0');
                    }
                }
            }
        }

        for(char i : pArr)
            System.out.print(i);
        System.out.println();
    }

    static void doAlg(char[] pArr){

        int tam = pArr.length;
        
        for(int i = 0 ; i < tam ; i++){
            
            if(pArr[i] == '0' || pArr[i] == '1'){
                
                if(pArr[i - 2] == 't'){

                    if(pArr[i] == '0')
                        pArr[i - 4] = '1';
                    else if(pArr[i] == '1')
                        pArr[i - 4] = '0';

                    for(int j = i - 3 ; j < tam - 1 ; j++){
                        pArr[j] = pArr[j+1];
                        pArr[j+1] = '-';
                    }
                }

                tam -= 1;
            }
        }

        for(char i : pArr)
            System.out.print(i);
        System.out.println();
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String p = sc.nextLine();

        while (!p.equals("FIM")) {

            int size = p.charAt(0) - '0';
            int[] val = new int[size];
            char[] let = new char[size];
            char[] pArr = new char[p.length() - ((val.length * 2) + 2)];

            fillLet(let);
            fillVal(p, val);
            swapNum(p, val, pArr, let);
            doAlg(pArr);

            p = sc.nextLine();
        }
    }
}

//2 0 1 and(not(A) , not(B))