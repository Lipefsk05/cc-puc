import java.util.*;
import java.io.*;
import java.text.*;

class Game {
    // ... (mantenha a classe Game igual)
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

class No {
    public Game game;
    public No esq;
    public No dir;

    public No(Game game) {
        this.game = game;
        this.esq = null;
        this.dir = null;
    }
}

class ArvoreBinaria {
    private No raiz;
    private PrintWriter logWriter;

    public ArvoreBinaria() {
        raiz = null;
        try {
            logWriter = new PrintWriter("858158_arvoreBinaria.txt", "UTF-8");
        } catch (Exception e) {
            System.err.println("Erro ao criar arquivo de log: " + e.getMessage());
        }
    }

    public void inserir(Game game) {
        raiz = inserirRec(raiz, game);
    }

    private No inserirRec(No no, Game game) {
        if (no == null) {
            logWriter.println("INSERCAO: " + game.name + " inserido com sucesso!");
            return new No(game);
        }

        int comparacao = game.name.compareTo(no.game.name);

        if (comparacao < 0) {
            no.esq = inserirRec(no.esq, game);
        } else if (comparacao > 0) {
            no.dir = inserirRec(no.dir, game);
        } else {
            logWriter.println("INSERCAO: " + game.name + " ja existente!");
        }

        return no;
    }

    public String pesquisar(String nome) {
        StringBuilder caminho = new StringBuilder("raiz");
        boolean encontrado = pesquisarRec(raiz, nome, caminho, true);

        // Formatar a saída conforme especificado: nome: =>caminho SIM
        String resultado = nome + ": =>" + caminho.toString() + (encontrado ? " SIM" : " NAO");

        return resultado;
    }

    private boolean pesquisarRec(No no, String nome, StringBuilder caminho, boolean primeiro) {
        if (no == null) {
            return false;
        }

        int comparacao = nome.compareTo(no.game.name);

        if (comparacao == 0) {
            return true;
        } else if (comparacao < 0) {
            caminho.append(" esq");
            return pesquisarRec(no.esq, nome, caminho, false);
        } else {
            caminho.append(" dir");
            return pesquisarRec(no.dir, nome, caminho, false);
        }
    }

    public void fecharLog() {
        if (logWriter != null) {
            logWriter.close();
        }
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
        for (char c : line.toCharArray()) {
            if (c == '"')
                inQuotes = !inQuotes;
            else if (c == ',' && !inQuotes) {
                tokens.add(sb.toString().trim());
                sb.setLength(0);
            } else
                sb.append(c);
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

    public static void main(String[] args) throws Exception {
        // Ler todos os jogos do arquivo
        File fl = new File("/tmp/games.csv");
        Scanner sc = new Scanner(fl);
        if (sc.hasNextLine())
            sc.nextLine();

        List<Game> allGames = new ArrayList<>();

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            List<String> t = parseCSVLine(line);
            int id = Integer.parseInt(t.get(0));
            String name = t.get(1);
            String releaseDate = t.get(2);
            int estimateOwners = Integer.parseInt(t.get(3));
            double price = Double.parseDouble(t.get(4));
            String[] supportedLanguages = parseArray(t.get(5));
            int metacriticScore = Integer.parseInt(t.get(6));
            double userScore = Double.parseDouble(t.get(7));
            int achieviments = Integer.parseInt(t.get(8));
            String[] publishers = parseArray(t.get(9));
            String[] developers = parseArray(t.get(10));
            String[] categories = parseArray(t.get(11));
            String[] genres = parseArray(t.get(12));
            String[] tags = parseArray(t.get(13));
            allGames.add(new Game(id, name, releaseDate, estimateOwners, price, supportedLanguages,
                    metacriticScore, userScore, achieviments, publishers, developers, categories, genres, tags));
        }
        sc.close();

        // Primeira parte: ler IDs até FIM e inserir na árvore
        Scanner input = new Scanner(System.in);
        ArvoreBinaria arvore = new ArvoreBinaria();

        while (true) {
            String line = input.nextLine();
            if (line.equalsIgnoreCase("FIM"))
                break;
            int id = Integer.parseInt(line);
            Game game = findGameById(allGames, id);
            if (game != null) {
                arvore.inserir(game);
            }
        }

        // Segunda parte: pesquisar nomes na árvore
        while (true) {
            String nome = input.nextLine();
            if (nome.equalsIgnoreCase("FIM"))
                break;
            String resultado = arvore.pesquisar(nome);
            System.out.println(resultado);
        }

        arvore.fecharLog();
        input.close();
    }
}