import java.util.*;

public class Main{

    static String swap(String str, char l1, char l2){
        
        char[] alt1 = str.toCharArray();

        for(int i = 0 ; i < str.length() ; i++){
            
            if(alt1[i] == '\uFFFD')
                alt1[i] = '\uFFFD';
            else
            if(alt1[i] == l1){
                alt1[i] = l2;
            }
        }
        
        String alt2 = new String(alt1);

        return alt2;
    }

    public static void main(String[] args){
        
        Scanner sc = new Scanner (System.in);
        Random rd = new Random();
        String str;
        
        rd.setSeed(4);
        char l1 = ((char)('a' + (Math.abs(rd.nextInt()) % 26)));
        char l2 = ((char)('a' + (Math.abs(rd.nextInt()) % 26)));
        

        
        do{

            str = sc.nextLine();
            if(!str.equals("FIM"))
            System.out.println(swap(str, l1, l2));
            
        }while(!str.equals("FIM"));

        sc.close();
    }
}