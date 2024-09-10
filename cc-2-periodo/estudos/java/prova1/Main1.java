import java.util.*;

public class Main1{

    public static int glob = 0;

    static void lerArray(int[] array){
        
        Scanner sc = new Scanner(System.in);
        
        for(int i = 0 ; i < array.length ; i++ ){
            array[i] = sc.nextInt(); 
        }
        sc.close();
    }

    static void verArray(int[] array){

        Scanner sc = new Scanner(System.in);
        
        for(int i = 0 ; i < array.length ; i++ ){
            System.out.print(array[i] + " "); 
        }
        System.out.println(" ");
        sc.close();
    }
    
    static void swap(int[] array, int i, int j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    static void ordArraySel(int[] array){
        
        glob = 0;

        for(int i = 0 ; i < array.length-1 ; i++){
            
            int m = i;

            for(int j = (i + 1) ; j < array.length ; j++){

                
                if(array[m] > array[j])
                m = j;
            }
            if(m != i){
                glob++;
                swap(array, m, i);
                
            }
        }
    }

    static void ordArrayIns(int[] array){

        glob = 0;

        for(int i = 1 ; i < array.length ; i++){

            int tmp = array[i];
            int j = i - 1;
            while ( (j >= 0) && (array[j]> tmp) ) {

                glob++;

                array[j + 1] = array[j];
                j--;
            }

            array[j + 1] = tmp;
        }
    }
    
    static void ordArrayBol(int[] array){

        glob = 0;

        for(int i = 0 ; i < array.length-1 ; i++){
            
            for(int j = 0 ; j < array.length-1 ; j++){
                
                glob++;

                if(array[j] > array[j + 1]){
            
                    int aux = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = aux;
                }
            }
        }
    }
    
    static void ordArrayBolFix(int[] array){
        
        glob = 0;

        for(int i = array.length-1 ; i > 0 ; i--){
            
            for(int j = 0 ; j < i ; j++){
                glob++;
                if(array[j] > array[j + 1]){
            
                    int aux = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = aux;
                    
                    
                }
            }
        }
    }
    
    static void ordArrayInsBin(int[] array){
        
        glob = 0;

        for(int i = 1 ; i < array.length ; i++){

            int aux = array[i];
            int j = pesqBin(array, aux, 0, i);
            int k = i;

            while (k > j) {
                
                glob++;
                array[k] = array[k-1];
                k--;
            }
            array[j] = aux;
        }
    }

    static int pesqBin(int[] array, int aux, int esq, int dir){
        while (esq < dir) {
            int meio = (esq+dir)/2;

            if(array[meio] < aux)
                esq = meio+1;
            else
                dir = meio;
        }
        return esq;
    }

    public static void main(String[] args){

        Scanner sc = new Scanner(System.in);
        
        int[] array = {10, 9, 8, 7 ,6 ,5 , 4, 3, 2, 1};
        verArray(array);
        System.err.println(" ");

        int[] array1 = {10, 9, 8, 7 ,6 ,5 , 4, 3, 2, 1};
        System.err.println("Seleção:");
        ordArraySel(array1);
        verArray(array1);
        System.err.println("Trocas: " + glob);

        System.err.println(" ");

        int[] array2 = {10, 9, 8, 7 ,6 ,5 , 4, 3, 2, 1};
        System.out.println("Insersção:");
        ordArrayIns(array2);
        verArray(array2);
        System.err.println("Trocas: " + glob);

        System.err.println(" ");

        int[] array3 = {10, 9, 8, 7 ,6 ,5 , 4, 3, 2, 1};
        System.out.println("Bolha:");
        ordArrayBol(array3);
        verArray(array3);
        System.err.println("Trocas: " + glob);
        
        System.err.println(" ");

        int[] array4 = {10, 9, 8, 7 ,6 ,5 , 4, 3, 2, 1};
        System.out.println("Bolha Fix:");
        ordArrayBolFix(array4);
        verArray(array4);
        System.err.println("Trocas: " + glob);

        System.err.println(" ");

        int[] array5 = {10, 9, 8, 7 ,6 ,5 , 4, 3, 2, 1};
        System.out.println("Inserção PesqBin:");
        ordArrayInsBin(array5);
        verArray(array5);
        System.err.println("Trocas: " + glob);


        sc.close();
    }
}