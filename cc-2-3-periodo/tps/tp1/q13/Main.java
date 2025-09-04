import java.io.*;
import java.net.URL;
import java.util.*;
import java.util.regex.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        while (scanner.hasNextLine()) {
            String linha = scanner.nextLine();
            if (linha.equals("FIM")) break;

            String[] partes = linha.split(" ", 2);
            if (partes.length < 2) continue;
            
            String url = partes[0];
            String nomePagina = partes[1];

            String conteudoPagina = obterCodigoFonte(url);
            if (conteudoPagina == null) {
                System.out.println("Erro ao obter o código-fonte da página: " + url);
                continue;
            }

            // Definição de padrões
            String vogais = "aeiouáéíóúàèìòùãõâêîôû";
            String consoantes = "bcdfghjklmnpqrstvwxyz";

            // Dicionário para contar vogais individualmente
            Map<Character, Integer> contagemVogais = new HashMap<>();
            for (char v : vogais.toCharArray()) {
                contagemVogais.put(v, 0);
            }

            int consoanteCount = 0;
            int brCount = contarOcorrencias(conteudoPagina, "<br>");
            int tableCount = contarOcorrencias(conteudoPagina, "<table>");
            int nomePaginaCount = contarOcorrencias(conteudoPagina.toLowerCase(), nomePagina.toLowerCase());

            // Contagem de caracteres
            for (char c : conteudoPagina.toLowerCase().toCharArray()) {
                if (contagemVogais.containsKey(c)) {
                    contagemVogais.put(c, contagemVogais.get(c) + 1);
                } else if (consoantes.indexOf(c) != -1) {
                    consoanteCount++;
                }
            }

            // Exibir resultado
            StringBuilder resultado = new StringBuilder();
            for (char v : vogais.toCharArray()) {
                resultado.append(v).append("(x ").append(contagemVogais.get(v)).append(") ");
            }
            resultado.append("consoante(x ").append(consoanteCount).append(") ");
            resultado.append("<br>(x ").append(brCount).append(") ");
            resultado.append("<table>(x ").append(tableCount).append(") ");
            resultado.append(nomePagina).append("(x ").append(nomePaginaCount).append(")");

            System.out.println(resultado.toString());
        }
        scanner.close();
    }

    // Método para obter código HTML da página
    private static String obterCodigoFonte(String endereco) {
        StringBuilder resultado = new StringBuilder();
        try {
            URL url = new URL(endereco);
            BufferedReader reader = new BufferedReader(new InputStreamReader(url.openStream()));
            String linha;
            while ((linha = reader.readLine()) != null) {
                resultado.append(linha).append("\n");
            }
            reader.close();
        } catch (IOException e) {
            System.err.println("Erro ao acessar URL: " + endereco);
            return null;
        }
        return resultado.toString();
    }

    // Método para contar padrões no texto
    private static int contarOcorrencias(String texto, String padrao) {
        Matcher matcher = Pattern.compile(Pattern.quote(padrao), Pattern.CASE_INSENSITIVE).matcher(texto);
        int contador = 0;
        while (matcher.find()) {
            contador++;
        }
        return contador;
    }
}
