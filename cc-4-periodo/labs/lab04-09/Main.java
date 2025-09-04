import java.util.*;

class Main{

    static void swap(int[] arr, int j, int menor){
        int temp = arr[menor];
        arr[menor] = arr[j];
        arr[j] = temp;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();

        while (!(n == 0 && m == 0)) {
            int[] arr = new int[n];
            
            for(int i = 0 ; i < n ; i++){
            arr[i] = sc.nextInt();
            }
        
            for(int i = 0 ; i < arr.length ; i++){
                int menor = i;

                for(int j = i+1 ; j < arr.length ; j++){

                    // se for mod menor troca
                    if(arr[j] % m < arr[menor] % m){
                        swap(arr, j, menor);
                    }
                    // se for mod igual
                    else if(arr[j] % m == arr[menor] % m){
                        
                        // coloca o impar na atras
                        if((arr[j] % 2 != 0) && (arr[menor] % 2 == 0)){
                            swap(arr, j, menor);
                        }
                        else{
                            
                            // se forem 2 impares maior impar atras
                            if((arr[j] % 2 != 0) && (arr[menor] % 2 != 0)){
                                if(arr[j] > arr[menor])
                                swap(arr, j, menor);
                            }
                            
                            // se forem 2 pares
                            if((arr[j] % 2 == 0) && (arr[menor] % 2 == 0)){
                                if(arr[j] < arr[menor])
                                swap(arr, j, menor);
                            } 
                        }

                    }
                    
                }
            }

            System.out.println(n + " " + m);
            for(int i : arr){
                System.out.println(i);
            }

            n = sc.nextInt();
            m = sc.nextInt();
        }
            System.out.println(0 + " " + 0);

    }
}