import java.io.BufferedReader;
import java.io.FileReader;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class MergeSort {
    
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

    public static void main(String[] args) {
        List<Pokemon> allPokemons = Pokemon.readCSV(CSV_FILE);
        List<Pokemon> selectedPokemons = new ArrayList<>();

        Scanner sc = new Scanner(System.in);

        String input;
        while (!(input = sc.nextLine()).equals(inputBreak)) {
            int id = Integer.parseInt(input);
            Pokemon found = findById(id, allPokemons);
            if (found != null) {
                selectedPokemons.add(found);
            }
        }

        Mergesort mergeSort = new Mergesort(selectedPokemons);
        mergeSort.sort();

        for (Pokemon p : selectedPokemons) {
            System.out.println(p);
        }

        sc.close();
    }
}

class Mergesort {
    private List<Pokemon> pokemons;

    public Mergesort(List<Pokemon> pokemons) {
        this.pokemons = pokemons;
    }

    public void sort() {
        mergesort(0, pokemons.size() - 1);
    }

    private void mergesort(int esq, int dir) {
        if (esq < dir) {
            int meio = (esq + dir) / 2;
            mergesort(esq, meio);
            mergesort(meio + 1, dir);
            intercalar(esq, meio, dir);
        }
    }

    public void intercalar(int esq, int meio, int dir) {
        int n1 = meio - esq + 1;
        int n2 = dir - meio;

        List<Pokemon> a1 = new ArrayList<>(n1);
        List<Pokemon> a2 = new ArrayList<>(n2);

        for (int i = 0; i < n1; i++) {
            a1.add(pokemons.get(esq + i));
        }

        for (int j = 0; j < n2; j++) {
            a2.add(pokemons.get(meio + 1 + j));
        }

        a1.add(null); // Sentinel
        a2.add(null); // Sentinel

        int i = 0, j = 0;
        for (int k = esq; k <= dir; k++) {
            if (a1.get(i) == null) {
                pokemons.set(k, a2.get(j++));
            } else if (a2.get(j) == null) {
                pokemons.set(k, a1.get(i++));
            } else if (a1.get(i).getTypes().get(0).compareTo(a2.get(j).getTypes().get(0)) < 0) {
                pokemons.set(k, a1.get(i++));
            } else if (a1.get(i).getTypes().get(0).compareTo(a2.get(j).getTypes().get(0)) > 0) {
                pokemons.set(k, a2.get(j++));
            } else { // Types are equal, compare by name
                if (a1.get(i).getName().compareTo(a2.get(j).getName()) <= 0) {
                    pokemons.set(k, a1.get(i++));
                } else {
                    pokemons.set(k, a2.get(j++));
                }
            }
        }
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