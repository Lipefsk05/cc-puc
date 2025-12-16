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

class TabelaHashRehash {
    private Game[] tabela;
    private PrintWriter logWriter;
    private static final int TAM_TAB = 21;

    public TabelaHashRehash(String matricula) {
        tabela = new Game[TAM_TAB];
        
        try {
            logWriter = new PrintWriter(matricula + "_hashRehash.txt", "UTF-8");
        } catch (Exception e) {
            System.err.println("Erro ao criar arquivo de log: " + e.getMessage());
        }
    }

    private int calcularASCII(String nome) {
        int soma = 0;
        for (int i = 0; i < nome.length(); i++) {
            soma += (int) nome.charAt(i);
        }
        return soma;
    }

    private int hash1(String nome) {
        int ascii = calcularASCII(nome);
        return ascii % TAM_TAB;
    }

    private int hash2(String nome) {
        int ascii = calcularASCII(nome);
        return (ascii + 1) % TAM_TAB;
    }

    public void inserir(Game game) {
        int pos = hash1(game.name);
        
        if (tabela[pos] == null) {
            tabela[pos] = game;
            if (logWriter != null) {
                logWriter.println(game.name + " inserido com sucesso na posicao " + pos + " da tabela");
            }
        } else {
            int pos2 = hash2(game.name);
            
            if (tabela[pos2] == null) {
                tabela[pos2] = game;
                if (logWriter != null) {
                    logWriter.println(game.name + " inserido com sucesso na posicao " + pos2 + " da tabela (rehash)");
                }
            } else {
                if (logWriter != null) {
                    logWriter.println(game.name + " NAO FOI INSERIDO: colisao nas duas posicoes");
                }
            }
        }
    }

    public String pesquisar(String nome) {
        int pos = hash1(nome);
        
        if (tabela[pos] != null && tabela[pos].name.equals(nome)) {
            return nome + ":" + " (Posicao: " + pos + ") SIM";
        }
        
        int pos2 = hash2(nome);
        if (tabela[pos2] != null && tabela[pos2].name.equals(nome)) {
            return nome + ":" + " (Posicao: " + pos2 + ") SIM";
        }
        
        return nome + ":" + " (Posicao: " + pos + ") NAO";
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

        Scanner input = new Scanner(System.in);
        String matricula = "858158";
        TabelaHashRehash tabelaHash = new TabelaHashRehash(matricula);

        while (true) {
            String line = input.nextLine();
            if (line.equalsIgnoreCase("FIM"))
                break;
            int id = Integer.parseInt(line);
            Game game = findGameById(allGames, id);
            if (game != null) {
                tabelaHash.inserir(game);
            }
        }

        while (true) {
            String nome = input.nextLine();
            if (nome.equalsIgnoreCase("FIM"))
                break;
            String resultado = tabelaHash.pesquisar(nome);
            System.out.println(resultado);
        }

        tabelaHash.fecharLog();
        input.close();
    }
}