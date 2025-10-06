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
            // exemplo de formato CSV: "Oct 18, 2018"
            SimpleDateFormat inputFormat = new SimpleDateFormat("MMM dd, yyyy", java.util.Locale.ENGLISH);
            SimpleDateFormat outputFormat = new SimpleDateFormat("dd/MM/yyyy");
            Date date = inputFormat.parse(dateStr);
            return outputFormat.format(date);
        } catch (ParseException e) {
            return dateStr; // retorna original se não conseguir parsear
        }
    }

    private String arrayToString(String[] arr) {
        if (arr == null || arr.length == 0)
            return "[]";

        StringBuilder sb = new StringBuilder();
        sb.append("[");
        for (int i = 0; i < arr.length; i++) {
            sb.append(arr[i].trim()); // remove espaços extras
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
            // remove aspas simples ou duplas que ainda estejam ao redor
            items[i] = items[i].replaceAll("^'+|'+$", ""); // aspas simples
            items[i] = items[i].replaceAll("^\"+|\"+$", ""); // aspas duplas
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

    public static void main(String[] args) throws FileNotFoundException {
        File fl = new File("/tmp/games.csv");
        Scanner sc = new Scanner(fl);

        // Pular cabeçalho
        if (sc.hasNextLine())
            sc.nextLine();

        List<Game> gamesList = new ArrayList<>();

        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            List<String> tokens = parseCSVLine(line);

            int id = Integer.parseInt(tokens.get(0));
            String name = tokens.get(1);
            String releaseDate = tokens.get(2);
            int estimateOwners = Integer.parseInt(tokens.get(3));
            double price = Double.parseDouble(tokens.get(4));
            String[] supportedLanguages = parseArray(tokens.get(5));
            int metacriticScore = Integer.parseInt(tokens.get(6));
            double userScore = Double.parseDouble(tokens.get(7));
            int achieviments = Integer.parseInt(tokens.get(8));
            String[] publishers = parseArray(tokens.get(9));
            String[] developers = parseArray(tokens.get(10));
            String[] categories = parseArray(tokens.get(11));
            String[] genres = parseArray(tokens.get(12));
            String[] tags = parseArray(tokens.get(13));

            gamesList.add(new Game(id, name, releaseDate, estimateOwners, price, supportedLanguages,
                    metacriticScore, userScore, achieviments, publishers, developers,
                    categories, genres, tags));
        }

        Game[] games = gamesList.toArray(new Game[0]);

        // Ler IDs até digitar FIM
        Scanner input = new Scanner(System.in);
        while (true) {
            String line = input.nextLine();
            if (line.equalsIgnoreCase("FIM"))
                break;

            try {
                int searchId = Integer.parseInt(line);
                boolean found = false;
                for (Game g : games) {
                    if (g.id == searchId) {
                        g.printFormatted();
                        found = true;
                        break;
                    }
                }
            } catch (NumberFormatException e) {
            }
        }
    }

}