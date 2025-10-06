import java.util.*;


public class Main{

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int part;

        while (sc.hasNext()) {
            
            part = sc.nextInt();
            sc.nextLine();

            int[] arrIni = new int[part];
            int[] arrFim = new int[part];
            int cont = 0;
            
            for(int i = 0; i < part; i++){
                arrIni[i] = sc.nextInt();
            }
            
            for(int i = 0; i < part; i++){
                arrFim[i] = sc.nextInt();
            }
            
            for(int i = 0 ; i < part ; i++){
                for(int j = 0 ; j < i ; j++){
                    if(arrIni[i] == arrFim[j] && i > j){
                        int n = arrIni[i];

                        for(int k = i ; k > j ; k--){
                            arrIni[k] = arrIni[k-1];
                            cont++;

                        }
                        arrIni[j] = n;

                    }
                }   
            }
            System.out.println(cont);
        }
        System.out.println("\n");
        sc.close();
    }
}