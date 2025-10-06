public class QuickRandom {

    public QuickRandom() {  // <-- construtor correto
        Quicksort qs;

        System.out.println("------------------------------ Random Pivot ------------------------------\n");

        System.out.println("----- Quase ordenado -----\n");

        System.out.print("Array de 100: ");
        qs = new Quicksort(100);
        qs.quaseOrdenado();
        qs.sortRandom();

        System.out.print("Array de 1000: ");
        qs = new Quicksort(1000);
        qs.quaseOrdenado();
        qs.sortRandom();

        System.out.print("Array de 10000: ");
        qs = new Quicksort(10000);
        qs.quaseOrdenado();
        qs.sortRandom();

        System.out.println("\n----- Ordenado -----\n");

        System.out.print("Array de 100: ");
        qs = new Quicksort(100);
        qs.crescente();
        qs.sortRandom();

        System.out.print("Array de 1000: ");
        qs = new Quicksort(1000);
        qs.crescente();
        qs.sortRandom();

        System.out.print("Array de 10000: ");
        qs = new Quicksort(10000);
        qs.crescente();
        qs.sortRandom();

        System.out.println("\n----- Aleatório -----\n");

        System.out.print("Array de 100: ");
        qs = new Quicksort(100);
        qs.aleatorio();
        qs.sortRandom();

        System.out.print("Array de 1000: ");
        qs = new Quicksort(1000);
        qs.aleatorio();
        qs.sortRandom();

        System.out.print("Array de 10000: ");
        qs = new Quicksort(10000);
        qs.aleatorio();
        qs.sortRandom();

        System.out.println("\n\n\n");
    }
}
