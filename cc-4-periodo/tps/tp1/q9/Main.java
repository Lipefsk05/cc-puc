import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextLine()) {
            String linha = sc.nextLine().trim();
            if (linha.isEmpty()) continue;

            String[] partes = linha.split(" ");
            int n = Integer.parseInt(partes[0]);

            // condição de parada
            if (n == 0) break;

            // precisa ter pelo menos n valores + expressão
            if (partes.length < n + 2) {
                System.err.println("Linha inválida: " + linha);
                continue;
            }

            int[] valores = new int[n];
            for (int i = 0; i < n; i++) {
                valores[i] = Integer.parseInt(partes[i + 1]);
            }

            // reconstruir a expressão
            StringBuilder sb = new StringBuilder();
            for (int i = n + 1; i < partes.length; i++) {
                sb.append(partes[i]).append(" ");
            }
            String expr = sb.toString().trim();

            // substituir variáveis
            for (int i = 0; i < n; i++) {
                char var = (char) ('A' + i);
                expr = expr.replace(String.valueOf(var), String.valueOf(valores[i]));
            }

            // avaliar expressão
            boolean resultado = avalia(expr);
            System.out.println(resultado ? "1" : "0");
        }
    }

    static boolean avalia(String expr) {
        // normalizar espaços
        expr = expr.replace("(", " ( ")
                   .replace(")", " ) ")
                   .replace(",", " ");
        String[] tokens = expr.trim().split("\\s+");

        // shunting-yard
        List<String> saida = new ArrayList<>();
        Stack<String> ops = new Stack<>();

        for (String t : tokens) {
            if (t.equals("0") || t.equals("1")) {
                saida.add(t);
            } else if (t.equals("not") || t.equals("and") || t.equals("or")) {
                while (!ops.isEmpty() && !ops.peek().equals("(")) {
                    saida.add(ops.pop());
                }
                ops.push(t);
            } else if (t.equals("(")) {
                ops.push(t);
            } else if (t.equals(")")) {
                while (!ops.peek().equals("(")) {
                    saida.add(ops.pop());
                }
                ops.pop();
            }
        }
        while (!ops.isEmpty()) saida.add(ops.pop());

        // avaliar RPN
        Stack<Boolean> pilha = new Stack<>();
        for (String t : saida) {
            if (t.equals("0") || t.equals("1")) {
                pilha.push(t.equals("1"));
            } else if (t.equals("not")) {
                boolean a = pilha.pop();
                pilha.push(!a);
            } else if (t.equals("and")) {
                boolean b = pilha.pop();
                boolean a = pilha.pop();
                pilha.push(a && b);
            } else if (t.equals("or")) {
                boolean b = pilha.pop();
                boolean a = pilha.pop();
                pilha.push(a || b);
            }
        }

        return pilha.pop();
    }
}
