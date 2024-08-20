public class programa{
    public static void main(String[] args){
        
        MyIO.println("Digite o primeiro cateto: ");
        double cat1 = MyIO.readDouble();

        MyIO.println("Digite o segundo cateto: ");
        double cat2 = MyIO.readDouble();

        double hip = Math.sqrt((cat1*cat1)+(cat2*cat2));
        MyIO.println("A hipotenusa e: "+hip);

    }
}