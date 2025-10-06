import java.util.Random;

class Quicksort extends Geracao {

   public Quicksort() {
      super();
   }

   public Quicksort(int tamanho) {
      super(tamanho);
   }

   public void sort() {
      quicksort(0, n - 1);
   }

   public static int encontrarMediana(int x, int y, int z) {
      if ((x >= y && x <= z) || (x <= y && x >= z)) {
         return x;
      } else if ((y >= x && y <= z) || (y <= x && y >= z)) {
         return y;
      } else {
         return z;
      }
   }

   public void sortFirst() {
      long start = System.nanoTime();
      quicksortfirstpivot(0, n - 1);
      long end = System.nanoTime();

      long durationNs = end - start;
      long segundos = durationNs / 1_000_000_000;
      long milissegundos = (durationNs / 1_000_000) % 1000;
      long nanos = durationNs % 1_000_000;

      System.out.println(segundos + " segundos, " + milissegundos + " milissegundos e " + nanos + " nanosegundos");
   }

   public void sortLast() {
      long start = System.nanoTime();
      quicksortlastpivot(0, n - 1);
      long end = System.nanoTime();

      long durationNs = end - start;
      long segundos = durationNs / 1_000_000_000;
      long milissegundos = (durationNs / 1_000_000) % 1000;
      long nanos = durationNs % 1_000_000;

      System.out.println(segundos + " segundos, " + milissegundos + " milissegundos e " + nanos + " nanosegundos");
   }

   public void sortRandom() {
      long start = System.nanoTime();
      quicksortrandompivot(0, n - 1);
      long end = System.nanoTime();

      long durationNs = end - start;
      long segundos = durationNs / 1_000_000_000;
      long milissegundos = (durationNs / 1_000_000) % 1000;
      long nanos = durationNs % 1_000_000;

      System.out.println(segundos + " segundos, " + milissegundos + " milissegundos e " + nanos + " nanosegundos");
   }

   public void sortMedian() {
      long start = System.nanoTime();
      quicksortmedianpivot(0, n - 1);
      long end = System.nanoTime();

      long durationNs = end - start;
      long segundos = durationNs / 1_000_000_000;
      long milissegundos = (durationNs / 1_000_000) % 1000;
      long nanos = durationNs % 1_000_000;

      System.out.println(segundos + " segundos, " + milissegundos + " milissegundos e " + nanos + " nanosegundos");
   }

   private void quicksort(int esq, int dir) {
      int i = esq, j = dir;
      int pivo = array[(dir + esq) / 2];
      while (i <= j) {
         while (array[i] < pivo)
            i++;
         while (array[j] > pivo)
            j--;
         if (i <= j) {
            swap(i, j);
            i++;
            j--;
         }
      }
      if (esq < j)
         quicksort(esq, j);
      if (i < dir)
         quicksort(i, dir);
   }

   private void quicksortfirstpivot(int esq, int dir) {
      int i = esq, j = dir;
      int pivo = array[esq];
      while (i <= j) {
         while (array[i] < pivo)
            i++;
         while (array[j] > pivo)
            j--;
         if (i <= j) {
            swap(i, j);
            i++;
            j--;
         }
      }
      if (esq < j)
         quicksortfirstpivot(esq, j);
      if (i < dir)
         quicksortfirstpivot(i, dir);
   }

   private void quicksortlastpivot(int esq, int dir) {
      int i = esq, j = dir;
      int pivo = array[dir];
      while (i <= j) {
         while (array[i] < pivo)
            i++;
         while (array[j] > pivo)
            j--;
         if (i <= j) {
            swap(i, j);
            i++;
            j--;
         }
      }
      if (esq < j)
         quicksortlastpivot(esq, j);
      if (i < dir)
         quicksortlastpivot(i, dir);
   }

   Random rand = new Random();

   private void quicksortrandompivot(int esq, int dir) {
      if (esq >= dir)
         return; // evita subarrays inválidos

      int numero = esq + rand.nextInt(dir - esq + 1); // pivô seguro
      int pivo = array[numero];

      int i = esq;
      int j = dir;

      while (i <= j) {
         while (i <= dir && array[i] < pivo)
            i++;
         while (j >= esq && array[j] > pivo)
            j--;
         if (i <= j) {
            swap(i, j);
            i++;
            j--;
         }
      }

      if (esq < j)
         quicksortrandompivot(esq, j);
      if (i < dir)
         quicksortrandompivot(i, dir);
   }

   private void quicksortmedianpivot(int esq, int dir) {
      int i = esq, j = dir;

      int mediana = encontrarMediana(esq, ((dir + esq) / 2), dir);

      int pivo = array[mediana];
      while (i <= j) {
         while (array[i] < pivo)
            i++;
         while (array[j] > pivo)
            j--;
         if (i <= j) {
            swap(i, j);
            i++;
            j--;
         }
      }
      if (esq < j)
         quicksortmedianpivot(esq, j);
      if (i < dir)
         quicksortmedianpivot(i, dir);
   }

}