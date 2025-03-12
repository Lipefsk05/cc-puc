import java.util.*;


public class Main{

	static boolean palindromo(String palavra, int tam, int i, int j){
		
		char [] p = palavra.toCharArray();
		
		if(i >= j)
			return true;

		if(p[i] != p[j]) 
			return false;
	
		return palindromo(palavra, tam, i+1, j-1);
	}	
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);

		String palavra;

		do{
		
			palavra = sc.nextLine();

			if(!palavra.equals("FIM")){
				if(palindromo(palavra, palavra.length() - 1, 0, palavra.length() - 1))
					System.out.println("SIM");
				else
					System.out.println("NAO");
			}
		}
		while(!palavra.equals("FIM"));
	}
}
