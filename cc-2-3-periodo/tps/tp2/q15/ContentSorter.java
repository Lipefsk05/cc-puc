// package ex15;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.time.format.DateTimeFormatter;
import java.time.LocalDate;
import java.io.IOException;
import java.io.RandomAccessFile;

class MediaContent {
    private String id;
    private String contentType;
    private String name;
    private String directorName;
    private String[] actors;
    private String country;
    private LocalDate addedDate;
    private Integer releaseYear;
    private String contentRating;
    private String runtime;
    private String[] genres;

    public MediaContent() {
        this.id = "";
        this.contentType = "";
        this.name = "";
        this.directorName = "";
        this.actors = new String[1];
        this.country = "";
        this.addedDate = LocalDate.now();
        this.releaseYear = 0;
        this.contentRating = "";
        this.runtime = "";
        this.genres = new String[1];
    }

    public MediaContent(String id, String contentType, String name, String directorName, String[] actors, String country,
            LocalDate addedDate, Integer releaseYear, String contentRating, String runtime, String[] genres) {
        this.id = id;
        this.contentType = contentType;
        this.name = name;
        this.directorName = directorName;
        this.actors = actors;
        this.country = country;
        this.addedDate = addedDate;
        this.releaseYear = releaseYear;
        this.contentRating = contentRating;
        this.runtime = runtime;
        this.genres = genres;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getId() {
        return id;
    }

    public void setContentType(String contentType) {
        this.contentType = contentType;
    }

    public String getContentType() {
        return contentType;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setDirectorName(String directorName) {
        this.directorName = directorName;
    }

    public String getDirectorName() {
        return this.directorName;
    }

    public void setActors(String[] actors) {
        int length = actors.length;
        for(int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - i - 1; j++){
                String current = actors[j];
                String next = actors[j + 1];

                if(current.compareTo(next) > 0){
                    String temp = actors[j];
                    actors[j] = actors[j + 1];
                    actors[j + 1] = temp;
                }
            }
        }
        this.actors = actors;
    }

    public String[] getActors() {
        return this.actors;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getCountry() {
        return this.country;
    }

    public void setAddedDate(LocalDate addedDate) {
        this.addedDate = addedDate;
    }

    public LocalDate getAddedDate() {
        return this.addedDate;
    }

    public void setReleaseYear(Integer releaseYear) {
        this.releaseYear = releaseYear;
    }

    public Integer getReleaseYear() {
        return this.releaseYear;
    }

    public void setContentRating(String contentRating) {
        this.contentRating = contentRating;
    }

    public String getContentRating() {
        return this.contentRating;
    }

    public void setRuntime(String runtime) {
        this.runtime = runtime;
    }

    public String getRuntime() {
        return this.runtime;
    }

    public void setGenres(String[] genres) {
        int length = genres.length;
        for(int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - i - 1; j++){
                String current = genres[j];
                String next = genres[j + 1];

                if(current.compareTo(next) > 0){
                    String temp = genres[j];
                    genres[j] = genres[j + 1];
                    genres[j + 1] = temp;
                }
            }
        }
        this.genres = genres;
    }

    public String[] getGenres() {
        return this.genres;
    }

    public String actorsToString(){
        Integer count = this.actors.length;

        StringBuilder builder = new StringBuilder();

        for(int i = 0; i < count; i++){
            builder.append(this.actors[i]);
            if(i != count - 1){
                builder.append(", ");
            }
        }

        return new String(builder);
    }
    
    public String genresToString(){
        Integer count = this.genres.length;
        
        StringBuilder builder = new StringBuilder();

        for(int i = 0; i < count; i++){
            builder.append(this.genres[i]);
            if(i != count - 1){
                builder.append(", ");
            }
        }

        return new String(builder);
    }

    public void display() {
        String dateString = "NaN";
        if(this.addedDate != null){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
            dateString = addedDate.format(formatter);
        }
        System.out.println("=> " + id + " ## " + name + " ## " + contentType + " ## " + directorName 
            + " ## [" + actorsToString() +"] ## " + country + " ## " + dateString + " ## " + releaseYear 
            + " ## " + contentRating + " ## " + runtime + " ## [" + genresToString() +"] ##");
    }

    public void parse(String line) {
        Integer length = line.length();
        String[] fields = new String[11];
        StringBuilder builder = new StringBuilder();
        for(int i = 0, k = 0, l = 0; i < length && k < 11; i++){
            if(line.charAt(i) != ','){
                if(line.charAt(i) == '"'){
                    i++;
                    while(line.charAt(i) != '"'){
                        builder.append(line.charAt(i++));
                    }
                }else{
                    builder.append(line.charAt(i));
                }
                
            }else if(line.charAt(i) == ',' && line.charAt(i + 1) == ','){
                fields[k] = new String(builder);
                builder = new StringBuilder();
                k++;
                l = 0;
                builder.append("NaN");
                fields[k] = new String(builder);

            }else if(line.charAt(i) == ',' && line.charAt(i + 1) != ','){
                fields[k] = new String(builder);
                builder = new StringBuilder();
                k++;
                l = 0;
            }
        }

        String parsedId = "";
        String parsedContentType = "";
        String parsedName = "";
        String parsedDirector = "";
        String[] parsedActors = new String[1];
        String parsedCountry = "";
        LocalDate parsedDate = LocalDate.now();
        Integer parsedYear = 0;
        String parsedRating = "";
        String parsedRuntime = "";
        String[] parsedGenres = new String[1];

        for(int i = 0; i < 11; i++){
            switch(i){
                case 0:
                    parsedId = new String(fields[i]);
                    setId(parsedId);
                    break;
                case 1:
                    parsedContentType = new String(fields[i]);
                    setContentType(parsedContentType);
                    break;
                case 2:
                    parsedName = new String(fields[i]);
                    setName(parsedName);
                    break;
                case 3:
                    parsedDirector = new String(fields[i]);
                    setDirectorName(parsedDirector);
                    break;
                case 4:
                    Integer actorCount = 1;
                    Integer actorLength = fields[i].length();

                    for(int j = 0; j < actorLength; j++){
                        if(fields[i].charAt(j) == ',')
                            actorCount++;
                    }

                    parsedActors = new String[actorCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < actorLength; j++){
                        if(fields[i].charAt(j) != ','){
                            builder.append(fields[i].charAt(j));
                        }else if(fields[i].charAt(j) == ','){
                            j++;
                            parsedActors[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == actorLength - 1){
                            j++;
                            parsedActors[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }

                    setActors(parsedActors);
                    break;
                case 5:
                    parsedCountry = new String(fields[i]);
                    setCountry(parsedCountry);
                    break;
                case 6:
                    if(!fields[i].equals("NaN")){
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        parsedDate = LocalDate.parse(fields[i],formatter);
                        setAddedDate(parsedDate);
                    }else{
                        fields[i] = "March 1, 1900";
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        parsedDate = LocalDate.parse(fields[i],formatter);
                        setAddedDate(parsedDate);
                    }
                    break;
                case 7:
                    parsedYear = Integer.parseInt(fields[i]);
                    setReleaseYear(parsedYear);
                    break;
                case 8:
                    parsedRating = new String(fields[i]);
                    setContentRating(parsedRating);
                    break;
                case 9:
                    parsedRuntime = new String(fields[i]);
                    setRuntime(parsedRuntime);
                    break;
                case 10:
                    Integer genreCount = 1;
                    Integer genreLength = fields[i].length();

                    for(int j = 0; j < genreLength; j++){
                        if(fields[i].charAt(j) == ',')
                            genreCount++;
                    }

                    parsedGenres = new String[genreCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < genreLength; j++){
                        if(fields[i].charAt(j) != ','){
                            builder.append(fields[i].charAt(j));
                        }else if(fields[i].charAt(j) == ','){
                            j++;
                            parsedGenres[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == genreLength - 1){
                            j++;
                            parsedGenres[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }

                    setGenres(parsedGenres);
                    break;
            }
        }
    }

    public MediaContent copy(){
        return new MediaContent(this.id, this.contentType, this.name, this.directorName, this.actors, this.country, 
                             this.addedDate, this.releaseYear, this.contentRating, this.runtime, this.genres);
    }
}

public class ContentSorter {
    public static void partialSelectionSort(MediaContent[] array, Integer size){
        File logFile = new File("./853431_selecaoParcial.txt");
        try{
            FileWriter writer = new FileWriter(logFile);

            long startTime = System.nanoTime();
            Integer moveCount = 0;
            Integer comparisonCount = 0;

            for(int i = 0; i < 10; i++){
                int minIndex = i;
                for(int j = i + 1; j < size; j++){

                    Boolean compareResult = array[minIndex].getName().compareToIgnoreCase(array[j].getName()) > 0;
                    comparisonCount++;

                    if(compareResult){
                        minIndex = j;
                    }
                }
                if(minIndex != i){
                    moveCount++;
                    MediaContent temp = array[minIndex];
                    array[minIndex] = array[i];
                    array[i] = temp;
                }
            }

            long endTime = System.nanoTime();
            long duration = endTime - startTime;

            writer.write("853431\t" + comparisonCount + "\t" + moveCount + "\t" + duration/1_000_000.0 );

            writer.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) throws FileNotFoundException {
        Scanner inputScanner = new Scanner(System.in);
        File dataFile = new File("/tmp/disneyplus.csv");
        Scanner fileScanner = new Scanner(dataFile,"UTF-8");
        fileScanner.nextLine();

        MediaContent[] contentList = new MediaContent[1368];
        for(int i = 0; i < 1368; i++){
            String line = fileScanner.nextLine();
            contentList[i] = new MediaContent();
            contentList[i].parse(line);
        }
        fileScanner.close();

        String inputId = inputScanner.nextLine();
        MediaContent[] selectedContent = new MediaContent[1368];
        int selectedCount = 0;
        while(!inputId.equals("FIM")){
            Integer id = Integer.parseInt(inputId.substring(1,inputId.length()));
            selectedContent[selectedCount++] = contentList[id - 1].copy();
            inputId = inputScanner.nextLine();
        }

        partialSelectionSort(selectedContent,selectedCount);
        for(int i = 0; i < 10; i++){
            selectedContent[i].display();
        }

        inputScanner.close();
    }
}