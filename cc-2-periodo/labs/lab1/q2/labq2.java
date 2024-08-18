public class labq2{

    static int maimin(int i, String palavra, int mai){

        char[] stg = palavra.toCharArray();
        
        int tam = ((palavra.length()));

        if(i>=tam){
           
            return mai;

        }else if((stg[i]>=65 && stg[i]<=90)){

            return maimin(i+1, palavra, mai+1);
        }else 
            return maimin (i+1, palavra, mai);
    }
    public static void main(String[] args){
        
        String palavra;
        
        do{
            palavra = MyIO.readLine();
            if(!palavra.equals("FIM"))
            MyIO.println(maimin(0, palavra, 0));
        }

        while(!palavra.equals("FIM"));
    }
    
}