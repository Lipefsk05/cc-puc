import java.io.BufferedReader;
import java.io.FileReader;
import java.util.*;

class Show {
    private String SHOW_ID;
    private String TYPE;
    private String TITTLE;
    private String DIRECTOR;
    private String[] CAST;
    private String COUNTRY;
    private String DATE_ADDED;
    private int RELEASE_YEAR;
    private String RATING;
    private String DURATION;
    private String[] LISTENED_IN;

    public Show() {
        SHOW_ID = "";
        TYPE = "";
        TITTLE = "";
        DIRECTOR = "";
        CAST = new String[0];
        COUNTRY = "";
        DATE_ADDED = "";
        RELEASE_YEAR = 0;
        RATING = "";
        DURATION = "";
        LISTENED_IN = new String[0];
    }
    
    public Show(String SHOW_ID, String TYPE, String TITTLE, String DIRECTOR, String[] CAST, String COUNTRY, String DATE_ADDED, int RELEASE_YEAR, String RATING, String DURATION, String[] LISTENED_IN) {
        this.SHOW_ID = SHOW_ID;
        this.TYPE = TYPE;
        this.TITTLE = TITTLE;
        this.DIRECTOR = DIRECTOR;
        this.CAST = CAST;
        this.COUNTRY = COUNTRY;
        this.DATE_ADDED = DATE_ADDED;
        this.RELEASE_YEAR = RELEASE_YEAR;
        this.RATING = RATING;
        this.DURATION = DURATION;
        this.LISTENED_IN = LISTENED_IN;
    }

    public String getShowId() { return SHOW_ID; }
    public void setShowId(String SHOW_ID) { this.SHOW_ID = SHOW_ID; }

    public String getType() { return TYPE; }
    public void setType(String TYPE) { this.TYPE = TYPE; }

    public String getTittle() { return TITTLE; }
    public void setTittle(String TITTLE) { this.TITTLE = TITTLE; }

    public String getDirector() { return DIRECTOR; }
    public void setDirector(String DIRECTOR) { this.DIRECTOR = DIRECTOR; }

    public String[] getCast() { return CAST; }
    public void setCast(String[] CAST) { this.CAST = CAST; }

    public String getCountry() { return COUNTRY; }
    public void setCountry(String COUNTRY) { this.COUNTRY = COUNTRY; }

    public String getDate() { return DATE_ADDED; }
    public void setDate(String DATE_ADDED) { this.DATE_ADDED = DATE_ADDED; }

    public int getReleaseYear() { return RELEASE_YEAR; }
    public void setReleaseYear(int RELEASE_YEAR) { this.RELEASE_YEAR = RELEASE_YEAR; }

    public String getRating() { return RATING; }
    public void setRating(String RATING) { this.RATING = RATING; }

    public String getDuration() { return DURATION; }
    public void setDuration(String DURATION) { this.DURATION = DURATION; }

    public String[] getListenedIn() { return LISTENED_IN; }
    public void setListenedIn(String[] LISTENED_IN) { this.LISTENED_IN = LISTENED_IN; }

    public Show clone() {
        return new Show(
            this.SHOW_ID,
            this.TYPE,
            this.TITTLE,
            this.DIRECTOR,
            Arrays.copyOf(this.CAST, this.CAST.length),
            this.COUNTRY,
            this.DATE_ADDED,
            this.RELEASE_YEAR,
            this.RATING,
            this.DURATION,
            Arrays.copyOf(this.LISTENED_IN, this.LISTENED_IN.length)
        );
    }
    
    public void ler(Scanner in) {
        System.out.print("ID: ");
        this.SHOW_ID = in.nextLine();
    
        System.out.print("Tipo: ");
        this.TYPE = in.nextLine();
    
        System.out.print("Título: ");
        this.TITTLE = in.nextLine();
    
        System.out.print("Diretor: ");
        this.DIRECTOR = in.nextLine();
    
        System.out.print("Elenco (separado por vírgulas): ");
        this.CAST = in.nextLine().split(",\\s*");
    
        System.out.print("País: ");
        this.COUNTRY = in.nextLine();
    
        System.out.print("Data adicionada: ");
        this.DATE_ADDED = in.nextLine();
    
        System.out.print("Ano de lançamento: ");
        this.RELEASE_YEAR = Integer.parseInt(in.nextLine());
    
        System.out.print("Classificação: ");
        this.RATING = in.nextLine();
    
        System.out.print("Duração: ");
        this.DURATION = in.nextLine();
    
        System.out.print("Idiomas (separado por vírgulas): ");
        this.LISTENED_IN = in.nextLine().split(",\\s*");
    }
    
    public void imprimir() {
        String castStr = (CAST.length > 0) ? String.join(", ", CAST) : "NaN";
        String listenedStr = (LISTENED_IN.length > 0) ? String.join(", ", LISTENED_IN) : "NaN";
    
        System.out.println("=> " +
            (SHOW_ID.isEmpty() ? "NaN" : SHOW_ID) + " ## " +
            (TITTLE.equals("NaN") ? TITTLE : TITTLE.replace("\"", "")) + " ## " +
            (TYPE.isEmpty() ? "NaN" : TYPE) + " ## " +
            (DIRECTOR.isEmpty() ? "NaN" : DIRECTOR) + " ## " +
            "[" + castStr + "] ## " +
            (COUNTRY.isEmpty() ? "NaN" : COUNTRY) + " ## " +
            (DATE_ADDED.equals("NaN") ? DATE_ADDED : DATE_ADDED.replace("\"", "")) + " ## " +
            (RELEASE_YEAR == 0 ? "NaN" : RELEASE_YEAR) + " ## " +
            (RATING.isEmpty() ? "NaN" : RATING) + " ## " +
            (DURATION.isEmpty() ? "NaN" : DURATION) + " ## " +
            "[" + listenedStr + "] ##"
        );
    }
}

public class Main {
    
    public static Show setFilme(String[] filmeSplited) {
        Show filme = new Show();
    
        filme.setShowId(filmeSplited[0].replace("\"", ""));
        filme.setType(filmeSplited[1].replace("\"", ""));
        filme.setTittle(filmeSplited[2].replace("\"", ""));
        filme.setDirector(filmeSplited[3].replace("\"", ""));
    
        // Processar o CAST
        if (filmeSplited[4].equals("NaN")) {
            filme.setCast(new String[0]);
        } else {
            String[] cast = filmeSplited[4].replace("\"", "").split(",\\s*");
            Arrays.sort(cast);
            filme.setCast(cast);
        }
    
        filme.setCountry(filmeSplited[5].replace("\"", ""));
        filme.setDate(filmeSplited[6].replace("\"", ""));
    
        try {
            filme.setReleaseYear(Integer.parseInt(filmeSplited[7].replace("\"", "")));
        } catch (NumberFormatException e) {
            filme.setReleaseYear(0);
        }
    
        filme.setRating(filmeSplited[8].replace("\"", ""));
        filme.setDuration(filmeSplited[9].replace("\"", ""));
    
        // Processar LISTENED_IN
        if (filmeSplited[10].equals("NaN")) {
            filme.setListenedIn(new String[0]);
        } else {
            String[] listened = filmeSplited[10].replace("\"", "").split(",\\s*");
            Arrays.sort(listened);
            filme.setListenedIn(listened);
        }
    
        return filme;
    }
    
    
    
    public static void main(String[] args) {
        Map<String, Show> filmes = new HashMap<>();

        try (BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"))) {
            String linha;
            br.readLine();

            while ((linha = br.readLine()) != null) {
                String[] partes = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);

                for (int i = 0; i < partes.length; i++) {
                    if (partes[i].trim().isEmpty()) {
                        partes[i] = "NaN";
                    }
                }

                if (partes.length >= 11) {
                    Show filme = setFilme(partes);
                    filmes.put(filme.getShowId(), filme);
                }
            }

        } catch (Exception e) {
            System.out.println("Erro ao ler o arquivo: " + e);
        }

        Scanner sc = new Scanner(System.in);
        while (true) {
            String entrada = sc.nextLine();
            if (entrada.equals("FIM")) break;

            Show s = filmes.getOrDefault(entrada, new Show());
            s.imprimir();
        }
        sc.close();
    }
}
