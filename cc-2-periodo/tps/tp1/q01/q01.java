import java.util.*;


public class q01{
	
	static boolean palindromo(String palavra){
		int tam = palavra.length() - 1;
		int j = tam;
		
		char [] p = palavra.toCharArray();

		for(int i = 0 ; i < tam / 2 ; i++, j--){
						
			if(p[i] != p[j]) 
				return false;
		}

		return true;
	}	

	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);

		String palavra;

		do{
		
			palavra = sc.nextLine();

			if(!palavra.equals("FIM")){
				if(palindromo(palavra))
					System.out.println("SIM");
				else
					System.out.println("NAO");
			}
		}
		while(!palavra.equals("FIM"));
	}
}
