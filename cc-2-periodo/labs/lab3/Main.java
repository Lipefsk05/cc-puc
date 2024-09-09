import java.util.*;

public class Main
{
	
	static boolean pare(String str){
	   
	   int cont = 0;
	   
	    for(int i = 0 ; i < str.length() ; i++){
	        
	        if(str.charAt(i) == '('){
	            cont++;
	        }
	        else 
	        if(str.charAt(i) == ')'){
	            cont--;
	            if(cont < 0)
	                return false;
	        }
	    }    
	    
	    return cont == 0;
	}
	
	
	public static void main(String[] args) {
	    
        Scanner sc = new Scanner (System.in);
        String str;
        do{
            str = sc.nextLine();
            if(!str.equals("FIM")){
                if(pare(str))
                    System.out.println("correto");
                else
                    System.out.println("incorreto");
            }
        }
        while(!str.equals("FIM"));
	}
}
