import java.util.*;

public class Main{

	static boolean verVog(String p){
		
		p = p.toLowerCase();
		String vogais = "aeiou";

		for(int i = 0 ; i < p.length() ; i++){

			if(!vogais.contains(String.valueOf(p.charAt(i)))){
                return false;
            }
		}

		return true;
	}
	static boolean verConso(String p){
		
		p = p.toLowerCase();
        String consoantes = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";

		for(int i = 0 ; i < p.length() ; i++){

			if(!consoantes.contains(String.valueOf(p.charAt(i)))){
                return false;
            }
		}

		return true;
	}
	static boolean verInt(String p){
        
        try{
            Integer.parseInt(p);
            return true;
        }
        catch(NumberFormatException e){
            return false;
        } 

	}
	static boolean verReal(String p){
		
		p = p.replace(",",".");
        
        try{
            Double.parseDouble(p);
            return true;
        }
        catch(NumberFormatException e){
            return false;
        }
    }	

	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);

		String p = sc.nextLine();
	
		while(!p.equals("FIM")){
			
			if(verVog(p))
				System.out.print("SIM ");
			else	
				System.out.print("NAO ");
			
			if(verConso(p))
				System.out.print("SIM ");
			else
				System.out.print("NAO ");

			if(verInt(p))
				System.out.print("SIM ");
			else
				System.out.print("NAO ");

			if(verReal(p))
				System.out.println("SIM");
			else
				System.out.println("NAO");

			p = sc.nextLine();
		}
	}		
}
