import java.util.*;

public class Main{

	static void alterar(String alt, char let1, char let2){
	
	char[] alterado = alt.toCharArray(); 

	for(int i = 0 ; i < alterado.length ; i++){
		if(alterado[i] == let1)
			alterado[i] = let2;
	}

	System.out.println(alterado);
	
	}

	public static void main(String[] args){
		
		Scanner sc = new Scanner(System.in);
		
		Random gerador = new Random();
		gerador.setSeed(4);
		
		
		String alt = sc.nextLine();
		
		while(!alt.equals("FIM")){
		char let1 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
		char let2 = (char)('a' + (Math.abs(gerador.nextInt()) % 26));
		
		alterar(alt, let1, let2);

		alt = sc.nextLine();
		
		}
	}
}
