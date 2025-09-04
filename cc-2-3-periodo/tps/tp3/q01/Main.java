// package ex01;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Represents a dynamic list of Show objects.
 * The list is implemented using a fixed-size array.
 */
class Lista {
    private Show[] elements;
    private int size;
    private static final int INITIAL_CAPACITY = 1368; // Based on the dataset size

    public Lista() {
        this.elements = new Show[INITIAL_CAPACITY];
        this.size = 0;
    }

    // Inserts an element at the beginning of the list.
    public void inserirInicio(Show show) {
        if (size >= elements.length) {
            System.err.println("Error: List is full.");
            return;
        }
        // Shift elements to the right
        System.arraycopy(elements, 0, elements, 1, size);
        elements[0] = show;
        size++;
    }

    // Inserts an element at a specific position.
    public void inserir(Show show, int position) {
        if (size >= elements.length) {
            System.err.println("Error: List is full.");
            return;
        }
        if (position < 0 || position > size) {
            System.err.println("Error: Invalid position for insertion.");
            return;
        }
        // Shift elements from the position to the right
        System.arraycopy(elements, position, elements, position + 1, size - position);
        elements[position] = show;
        size++;
    }

    // Inserts an element at the end of the list.
    public void inserirFim(Show show) {
        if (size >= elements.length) {
            System.err.println("Error: List is full.");
            return;
        }
        elements[size++] = show;
    }

    // Removes and returns the element from the beginning of the list.
    public Show removerInicio() {
        if (size == 0) {
            System.err.println("Error: List is empty.");
            return null;
        }
        Show removedItem = elements[0];
        size--;
        // Shift elements to the left
        System.arraycopy(elements, 1, elements, 0, size);
        return removedItem;
    }

    // Removes and returns the element from a specific position.
    public Show remover(int position) {
        if (size == 0 || position < 0 || position >= size) {
            System.err.println("Error: Invalid position for removal.");
            return null;
        }
        Show removedItem = elements[position];
        int itemsToMove = size - position - 1;
        if (itemsToMove > 0) {
            // Shift elements from the right of the position to the left
            System.arraycopy(elements, position + 1, elements, position, itemsToMove);
        }
        size--;
        return removedItem;
    }

    // Removes and returns the element from the end of the list.
    public Show removerFim() {
        if (size == 0) {
            System.err.println("Error: List is empty.");
            return null;
        }
        return elements[--size];
    }

    // Displays the show_id of all elements in the list.
    public void mostrar() {
        System.out.print("[ ");
        for (int i = 0; i < size; i++) {
            System.out.print(elements[i].getShow_id() + " ");
        }
        System.out.println("]");
    }

    // Prints the full details of all shows currently in the list.
    public void mostraRestantes() {
        for (int i = 0; i < size; i++) {
            elements[i].imprimir();
        }
    }
}


/**
 * Represents a single TV show or Movie from the dataset.
 */
class Show {
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private LocalDate date_added;
    private Integer release_year;
    private String rating;
    private String duration;
    private String[] listed_in;

    // Default constructor
    public Show() {
        this.show_id = "";
        this.type = "";
        this.title = "";
        this.director = "";
        this.cast = new String[0];
        this.country = "";
        this.date_added = null;
        this.release_year = 0;
        this.rating = "";
        this.duration = "";
        this.listed_in = new String[0];
    }

    // Parameterized constructor
    public Show(String show_id, String type, String title, String director, String[] cast, String country,
                LocalDate date_added, Integer release_year, String rating, String duration, String[] listed_in) {
        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.setCast(cast); // Use setter to ensure sorting
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.rating = rating;
        this.duration = duration;
        this.setListedIn(listed_in); // Use setter to ensure sorting
    }

    // Getters and Setters
    public String getShow_id() { return show_id; }
    public void setShow_id(String show_id) { this.show_id = show_id; }

    public String getType() { return type; }
    public void setType(String type) { this.type = type; }

    public String getTitle() { return title; }
    public void setTitle(String title) { this.title = title; }

    public String getDirector() { return director; }
    public void setDirector(String director) { this.director = director; }

    public String[] getCast() { return cast; }
    public void setCast(String[] cast) {
        if (cast != null) {
            Arrays.sort(cast);
        }
        this.cast = cast;
    }

    public String getCountry() { return country; }
    public void setCountry(String country) { this.country = country; }

    public LocalDate getDateAdded() { return date_added; }
    public void setDateAdded(LocalDate date_added) { this.date_added = date_added; }

    public Integer getReleaseYear() { return release_year; }
    public void setReleaseYear(Integer release_year) { this.release_year = release_year; }

    public String getRating() { return rating; }
    public void setRating(String rating) { this.rating = rating; }

    public String getDuration() { return duration; }
    public void setDuration(String duration) { this.duration = duration; }

    public String[] getListedIn() { return listed_in; }
    public void setListedIn(String[] listed_in) {
        if (listed_in != null) {
            Arrays.sort(listed_in);
        }
        this.listed_in = listed_in;
    }
    
    // Helper methods to format array fields into strings.
    public String castToString() {
        return (this.cast != null && this.cast.length > 0) ? String.join(", ", this.cast) : "";
    }

    public String listed_inToString() {
        return (this.listed_in != null && this.listed_in.length > 0) ? String.join(", ", this.listed_in) : "";
    }

    // Prints a formatted representation of the Show object.
    public void imprimir() {
        String formattedDate = "NaN";
        if (this.date_added != null) {
            // A specific date format is required for the output
            if (!this.date_added.equals(LocalDate.of(1900, 3, 1))) {
                 DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                 formattedDate = date_added.format(formatter);
            }
        }

        System.out.println("=> " + show_id + " ## " + title + " ## " + type + " ## " + director
                + " ## [" + castToString() + "] ## " + country + " ## " + formattedDate + " ## " + release_year
                + " ## " + rating + " ## " + duration + " ## [" + listed_inToString() + "] ##");
    }

    // Parses a CSV line to populate the Show object's fields.
    public void ler(String line) {
        String[] fields = new String[11];
        int fieldIndex = 0;
        StringBuilder fieldBuilder = new StringBuilder();
        
        // Custom parser to handle quotes and empty fields correctly.
        for (int i = 0; i < line.length() && fieldIndex < 11; i++) {
            char c = line.charAt(i);
            if (c == '"') {
                i++; // Skip the opening quote
                while (i < line.length() && line.charAt(i) != '"') {
                    fieldBuilder.append(line.charAt(i++));
                }
            } else if (c == ',') {
                 if (fieldBuilder.length() == 0 && (i > 0 && line.charAt(i-1) == ',')) {
                     fields[fieldIndex++] = "NaN";
                 } else {
                     fields[fieldIndex++] = fieldBuilder.toString();
                     fieldBuilder.setLength(0); // Reset for next field
                 }
            } else {
                fieldBuilder.append(c);
            }
        }
        // Add the last field
        if (fieldIndex < 11) {
            fields[fieldIndex] = fieldBuilder.toString();
        }

        // Assign parsed fields to the object properties
        setShow_id(fields[0]);
        setType(fields[1]);
        setTitle(fields[2]);
        setDirector(fields[3]);
        setCast(fields[4] != null ? fields[4].split(", ") : new String[0]);
        setCountry(fields[5]);
        
        if (fields[6] != null && !fields[6].equals("NaN") && !fields[6].trim().isEmpty()) {
            DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
            setDateAdded(LocalDate.parse(fields[6], dateFormatter));
        } else {
            // Specific behavior from original code for null/NaN dates
            setDateAdded(LocalDate.of(1900, 3, 1));
        }
        
        setReleaseYear(Integer.parseInt(fields[7]));
        setRating(fields[8]);
        setDuration(fields[9]);
        setListedIn(fields[10] != null ? fields[10].split(", ") : new String[0]);
    }

    // Creates a clone of the current Show object.
    @Override
    public Show clone() {
        return new Show(this.show_id, this.type, this.title, this.director, this.cast, this.country,
                this.date_added, this.release_year, this.rating, this.duration, this.listed_in);
    }
}


/**
 * Main application class to process Disney+ show data.
 */
public class Main {
    private static final String CSV_FILE_PATH = "/tmp/disneyplus.csv";
    private static final int MAX_SHOWS = 1368;

    public static void main(String[] args) {
        Show[] allShows = new Show[MAX_SHOWS];
        
        // Use try-with-resources to ensure scanners are closed automatically
        try (Scanner fileScanner = new Scanner(new File(CSV_FILE_PATH), "UTF-8")) {
            fileScanner.nextLine(); // Skip header row

            for (int i = 0; i < MAX_SHOWS && fileScanner.hasNextLine(); i++) {
                String line = fileScanner.nextLine();
                allShows[i] = new Show();
                allShows[i].ler(line);
            }
        } catch (FileNotFoundException e) {
            System.err.println("Error: CSV file not found at " + CSV_FILE_PATH);
            e.printStackTrace();
            return;
        }

        Lista lista_shows = new Lista();
        try (Scanner consoleScanner = new Scanner(System.in)) {
            String inputId;
            while (!(inputId = consoleScanner.nextLine()).equals("FIM")) {
                int id = Integer.parseInt(inputId.substring(1)); // Remove 's' prefix and parse
                if (id > 0 && id <= MAX_SHOWS) {
                    lista_shows.inserirFim(allShows[id - 1].clone());
                }
            }

            int numOperations = consoleScanner.nextInt();
            for (int i = 0; i < numOperations; i++) {
                String operation = consoleScanner.next();
                int id;
                int pos;

                switch (operation) {
                    case "II":
                        id = Integer.parseInt(consoleScanner.next().substring(1));
                        lista_shows.inserirInicio(allShows[id - 1].clone());
                        break;
                    case "IF":
                        id = Integer.parseInt(consoleScanner.next().substring(1));
                        lista_shows.inserirFim(allShows[id - 1].clone());
                        break;
                    case "I*":
                        pos = consoleScanner.nextInt();
                        id = Integer.parseInt(consoleScanner.next().substring(1));
                        lista_shows.inserir(allShows[id - 1].clone(), pos);
                        break;
                    case "RI":
                        System.out.println("(R) " + lista_shows.removerInicio().getTitle());
                        break;
                    case "RF":
                        System.out.println("(R) " + lista_shows.removerFim().getTitle());
                        break;
                    case "R*":
                        pos = consoleScanner.nextInt();
                        System.out.println("(R) " + lista_shows.remover(pos).getTitle());
                        break;
                    default:
                        System.err.println("Unknown operation: " + operation);
                        break;
                }
            }
        } catch (Exception e) {
            System.err.println("An error occurred during input processing.");
            e.printStackTrace();
        }

        lista_shows.mostraRestantes();
    }
}