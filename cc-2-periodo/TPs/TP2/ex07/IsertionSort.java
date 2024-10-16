import java.io.BufferedReader;
import java.io.FileReader;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class IsertionSort {
    
    // static final String CSV_FILE = "../../pokemon.csv";
    static final String CSV_FILE = "/tmp/pokemon.csv";
    static final String inputBreak = "FIM";

    static Pokemon findById(int id, List<Pokemon> allPokemons) {
        for (Pokemon pokemon : allPokemons) {
            if (id == pokemon.getId())
                return pokemon;
        }
        return null;
    }

// Método para realizar a ordenação por inserção em uma lista de Pokémons, baseado na data de captura
public static void insertionSort(List<Pokemon> array) {
    int n = array.size();

    // Itera sobre cada elemento do array a partir do segundo
    for (int i = 1; i < n; i++) {
        Pokemon key = array.get(i);  // O Pokémon atual a ser inserido na posição correta
        int j = i - 1;

        // Move os elementos que têm data de captura posterior à do "key" uma posição para frente
        while (j >= 0 && array.get(j).getCaptureDate().isAfter(key.getCaptureDate())) {
            array.set(j + 1, array.get(j));  // Desloca o Pokémon com data mais recente uma posição à frente
            j--;
        }

        // Insere o "key" na posição correta, de acordo com a data de captura
        array.set(j + 1, key);
    }
}


    public static void main(String[] args) {
        List<Pokemon> allPokemons = Pokemon.readCSV(CSV_FILE);
        List<Pokemon> selectedPokemons = new ArrayList<>();

        Scanner sc = new Scanner(System.in);

        String input;
        while (!(input = sc.nextLine()).equals(inputBreak)) {
            int id = Integer.parseInt(input);
            Pokemon found = findById(id, allPokemons);
            selectedPokemons.add(found);
        }
      insertionSort(selectedPokemons);

      for (Pokemon p : selectedPokemons) {
        
          System.out.println(p);
      }
        
        sc.close();
    }
}

class Pokemon {
    private int id;
    private int generation;
    private String name;
    private String description;
    private List<String> types;
    private List<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private LocalDate captureDate;

    public Pokemon() {
    }

    public Pokemon(int id, int generation, String name, String description, List<String> types, List<String> abilities,
            double weight,
            double height, int captureRate, boolean isLegendary, LocalDate captureDate) {
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;

    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getGeneration() {
        return generation;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public List<String> getTypes() {
        return types;
    }

    public void setTypes(List<String> types) {
        this.types = types;
    }

    public List<String> getAbilities() {
        return abilities;
    }

    public void setAbilities(List<String> abilities) {
        this.abilities = abilities;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public int getCaptureRate() {
        return captureRate;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    public boolean isLegendary() {
        return isLegendary;
    }

    public void setLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    public LocalDate getCaptureDate() {
        return captureDate;
    }

    public void setCaptureDate(LocalDate captureDate) {
        this.captureDate = captureDate;
    }

    @Override
    public String toString() {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        return "[#" + id + " -> " + name + ": " + description + " - " + toStringTypes(types) + " - " +
                ToString(abilities) + " - " + weight + "kg - " + height + "m - " + captureRate + "% - " + isLegendary
                + " - " +
                generation + " gen] - " + captureDate.format(dtf);
    }

    private String ToString(List<String> lista) {
        return String.join(",", lista);
    }

    public String toStringTypes(List<String> lista) {
        return lista.get(1) != null ? "['" + lista.get(0) + "', '" + lista.get(1) + "']" : "['" + lista.get(0) + "']";
    }

    public boolean ehId(int num) {
        return num == id;
    }

    public Pokemon clonar(Pokemon pokemon) {
        return new Pokemon(pokemon.id, pokemon.generation, pokemon.name, pokemon.description, pokemon.types,
                pokemon.abilities, pokemon.weight, pokemon.height, pokemon.captureRate, pokemon.isLegendary,
                pokemon.captureDate);
    }

    public static List<Pokemon> readCSV(String path) {
        List<Pokemon> pokemons = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            String line = br.readLine();
            while (br.ready()) {
                line = br.readLine();
                Pokemon pokemon = parse(line);
                pokemons.add(pokemon);

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return pokemons;
    }

    private static Pokemon parse(String csvLine) {
        String[] dadospok = csvLine.split("\"");
        String habilidades = dadospok[1];
        String[] primeiraParte = dadospok[0].split(",", -1);
        String[] segundaParte = dadospok[2].split(",", -1);

        int id = Integer.parseInt(primeiraParte[0]);
        int generation = Integer.parseInt(primeiraParte[1]);
        String name = primeiraParte[2];
        String description = primeiraParte[3];

        List<String> types = new ArrayList<>();
        types.add(primeiraParte[4]);
        types.add(primeiraParte[5].isEmpty() ? null : primeiraParte[5]);

        List<String> abilities = new ArrayList<>();
        abilities.add(habilidades);

        double weight = segundaParte[1].isEmpty() ? 0 : Double.parseDouble(segundaParte[1]);
        double height = segundaParte[2].isEmpty() ? 0 : Double.parseDouble(segundaParte[2]);
        int captureRate = segundaParte[3].isEmpty() ? 0 : Integer.parseInt(segundaParte[3]);
        boolean isLegendary = segundaParte[4].charAt(0) == '0' ? false : true;
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy");
        LocalDate captureDate = LocalDate.parse(segundaParte[5], dtf);

        Pokemon pokemon = new Pokemon(id, generation, name, description, types, abilities, weight,
                height, captureRate, isLegendary, captureDate);
        return pokemon;
    }
}