import java.util.*;

public class Main{

	static boolean verVog(String p, int i){
		
		String vogais = "aeiou";

        if(i >= p.length())
            return true;

        if(!vogais.contains(String.valueOf(p.charAt(i)))){
            return false;
        }

		return verVog(p, i + 1);
	}
	static boolean verConso(String p, int i){
		
        String consoantes = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";

        if(i >= p.length())
            return true;

        if(!consoantes.contains(String.valueOf(p.charAt(i))))
            return false;

        return verConso(p, i + 1);


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
		p = p.toLowerCase();
	
		while(!p.equals("FIM")){
			
			if(verVog(p, 0))
				System.out.print("SIM ");
			else	
				System.out.print("NAO ");
			
			if(verConso(p, 0))
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