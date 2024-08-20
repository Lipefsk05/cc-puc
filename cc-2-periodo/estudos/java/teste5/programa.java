public class programa{
    public static void main(String[] args){
    
        String[] carros = new String[3];
        
        carros[0] = "camaro";
        carros[1] = "bmw";
        carros[2] = "fusca";

        for(int i=0; i<carros.length; i++){
            System.out.println(carros[i]);
        }
    }
}