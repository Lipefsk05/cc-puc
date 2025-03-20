import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        try {
            Locale.setDefault(Locale.US);
            
            RandomAccessFile arquivo = new RandomAccessFile("dados.txt", "rw");

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            int n = Integer.parseInt(reader.readLine());

            for (int i = 0; i < n; i++) {
                double valor = Double.parseDouble(reader.readLine());
                arquivo.writeDouble(valor);
            }

            long posicao = arquivo.length() - 8;
            while (posicao >= 0) {
                arquivo.seek(posicao);
                double valor = arquivo.readDouble();

                // Se o valor for um número inteiro, imprima sem casas decimais
                if (valor == (int) valor) {
                    System.out.println((int) valor);
                } else {
                    System.out.println(valor);
                }

                posicao -= 8; 
            }

            arquivo.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
