// package ex18;

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
    private String title;
    private String director;
    private String[] castMembers;
    private String country;
    private LocalDate addedDate;
    private Integer releaseYear;
    private String contentRating;
    private String duration;
    private String[] genres;

    public MediaContent() {
        this.id = "";
        this.contentType = "";
        this.title = "";
        this.director = "";
        this.castMembers = new String[1];
        this.country = "";
        this.addedDate = LocalDate.now();
        this.releaseYear = 0;
        this.contentRating = "";
        this.duration = "";
        this.genres = new String[1];
    }

    public MediaContent(String id, String contentType, String title, String director, String[] castMembers, 
                       String country, LocalDate addedDate, Integer releaseYear, String contentRating, 
                       String duration, String[] genres) {
        this.id = id;
        this.contentType = contentType;
        this.title = title;
        this.director = director;
        this.castMembers = castMembers;
        this.country = country;
        this.addedDate = addedDate;
        this.releaseYear = releaseYear;
        this.contentRating = contentRating;
        this.duration = duration;
        this.genres = genres;
    }

    // Getters and setters with renamed methods
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

    public void setTitle(String title) {
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    public void setDirector(String director) {
        this.director = director;
    }

    public String getDirector() {
        return this.director;
    }

    public void setCastMembers(String[] castMembers) {
        int length = castMembers.length;
        for(int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - i - 1; j++){
                String current = castMembers[j];
                String next = castMembers[j + 1];

                if(current.compareTo(next) > 0){
                    String temp = castMembers[j];
                    castMembers[j] = castMembers[j + 1];
                    castMembers[j + 1] = temp;
                }
            }
        }
        this.castMembers = castMembers;
    }

    public String[] getCastMembers() {
        return this.castMembers;
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

    public void setDuration(String duration) {
        this.duration = duration;
    }

    public String getDuration() {
        return this.duration;
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

    public String castMembersToString(){
        Integer count = this.castMembers.length;
        StringBuilder builder = new StringBuilder();

        for(int i = 0; i < count; i++){
            builder.append(this.castMembers[i]);
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
        String dateStr = "NaN";
        if(this.addedDate != null){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
            dateStr = addedDate.format(formatter);
        }
        System.out.println("=> " + id + " ## " + title + " ## " + contentType + " ## " + director 
            + " ## [" + castMembersToString() +"] ## " + country + " ## " + dateStr + " ## " + releaseYear 
            + " ## " + contentRating + " ## " + duration + " ## [" + genresToString() +"] ##");
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
        String parsedTitle = "";
        String parsedDirector = "";
        String[] parsedCast = new String[1];
        String parsedCountry = "";
        LocalDate parsedDate = LocalDate.now();
        Integer parsedYear = 0;
        String parsedRating = "";
        String parsedDuration = "";
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
                    parsedTitle = new String(fields[i]);
                    setTitle(parsedTitle);
                    break;
                case 3:
                    parsedDirector = new String(fields[i]);
                    setDirector(parsedDirector);
                    break;
                case 4:
                    Integer castCount = 1;
                    Integer castLength = fields[i].length();

                    for(int j = 0; j < castLength; j++){
                        if(fields[i].charAt(j) == ',')
                            castCount++;
                    }

                    parsedCast = new String[castCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < castLength; j++){
                        if(fields[i].charAt(j) != ','){
                            builder.append(fields[i].charAt(j));
                        }else if(fields[i].charAt(j) == ','){
                            j++;
                            parsedCast[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == castLength - 1){
                            j++;
                            parsedCast[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }

                    setCastMembers(parsedCast);
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
                    parsedDuration = new String(fields[i]);
                    setDuration(parsedDuration);
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
        return new MediaContent(this.id, this.contentType, this.title, this.director, 
                              this.castMembers, this.country, this.addedDate, 
                              this.releaseYear, this.contentRating, this.duration, this.genres);
    }
}

public class MediaSorter {

    public static int compareDates(LocalDate date1, LocalDate date2){
        int result = 0;

        if(result == 0 && date1.getYear() != date2.getYear()){
            result = (date1.getYear() < date2.getYear()) ? -1 : 1;
        }

        if(result == 0 && date1.getMonthValue() != date2.getMonthValue()){
            result = (date1.getMonthValue() < date2.getMonthValue()) ? -1 : 1;
        }

        if(result == 0 && date1.getDayOfMonth() != date2.getDayOfMonth()){
            result = (date1.getDayOfMonth() < date2.getDayOfMonth()) ? -1 : 1;
        }

        return result;
    }

    public static int compareMediaContent(MediaContent a, MediaContent b, Integer[] moves, Integer[] comparisons){
        int result = 0;
        int dateComparison = compareDates(a.getAddedDate(), b.getAddedDate());
        if(dateComparison != 0){
            comparisons[0]++;
            result = dateComparison;
        }else{
            comparisons[0]+=2;
            result = a.getTitle().compareToIgnoreCase(b.getTitle());
        }
        return result;
    }

    public static void quickSort(MediaContent[] array, int left, int right, Integer[] moves, Integer[] comparisons){
        int i = left;
        int j = right;
        MediaContent pivot = array[(left + right)/2];
        while(i <= j){
            while(compareMediaContent(array[i], pivot, moves, comparisons) < 0){
                i++;
            }
            while(compareMediaContent(array[j], pivot, moves, comparisons) > 0){
                j--;
            }
            if(i <= j){
                moves[0]++;
                MediaContent temp = array[i];
                array[i] = array[j];
                array[j] = temp;
                i++;
                j--;
            }
        }
        if(left < j){
            quickSort(array, left, j, moves, comparisons);
        }
        if(i < 10 && i < right){
            quickSort(array, i, right, moves, comparisons);
        }
    }

    public static void sortWithQuickSort(MediaContent[] array, Integer size){
        File logFile = new File("./853431_quicksortParcial.txt");
        try{
            FileWriter writer = new FileWriter(logFile);

            long startTime = System.nanoTime();
            Integer[] moveCount = new Integer[1];
            moveCount[0] = 0;
            Integer[] comparisonCount = new Integer[1];
            comparisonCount[0] = 0;

            quickSort(array, 0, size - 1, moveCount, comparisonCount);

            long endTime = System.nanoTime();
            long duration = endTime - startTime;

            writer.write("853431\t" + comparisonCount[0] + "\t" + moveCount[0] + "\t" + duration/1_000_000.0 );

            writer.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner scanner = new Scanner(System.in);
        File dataFile = new File("/tmp/disneyplus.csv");
        Scanner fileScanner = new Scanner(dataFile,"UTF-8");
        fileScanner.nextLine();

        MediaContent[] mediaList = new MediaContent[1368];
        for(int i = 0; i < 1368; i++){
            String line = fileScanner.nextLine();
            mediaList[i] = new MediaContent();
            mediaList[i].parse(line);
        }
        fileScanner.close();

        String inputId = scanner.nextLine();
        MediaContent[] selectedMedia = new MediaContent[1368];
        int selectedCount = 0;
        while(!inputId.equals("FIM")){
            Integer id = Integer.parseInt(inputId.substring(1,inputId.length()));
            selectedMedia[selectedCount++] = mediaList[id - 1].copy();
            inputId = scanner.nextLine();
        }

        sortWithQuickSort(selectedMedia,selectedCount);
        for(int i = 0; i < 10; i++){
            selectedMedia[i].display();
        }

        scanner.close();
    }
}