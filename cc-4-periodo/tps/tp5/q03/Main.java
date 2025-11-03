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

    // ===== Heapsort =====
    private static int comparisons = 0;
    private static int movements = 0;

    private static void heapify(Game[] arr, int n, int i) {
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if (l < n) {
            comparisons++;
            if (arr[l].estimateOwners > arr[largest].estimateOwners ||
               (arr[l].estimateOwners == arr[largest].estimateOwners && arr[l].id > arr[largest].id)) {
                largest = l;
            }
        }
        if (r < n) {
            comparisons++;
            if (arr[r].estimateOwners > arr[largest].estimateOwners ||
               (arr[r].estimateOwners == arr[largest].estimateOwners && arr[r].id > arr[largest].id)) {
                largest = r;
            }
        }

        if (largest != i) {
            Game temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            movements += 3;
            heapify(arr, n, largest);
        }
    }

    private static void heapSort(Game[] arr) {
        int n = arr.length;

        for (int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);

        for (int i = n - 1; i >= 0; i--) {
            Game temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            movements += 3;

            heapify(arr, i, 0);
        }
    }

    public static void main(String[] args) throws Exception {
        long startTime = System.currentTimeMillis();

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
            allGames.add(new Game(id,name,releaseDate,estimateOwners,price,supportedLanguages,
                    metacriticScore,userScore,achieviments,publishers,developers,categories,genres,tags));
        }

        Scanner input = new Scanner(System.in);
        List<Game> selectedGames = new ArrayList<>();

        while(true) {
            String line = input.nextLine();
            if(line.equalsIgnoreCase("FIM")) break;
            int id = Integer.parseInt(line);
            for(Game g: allGames) {
                if(g.id == id) {
                    selectedGames.add(g);
                    break;
                }
            }
        }

        Game[] games = selectedGames.toArray(new Game[0]);

        heapSort(games);

        for(Game g: games) g.printFormatted();

        long endTime = System.currentTimeMillis();
        double elapsed = (endTime - startTime)/1000.0;

        FileWriter fw = new FileWriter("858158_heapsort.txt");
        fw.write("858158\t"+comparisons+"\t"+movements+"\t"+elapsed);
        fw.close();
    }
}
