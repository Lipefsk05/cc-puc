import java.util.*;

public class Main{

    static boolean bVog(String str, int i){

        String vog = "aeiouAEIOU";

        if(i == str.length()){
            return true;
        }
        else{
            if(!vog.contains(String.valueOf(str.charAt(i)))){
                return false;
            }
            else
                return(bVog(str, i+1));
        }
    }

    static boolean bCon(String str, int i){
        
        String con = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
        
        if(i == str.length()){
            return true;
        }
        else{
            if(!con.contains(String.valueOf(str.charAt(i)))){
                return false;
            }
            else
                return(bCon(str, i+1));
        }        
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
                if(bVog(str, 0))
                System.out.print("SIM ");
                else
                System.out.print("NAO ");
                //---------------------------------------
                if(bCon(str, 0))
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