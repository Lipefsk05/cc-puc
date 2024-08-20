public class labq1{

    static int maimin(String palavra){

        int tam = ((palavra.length())-1);

        char[] stg = palavra.toCharArray();

        int mai = 0;

        for(int i = 0 ; i <= tam ; i++){
            if(stg[i]>=65 && stg[i]<=90){
                mai++;
            }
        }

        return mai;

    }
    public static void main(String[] args){
        
        String palavra;
        
        do{
            palavra = MyIO.readLine();
            if(!palavra.equals("FIM"))
            MyIO.println(maimin(palavra));
        }

        while(!palavra.equals("FIM"));
    }
    
}