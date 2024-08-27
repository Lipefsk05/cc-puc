import java.util.*;

public class Main{

    static boolean bVog(String str){

        String vog = "aeiouAEIOU";

        for(int i = 0 ; i < str.length() ; i++){
          
            if(!vog.contains(String.valueOf(str.charAt(i)))){
                return false;
            }
        }
        return true;
    }

    static boolean bCon(String str){

        String con = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";

        for(int i = 0 ; i < str.length() ; i++){

            if(!con.contains(String.valueOf(str.charAt(i)))){
                return false;
            }
        }
        return true;
    }

    static boolean bInt(String str){
        
        try{
            Integer.parseInt(str);
            return true;
        }
        catch(NumberFormatException e){
            return false;
        }
    }

    static boolean bRea(String str){

        str = str.replace(",",".");
        
        try{
            Double.parseDouble(str);
            return true;
        }
        catch(NumberFormatException e){
            return false;
        }
    }
    public static void main(String[] args) {
        
        Scanner sc = new Scanner(System.in);

        String str;
        do{
            str = sc.nextLine();
            
            if(!str.equals("FIM")){ 
                //---------------------------------------
                if(bVog(str))
                System.out.print("SIM ");
                else
                System.out.print("NAO ");
                //---------------------------------------
                if(bCon(str))
                System.out.print("SIM ");
                else
                System.out.print("NAO ");
                //---------------------------------------
                if(bInt(str))
                System.out.print("SIM ");
                else
                System.out.print("NAO ");
                //---------------------------------------
                if(bRea(str))
                System.out.println("SIM");
                else
                System.out.println("NAO");
                //---------------------------------------
            }
        }
        while(!str.equals("FIM"));
    }
}