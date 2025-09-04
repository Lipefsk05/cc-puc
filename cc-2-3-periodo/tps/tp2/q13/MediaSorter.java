// package ex13;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.time.format.DateTimeFormatter;
import java.time.LocalDate;
import java.io.IOException;
import java.io.RandomAccessFile;

class MediaContent {
    private String contentId;
    private String contentType;
    private String contentTitle;
    private String contentDirector;
    private String[] contentCast;
    private String contentCountry;
    private LocalDate contentAddedDate;
    private Integer contentReleaseYear;
    private String contentRating;
    private String contentDuration;
    private String[] contentGenres;

    public MediaContent() {
        this.contentId = "";
        this.contentType = "";
        this.contentTitle = "";
        this.contentDirector = "";
        this.contentCast = new String[1];
        this.contentCountry = "";
        this.contentAddedDate = LocalDate.now();
        this.contentReleaseYear = 0;
        this.contentRating = "";
        this.contentDuration = "";
        this.contentGenres = new String[1];
    }

    public MediaContent(String id, String type, String title, String director, String[] cast, String country,
            LocalDate addedDate, Integer releaseYear, String rating, String duration, String[] genres) {
        this.contentId = id;
        this.contentType = type;
        this.contentTitle = title;
        this.contentDirector = director;
        this.contentCast = cast;
        this.contentCountry = country;
        this.contentAddedDate = addedDate;
        this.contentReleaseYear = releaseYear;
        this.contentRating = rating;
        this.contentDuration = duration;
        this.contentGenres = genres;
    }

    public void setId(String id) {
        this.contentId = id;
    }

    public String getId() {
        return contentId;
    }

    public void setType(String type) {
        this.contentType = type;
    }

    public String getType() {
        return contentType;
    }

    public void setTitle(String title) {
        this.contentTitle = title;
    }

    public String getTitle() {
        return contentTitle;
    }

    public void setDirector(String director) {
        this.contentDirector = director;
    }

    public String getDirector() {
        return this.contentDirector;
    }

    public void setCast(String[] cast) {
        int length = cast.length;
        for(int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - i - 1; j++){
                String current = cast[j];
                String next = cast[j + 1];

                if(current.compareTo(next) > 0){
                    String temp = cast[j];
                    cast[j] = cast[j + 1];
                    cast[j + 1] = temp;
                }
            }
        }
        this.contentCast = cast;
    }

    public String[] getCast() {
        return this.contentCast;
    }

    public void setCountry(String country) {
        this.contentCountry = country;
    }

    public String getCountry() {
        return this.contentCountry;
    }

    public void setAddedDate(LocalDate addedDate) {
        this.contentAddedDate = addedDate;
    }

    public LocalDate getAddedDate() {
        return this.contentAddedDate;
    }

    public void setReleaseYear(Integer releaseYear) {
        this.contentReleaseYear = releaseYear;
    }

    public Integer getReleaseYear() {
        return this.contentReleaseYear;
    }

    public void setRating(String rating) {
        this.contentRating = rating;
    }

    public String getRating() {
        return this.contentRating;
    }

    public void setDuration(String duration) {
        this.contentDuration = duration;
    }

    public String getDuration() {
        return this.contentDuration;
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
        this.contentGenres = genres;
    }

    public String[] getGenres() {
        return this.contentGenres;
    }

    public String castToString(){
        Integer count = this.contentCast.length;

        StringBuilder sb = new StringBuilder();

        for(int i = 0; i < count; i++){
            sb.append(this.contentCast[i]);
            if(i != count - 1){
                sb.append(", ");
            }
        }

        return new String(sb);
    }
    
    public String genresToString(){
        Integer count = this.contentGenres.length;
        
        StringBuilder sb = new StringBuilder();

        for(int i = 0; i < count; i++){
            sb.append(this.contentGenres[i]);
            if(i != count - 1){
                sb.append(", ");
            }
        }

        return new String(sb);
    }

    public void display() {
        String dateStr = "NaN";
        if(this.contentAddedDate != null){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
            dateStr = contentAddedDate.format(formatter);
        }
        System.out.println("=> " + contentId + " ## " + contentTitle + " ## " + contentType + " ## " + contentDirector 
            + " ## [" + castToString() +"] ## " + contentCountry + " ## " + dateStr + " ## " + contentReleaseYear 
            + " ## " + contentRating + " ## " + contentDuration + " ## [" + genresToString() +"] ##");
    }

    public void parse(String line) {
        Integer length = line.length();
        String[] attributes = new String[11];
        StringBuilder sb = new StringBuilder();
        
        for(int i = 0, attrIndex = 0, charIndex = 0; i < length && attrIndex < 11; i++){
            if(line.charAt(i) != ','){
                if(line.charAt(i) == '"'){
                    i++;
                    while(line.charAt(i) != '"'){
                        sb.append(line.charAt(i++));
                    }
                }else{
                    sb.append(line.charAt(i));
                }
                
            }else if(line.charAt(i) == ',' && line.charAt(i + 1) == ','){
                attributes[attrIndex] = new String(sb);
                sb = new StringBuilder();
                attrIndex++;
                charIndex = 0;
                sb.append("NaN");
                attributes[attrIndex] = new String(sb);

            }else if(line.charAt(i) == ',' && line.charAt(i + 1) != ','){
                attributes[attrIndex] = new String(sb);
                sb = new StringBuilder();
                attrIndex++;
                charIndex = 0;
            }
        }

        String id = "";
        String type = "";
        String title = "";
        String director = "";
        String[] cast = new String[1];
        String country = "";
        LocalDate addedDate = LocalDate.now();
        Integer releaseYear = 0;
        String rating = "";
        String duration = "";
        String[] genres = new String[1];

        for(int i = 0; i < 11; i++){
            switch(i){
                case 0:
                    id = new String(attributes[i]);
                    setId(id);
                    break;
                case 1:
                    type = new String(attributes[i]);
                    setType(type);
                    break;
                case 2:
                    title = new String(attributes[i]);
                    setTitle(title);
                    break;
                case 3:
                    director = new String(attributes[i]);
                    setDirector(director);
                    break;
                case 4:
                    Integer castCount = 1;
                    Integer castLength = attributes[i].length();

                    for(int j = 0; j < castLength; j++){
                        if(attributes[i].charAt(j) == ',')
                            castCount++;
                    }

                    cast = new String[castCount];
                    
                    sb = new StringBuilder();
                    for(int j = 0, k = 0; j < castLength; j++){
                        if(attributes[i].charAt(j) != ','){
                            sb.append(attributes[i].charAt(j));
                        }else if(attributes[i].charAt(j) == ','){
                            j++;
                            cast[k] = new String(sb);
                            k++;
                            sb = new StringBuilder();
                        }
                        if(j == castLength - 1){
                            j++;
                            cast[k] = new String(sb);
                            k++;
                            sb = new StringBuilder();
                        }
                    }

                    setCast(cast);
                    break;
                case 5:
                    country = new String(attributes[i]);
                    setCountry(country);
                    break;
                case 6:
                    if(!attributes[i].equals("NaN")){
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        addedDate = LocalDate.parse(attributes[i],formatter);
                        setAddedDate(addedDate);
                    }else{
                        attributes[i] = "March 1, 1900";
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        addedDate = LocalDate.parse(attributes[i],formatter);
                        setAddedDate(addedDate);
                    }
                    break;
                case 7:
                    releaseYear = Integer.parseInt(attributes[i]);
                    setReleaseYear(releaseYear);
                    break;
                case 8:
                    rating = new String(attributes[i]);
                    setRating(rating);
                    break;
                case 9:
                    duration = new String(attributes[i]);
                    setDuration(duration);
                    break;
                case 10:
                    Integer genresCount = 1;
                    Integer genresLength = attributes[i].length();

                    for(int j = 0; j < genresLength; j++){
                        if(attributes[i].charAt(j) == ',')
                            genresCount++;
                    }

                    genres = new String[genresCount];
                    
                    sb = new StringBuilder();
                    for(int j = 0, k = 0; j < genresLength; j++){
                        if(attributes[i].charAt(j) != ','){
                            sb.append(attributes[i].charAt(j));
                        }else if(attributes[i].charAt(j) == ','){
                            j++;
                            genres[k] = new String(sb);
                            k++;
                            sb = new StringBuilder();
                        }
                        if(j == genresLength - 1){
                            j++;
                            genres[k] = new String(sb);
                            k++;
                            sb = new StringBuilder();
                        }
                    }

                    setGenres(genres);
                    break;
            }
        }
    }

    public MediaContent copy(){
        return new MediaContent(this.contentId, this.contentType, this.contentTitle, this.contentDirector, 
                              this.contentCast, this.contentCountry, this.contentAddedDate, 
                              this.contentReleaseYear, this.contentRating, this.contentDuration, 
                              this.contentGenres);
    }
}

public class MediaSorter {

    public static int compareContent(MediaContent a, MediaContent b, Integer[] moves, Integer[] comparisons){
        int result = 0;
        int durationCompare = a.getDuration().compareTo(b.getDuration());
        if(durationCompare != 0){
            comparisons[0]++;
            result = durationCompare;
        }else{
            comparisons[0]+=2;
            result = a.getTitle().compareToIgnoreCase(b.getTitle());
        }
        return result;
    }
    
    public static void merge(MediaContent[] array, int left, int mid, int right, Integer[] moves, Integer[] comparisons){
        int leftSize = (mid + 1) - left;
        int rightSize = right - mid;

        MediaContent[] leftArray = new MediaContent[leftSize + 1]; 
        MediaContent[] rightArray = new MediaContent[rightSize + 1]; 

        leftArray[leftSize] = rightArray[rightSize] = new MediaContent("ZZZZ","ZZZZ","ZZZZ","ZZZZ",
            new String[] {"ZZZZ"},"ZZZZ",LocalDate.of(9999,12,31),9999,"ZZZZ","ZZZZ", new String[] {"ZZZZ"});

        int leftIndex = 0, rightIndex = 0;

        for(leftIndex = 0; leftIndex < leftSize; leftIndex++){
            leftArray[leftIndex] = array[left + leftIndex];
        }
        for(rightIndex = 0; rightIndex < rightSize; rightIndex++){
            rightArray[rightIndex] = array[(mid + 1) + rightIndex];
        }
        leftIndex = 0;
        rightIndex = 0;
        for(int i = left; i <= right; i++){
            moves[0]++;
            array[i] = (compareContent(leftArray[leftIndex], rightArray[rightIndex], moves, comparisons) <= 0) 
                ? leftArray[leftIndex++] : rightArray[rightIndex++];
        }
    }
    
    public static void mergeSort(MediaContent[] array, int left, int right, Integer[] moves, Integer[] comparisons){
        if(left < right){
            int mid = (left + right) / 2;
            mergeSort(array, left, mid, moves, comparisons);
            mergeSort(array, mid + 1, right, moves, comparisons);
            merge(array, left, mid, right, moves, comparisons);
        }
    }
    
    public static void sortContent(MediaContent[] array, Integer size){
        File logFile = new File("./853431_mergesort.txt");
        try{
            FileWriter logWriter = new FileWriter(logFile);

            long startTime = System.nanoTime();
            Integer[] moves = new Integer[1];
            moves[0] = 0;
            Integer[] comparisons = new Integer[1];
            comparisons[0] = 0;

            mergeSort(array, 0, size - 1, moves, comparisons);

            long endTime = System.nanoTime();
            long duration = endTime - startTime;

            logWriter.write("853431\t" + comparisons[0] + "\t" + moves[0] + "\t" + duration/1_000_000.0 );

            logWriter.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) throws FileNotFoundException{
        Scanner scanner = new Scanner(System.in);
        File dataFile = new File("/tmp/disneyplus.csv");
        Scanner fileScanner = new Scanner(dataFile,"UTF-8");
        fileScanner.nextLine();

        MediaContent[] mediaContents = new MediaContent[1368];
        for(int i = 0; i < 1368; i++){
            String line = fileScanner.nextLine();
            mediaContents[i] = new MediaContent();
            mediaContents[i].parse(line);
        }
        fileScanner.close();

        String inputId = scanner.nextLine();
        MediaContent[] selectedContents = new MediaContent[1368];
        int selectedCount = 0;
        
        while(!inputId.equals("FIM")){
            Integer id = Integer.parseInt(inputId.substring(1,inputId.length()));
            selectedContents[selectedCount++] = mediaContents[id - 1].copy();
            inputId = scanner.nextLine();
        }

        sortContent(selectedContents,selectedCount);
        for(int i = 0; i < selectedCount; i++){
            selectedContents[i].display();
        }

        scanner.close();
    }
}