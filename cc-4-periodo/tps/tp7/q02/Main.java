import java.util.*;
import java.io.*;
import java.text.*;

class Game {
    int id;
    String name;
    String releaseDate;
    int estimateOwners;
    double price;
    String[] supportedLanguages;
    int metacriticScore;
    double userScore;
    int achieviments;
    String[] publishers;
    String[] developers;
    String[] categories;
    String[] genres;
    String[] tags;

    public Game(
            int id,
            String name,
            String releaseDate,
            int estimateOwners,
            double price,
            String[] supportedLanguages,
            int metacriticScore,
            double userScore,
            int achieviments,
            String[] publishers,
            String[] developers,
            String[] categories,
            String[] genres,
            String[] tags) {
        this.id = id;
        this.name = name;
        this.releaseDate = releaseDate;
        this.estimateOwners = estimateOwners;
        this.price = price;
        this.supportedLanguages = supportedLanguages;
        this.metacriticScore = metacriticScore;
        this.userScore = userScore;
        this.achieviments = achieviments;
        this.publishers = publishers;
        this.developers = developers;
        this.categories = categories;
        this.genres = genres;
        this.tags = tags;
    }

    private String formatDate(String dateStr) {
        try {
            SimpleDateFormat inputFormat = new SimpleDateFormat("MMM dd, yyyy", java.util.Locale.ENGLISH);
            SimpleDateFormat outputFormat = new SimpleDateFormat("dd/MM/yyyy");
            Date date = inputFormat.parse(dateStr);
            return outputFormat.format(date);
        } catch (ParseException e) {
            return dateStr;
        }
    }

    private String arrayToString(String[] arr) {
        if (arr == null || arr.length == 0)
            return "[]";

        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < arr.length; i++) {
            sb.append(arr[i].trim());
            if (i < arr.length - 1)
                sb.append(", ");
        }
        sb.append("]");
        return sb.toString();
    }

    public void printFormatted() {
        String priceStr = (price == 0.0) ? "0.0" : String.format("%.2f", price);

        System.out.printf(
                "=> %d ## %s ## %s ## %d ## %s ## %s ## %d ## %.1f ## %d ## %s ## %s ## %s ## %s ## %s ##%n",
                id,
                name,
                formatDate(releaseDate),
                estimateOwners,
                priceStr,
                arrayToString(supportedLanguages),
                metacriticScore,
                userScore,
                achieviments,
                arrayToString(publishers),
                arrayToString(developers),
                arrayToString(categories),
                arrayToString(genres),
                arrayToString(tags));
    }
}

// Nó da segunda árvore (árvore de nomes)
class No2 {
    public Game game;
    public String key;
    public No2 esq;
    public No2 dir;

    public No2(Game game) {
        this.game = game;
        this.key = game.name;
        this.esq = null;
        this.dir = null;
    }
}

// Arvore2: operações de inserção e pesquisa por nome (string)
// A pesquisa retorna o caminho dentro da árvore 2 usando "esq"/"dir" (minúsculo),
// sem prefixar "raiz".
class Arvore2 {
    public No2 inserir(No2 no, Game game) {
        if (no == null) return new No2(game);

        int cmp = game.name.compareTo(no.key);
        if (cmp < 0) no.esq = inserir(no.esq, game);
        else if (cmp > 0) no.dir = inserir(no.dir, game);
        // se igual, ignora (não insere duplicado)
        return no;
    }

    // Pesquisar construindo caminho sem "raiz" inicial.
    // caminho: StringBuilder que será preenchido com " esq" / " dir" conforme sobe.
    public boolean pesquisarSemRaiz(No2 no, String nome, StringBuilder caminho) {
        if (no == null) return false;

        int cmp = nome.compareTo(no.key);
        if (cmp == 0) return true;

        if (cmp < 0) {
            caminho.append(" esq");
            return pesquisarSemRaiz(no.esq, nome, caminho);
        } else {
            caminho.append(" dir");
            return pesquisarSemRaiz(no.dir, nome, caminho);
        }
    }
}

// Nó da primeira árvore (inteiro) que contém raiz da segunda árvore
class No1 {
    public int chave;
    public No1 esq;
    public No1 dir;
    public No2 raiz2; // raiz da segunda árvore

    public No1(int chave) {
        this.chave = chave;
        this.esq = null;
        this.dir = null;
        this.raiz2 = null;
    }
}

// Arvore1: árvore de inteiros (chaves 0..14) fixa
class Arvore1 {
    private No1 raiz;

    public Arvore1() {
        raiz = null;
    }

    public No1 getRaiz() {
        return raiz;
    }

    public void inserir(int chave) {
        raiz = inserirRec(raiz, chave);
    }

    private No1 inserirRec(No1 no, int chave) {
        if (no == null) return new No1(chave);

        if (chave < no.chave) no.esq = inserirRec(no.esq, chave);
        else if (chave > no.chave) no.dir = inserirRec(no.dir, chave);
        return no;
    }

    public No1 buscarChave(int chave) {
        No1 x = raiz;
        while (x != null) {
            if (chave == x.chave) return x;
            if (chave < x.chave) x = x.esq;
            else x = x.dir;
        }
        return null;
    }
}

public class Main {

    private static String[] parseArray(String s) {
        s = s.trim();
        if (s.startsWith("[") && s.endsWith("]")) {
            s = s.substring(1, s.length() - 1);
        }
        if (s.isEmpty())
            return new String[0];

        String[] items = s.split(",\\s*");
        for (int i = 0; i < items.length; i++) {
            items[i] = items[i].trim();
            items[i] = items[i].replaceAll("^'+|'+$", "");
            items[i] = items[i].replaceAll("^\"+|\"+$", "");
        }
        return items;
    }

    private static List<String> parseCSVLine(String line) {
        List<String> tokens = new ArrayList<>();
        boolean inQuotes = false;
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < line.length(); i++) {
            char c = line.charAt(i);
            if (c == '"') {
                inQuotes = !inQuotes;
                // não adiciona a própria aspa
            } else if (c == ',' && !inQuotes) {
                tokens.add(sb.toString().trim());
                sb.setLength(0);
            } else {
                sb.append(c);
            }
        }
        tokens.add(sb.toString().trim());
        return tokens;
    }

    public static Game findGameById(List<Game> games, int id) {
        for (Game g : games) {
            if (g.id == id) {
                return g;
            }
        }
        return null;
    }

    // percorre a primeira árvore em pré-ordem;
    // para cada movimento na árvore 1 (a partir do pai), anexa "  ESQ" ou "  DIR" (duas espaços antes),
    // em seguida pesquisa na árvore2 daquele nó e anexa o caminho da árvore2 (como " esq"/" dir" minúsculos, sem "raiz").
    // Retorna true se encontrou.
    private static boolean percorrerPrimeiraEProcurar(No1 no, String movimentoDoPai, StringBuilder saida, Arvore2 a2, String nomeProcurado) {
        if (no == null) return false;

        // anexar movimento na árvore 1 (se existe)
        if (movimentoDoPai != null) {
            saida.append("  ").append(movimentoDoPai); // duas espaços antes (como no exemplo)
        }

        // pesquisar na segunda árvore deste nó (sem imprimir "raiz")
        if (no.raiz2 != null) {
            StringBuilder cam2 = new StringBuilder();
            boolean achou = a2.pesquisarSemRaiz(no.raiz2, nomeProcurado, cam2);
            if (cam2.length() > 0) {
                // cam2 já tem " esq"/" dir" tokens com um leading space
                saida.append(cam2.toString());
            }
            if (achou) return true;
        }
        // continuar pré-ordem
        if (percorrerPrimeiraEProcurar(no.esq, "ESQ", saida, a2, nomeProcurado)) return true;
        if (percorrerPrimeiraEProcurar(no.dir, "DIR", saida, a2, nomeProcurado)) return true;

        return false;
    }

    public static void main(String[] args) throws Exception {
        // Ler todos os jogos do arquivo
        File fl = new File("/tmp/games.csv");
        Scanner scFile = new Scanner(fl);
        if (scFile.hasNextLine()) scFile.nextLine(); // pular header

        List<Game> allGames = new ArrayList<>();

        while (scFile.hasNextLine()) {
            String line = scFile.nextLine();
            if (line.trim().isEmpty()) continue;
            List<String> t = parseCSVLine(line);
            while (t.size() < 14) t.add("");

            int id = 0;
            try { id = Integer.parseInt(t.get(0)); } catch (Exception e) { continue; }
            String name = t.get(1);
            String releaseDate = t.get(2);
            int estimateOwners = 0;
            try { estimateOwners = Integer.parseInt(t.get(3)); } catch (Exception e) { estimateOwners = 0; }
            double price = 0.0;
            try { price = Double.parseDouble(t.get(4)); } catch (Exception e) { price = 0.0; }
            String[] supportedLanguages = parseArray(t.get(5));
            int metacriticScore = 0;
            try { metacriticScore = Integer.parseInt(t.get(6)); } catch (Exception e) { metacriticScore = 0; }
            double userScore = 0.0;
            try { userScore = Double.parseDouble(t.get(7)); } catch (Exception e) { userScore = 0.0; }
            int achieviments = 0;
            try { achieviments = Integer.parseInt(t.get(8)); } catch (Exception e) { achieviments = 0; }
            String[] publishers = parseArray(t.get(9));
            String[] developers = parseArray(t.get(10));
            String[] categories = parseArray(t.get(11));
            String[] genres = parseArray(t.get(12));
            String[] tags = parseArray(t.get(13));

            allGames.add(new Game(id, name, releaseDate, estimateOwners, price, supportedLanguages,
                    metacriticScore, userScore, achieviments, publishers, developers, categories, genres, tags));
        }
        scFile.close();

        // Primeira árvore (fixa)
        Arvore1 arvore1 = new Arvore1();
        int[] ordem = {7, 3, 11, 1, 5, 9, 13, 0, 2, 4, 6, 8, 10, 12, 14};
        for (int v : ordem) arvore1.inserir(v);

        // Ler IDs até "FIM" e inserir cada jogo na árvore2 do nó correspondente
        Scanner input = new Scanner(System.in);
        Arvore2 arv2 = new Arvore2();

        while (input.hasNextLine()) {
            String line = input.nextLine();
            if (line.equalsIgnoreCase("FIM")) break;
            if (line.trim().isEmpty()) continue;

            int id;
            try {
                id = Integer.parseInt(line.trim());
            } catch (Exception e) {
                continue;
            }

            Game g = findGameById(allGames, id);
            if (g == null) continue;

            int chave = 0;
            try {
                chave = g.estimateOwners % 15;
                if (chave < 0) chave = (chave + 15) % 15;
            } catch (Exception e) {
                chave = 0;
            }

            No1 noDestino = arvore1.buscarChave(chave);
            if (noDestino != null) {
                noDestino.raiz2 = arv2.inserir(noDestino.raiz2, g);
            }
        }

        // Segunda fase: ler nomes a serem pesquisados até "FIM"
        while (input.hasNextLine()) {
            String nome = input.nextLine();
            if (nome.equalsIgnoreCase("FIM")) break;
            if (nome.trim().isEmpty()) continue;

            // Construir saída conforme solicitado
            StringBuilder saida = new StringBuilder();
            // começa sempre com "raiz" e duas espaços em seguida
            saida.append("raiz");

            // Percorrer a primeira árvore (pré-ordem). Para cada nó visitado:
            boolean encontrado = percorrerPrimeiraEProcurar(arvore1.getRaiz(), null, saida, arv2, nome);

            // duas espaços antes do SIM/NAO conforme seu exemplo
            String resultadoFinal = (encontrado ? " SIM" : " NAO");

            // imprimir no formato: => Nome => raiz  ...  SIM/NAO
            System.out.println("=> " + nome + " => " + saida.toString() + "  " + resultadoFinal.trim());
        }

        input.close();
    }
}
