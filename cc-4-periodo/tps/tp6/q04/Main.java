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

class Celula {
    public Game game;
    public Celula prox;

    public Celula() {
        this.game = null;
        this.prox = null;
    }

    public Celula(Game game) {
        this.game = game;
        this.prox = null;
    }
}

class Fila {
    private Celula primeiro;
    private Celula ultimo;
    private int n;

    public Fila() {
        primeiro = new Celula();
        ultimo = primeiro;
        n = 0;
    }

    public void enfileirar(Game game) {
        ultimo.prox = new Celula(game);
        ultimo = ultimo.prox;
        n++;
    }

    public Game desenfileirar() {
        if (primeiro == ultimo) {
            System.out.println("Erro ao desenfileirar: fila vazia!");
            return null;
        }
        Celula tmp = primeiro.prox;
        Game resp = tmp.game;
        primeiro.prox = tmp.prox;
        if (tmp == ultimo) {
            ultimo = primeiro;
        }
        n--;
        return resp;
    }

    public void mostrar() {
        int j = 0;
        for (Celula i = primeiro.prox; i != null; i = i.prox, j++) {
            System.out.print("[" + j + "] ");
            i.game.printFormatted();
        }
    }

    public int tamanho() {
        return n;
    }

    public boolean vazia() {
        return primeiro == ultimo;
    }
}

public class Main {
    private static String[] parseArray(String s) {
        s = s.trim();
        if (s.startsWith("[") && s.endsWith("]")) {
            s = s.substring(1, s.length() - 1);
        }
        if (s.isEmpty()) return new String[0];

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
            if (c == '"') inQuotes = !inQuotes;
            else if (c == ',' && !inQuotes) {
                tokens.add(sb.toString().trim());
                sb.setLength(0);
            } else sb.append(c);
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
        if (sc.hasNextLine()) sc.nextLine();

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

        // Primeira parte: ler IDs até FIM
        Scanner input = new Scanner(System.in);
        Fila fila = new Fila();

        while (true) {
            String line = input.nextLine();
            if (line.equalsIgnoreCase("FIM")) break;
            int id = Integer.parseInt(line);
            Game game = findGameById(allGames, id);
            if (game != null) {
                fila.enfileirar(game);
            }
        }

        // Segunda parte: ler operações
        int n = Integer.parseInt(input.nextLine());
        for (int i = 0; i < n; i++) {
            String line = input.nextLine();
            String[] parts = line.split(" ");
            String comando = parts[0];

            try {
                if (comando.equals("I")) {
                    int id = Integer.parseInt(parts[1]);
                    Game game = findGameById(allGames, id);
                    if (game != null) {
                        fila.enfileirar(game);
                    }
                } else if (comando.equals("R")) {
                    Game removido = fila.desenfileirar();
                    if (removido != null) {
                        System.out.println("(R) " + removido.name);
                    }
                }
            } catch (Exception e) {
                System.err.println("Erro ao executar comando: " + line + " - " + e.getMessage());
            }
        }

        // Mostrar fila final
        fila.mostrar();
        input.close();
    }
}