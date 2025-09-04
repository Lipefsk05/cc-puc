// package ex09;

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
    private String[] contentCategories;

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
        this.contentCategories = new String[1];
    }

    public MediaContent(String id, String type, String title, String director, String[] cast, String country,
            LocalDate addedDate, Integer releaseYear, String rating, String duration, String[] categories) {
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
        this.contentCategories = categories;
    }

    public void setContentId(String id) {
        this.contentId = id;
    }

    public String getContentId() {
        return contentId;
    }

    public void setContentType(String type) {
        this.contentType = type;
    }

    public String getContentType() {
        return contentType;
    }

    public void setContentTitle(String title) {
        this.contentTitle = title;
    }

    public String getContentTitle() {
        return contentTitle;
    }

    public void setContentDirector(String director) {
        this.contentDirector = director;
    }

    public String getContentDirector() {
        return this.contentDirector;
    }

    public void setContentCast(String[] cast) {
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

    public String[] getContentCast() {
        return this.contentCast;
    }

    public void setContentCountry(String country) {
        this.contentCountry = country;
    }

    public String getContentCountry() {
        return this.contentCountry;
    }

    public void setContentAddedDate(LocalDate addedDate) {
        this.contentAddedDate = addedDate;
    }

    public LocalDate getContentAddedDate() {
        return this.contentAddedDate;
    }

    public void setContentReleaseYear(Integer releaseYear) {
        this.contentReleaseYear = releaseYear;
    }

    public Integer getContentReleaseYear() {
        return this.contentReleaseYear;
    }

    public void setContentRating(String rating) {
        this.contentRating = rating;
    }

    public String getContentRating() {
        return this.contentRating;
    }

    public void setContentDuration(String duration) {
        this.contentDuration = duration;
    }

    public String getContentDuration() {
        return this.contentDuration;
    }

    public void setContentCategories(String[] categories) {
        int length = categories.length;
        for(int i = 0; i < length - 1; i++){
            for(int j = 0; j < length - i - 1; j++){
                String current = categories[j];
                String next = categories[j + 1];

                if(current.compareTo(next) > 0){
                    String temp = categories[j];
                    categories[j] = categories[j + 1];
                    categories[j + 1] = temp;
                }
            }
        }
        this.contentCategories = categories;
    }

    public String[] getContentCategories() {
        return this.contentCategories;
    }

    public String castToString(){
        Integer count = this.contentCast.length;

        StringBuilder builder = new StringBuilder();

        for(int i = 0; i < count; i++){
            builder.append(this.contentCast[i]);
            if(i != count - 1){
                builder.append(", ");
            }
        }

        return new String(builder);
    }
    
    public String categoriesToString(){
        Integer count = this.contentCategories.length;
        
        StringBuilder builder = new StringBuilder();

        for(int i = 0; i < count; i++){
            builder.append(this.contentCategories[i]);
            if(i != count - 1){
                builder.append(", ");
            }
        }

        return new String(builder);
    }

    public void display() {
        String dateString = "NaN";
        if(this.contentAddedDate != null){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
            dateString = contentAddedDate.format(formatter);
        }
        System.out.println("=> " + contentId + " ## " + contentTitle + " ## " + contentType + " ## " + contentDirector 
            + " ## [" + castToString() +"] ## " + contentCountry + " ## " + dateString + " ## " + contentReleaseYear 
            + " ## " + contentRating + " ## " + contentDuration + " ## [" + categoriesToString() +"] ##");
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
        String[] categories = new String[1];

        for(int i = 0; i < 11; i++){
            switch(i){
                case 0:
                    id = new String(fields[i]);
                    setContentId(id);
                    break;
                case 1:
                    type = new String(fields[i]);
                    setContentType(type);
                    break;
                case 2:
                    title = new String(fields[i]);
                    setContentTitle(title);
                    break;
                case 3:
                    director = new String(fields[i]);
                    setContentDirector(director);
                    break;
                case 4:
                    Integer castCount = 1;
                    Integer castLength = fields[i].length();

                    for(int j = 0; j < castLength; j++){
                        if(fields[i].charAt(j) == ',')
                            castCount++;
                    }

                    cast = new String[castCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < castLength; j++){
                        if(fields[i].charAt(j) != ','){
                            builder.append(fields[i].charAt(j));
                        }else if(fields[i].charAt(j) == ','){
                            j++;
                            cast[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == castLength - 1){
                            j++;
                            cast[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }

                    setContentCast(cast);
                    break;
                case 5:
                    country = new String(fields[i]);
                    setContentCountry(country);
                    break;
                case 6:
                    if(!fields[i].equals("NaN")){
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        addedDate = LocalDate.parse(fields[i],formatter);
                        setContentAddedDate(addedDate);
                    }else{
                        fields[i] = "March 1, 1900";
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        addedDate = LocalDate.parse(fields[i],formatter);
                        setContentAddedDate(addedDate);
                    }
                    break;
                case 7:
                    releaseYear = Integer.parseInt(fields[i]);
                    setContentReleaseYear(releaseYear);
                    break;
                case 8:
                    rating = new String(fields[i]);
                    setContentRating(rating);
                    break;
                case 9:
                    duration = new String(fields[i]);
                    setContentDuration(duration);
                    break;
                case 10:
                    Integer categoryCount = 1;
                    Integer categoryLength = fields[i].length();

                    for(int j = 0; j < categoryLength; j++){
                        if(fields[i].charAt(j) == ',')
                            categoryCount++;
                    }

                    categories = new String[categoryCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < categoryLength; j++){
                        if(fields[i].charAt(j) != ','){
                            builder.append(fields[i].charAt(j));
                        }else if(fields[i].charAt(j) == ','){
                            j++;
                            categories[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == categoryLength - 1){
                            j++;
                            categories[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }

                    setContentCategories(categories);
                    break;
            }
        }
    }

    public MediaContent copy(){
        MediaContent copy = new MediaContent(this.contentId, this.contentType, this.contentTitle, 
            this.contentDirector, this.contentCast, this.contentCountry, this.contentAddedDate, 
            this.contentReleaseYear, this.contentRating, this.contentDuration, this.contentCategories);
        return copy;
    }
}

public class ContentManager {
    public static Integer findMaxYear(MediaContent[] array, int length){
        int max = array[0].getContentReleaseYear();

        for(int i = 1; i < length; i++){
            if(array[i].getContentReleaseYear() > max){
                max = array[i].getContentReleaseYear();
            }
        }
        return max;
    }

    public static int compareContent(MediaContent a, MediaContent b, Integer[] comparisons){
        int result = 0;

        if(a.getContentDirector().compareToIgnoreCase(b.getContentDirector()) != 0){
            comparisons[0]++;
            result = a.getContentDirector().compareToIgnoreCase(b.getContentDirector());
        }else{
            comparisons[0] += 2;
            result = a.getContentTitle().compareToIgnoreCase(b.getContentTitle());
        }

        return result;
    }

    public static void buildHeap(MediaContent[] array, Integer length, Integer i, Integer[] moves, Integer[] comparisons){
        int largest = i;
        int left = (2 * i) + 1;
        int right = (2 * i) + 2;

        if(left < length && compareContent(array[left], array[largest], comparisons) > 0){
            largest = left;
        }
        if(right < length && compareContent(array[right], array[largest], comparisons) > 0){
            largest = right;
        }

        if(largest != i){
            moves[0]++;
            MediaContent temp = array[i];
            array[i] = array[largest];
            array[largest] = temp;
            buildHeap(array, length, largest, moves, comparisons);
        }
    }
    
    public static void heapSort(MediaContent[] array, Integer length, Integer[] moves, Integer[] comparisons){
        for(int i = (length / 2) - 1; i >= 0; i--){
            buildHeap(array, length, i, moves, comparisons);
        }

        for(int i = length - 1; i > 0; i--){
            moves[0]++;
            MediaContent temp = array[0];
            array[0] = array[i];
            array[i] = temp;
            buildHeap(array, i, 0, moves, comparisons);
        }
    }
    
    public static void sortWithHeapSort(MediaContent[] array, Integer size){
        File logFile = new File("./853431_heapsort.txt");
        try{
            FileWriter writer = new FileWriter(logFile);

            long startTime = System.nanoTime();
            Integer[] moves = {0};
            Integer[] comparisons = {0};

            heapSort(array, size, moves, comparisons);

            long endTime = System.nanoTime();
            long duration = endTime - startTime;

            writer.write("853431\t" + comparisons[0] + "\t" + moves[0] + "\t" + duration/1_000_000.0 );

            writer.close();
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public static void main(String[] args) throws FileNotFoundException{
        Scanner scanner = new Scanner(System.in);
        File inputFile = new File("/tmp/disneyplus.csv");
        Scanner fileScanner = new Scanner(inputFile,"UTF-8");
        fileScanner.nextLine();

        MediaContent[] contentList = new MediaContent[1368];
        for(int i = 0; i < 1368; i++){
            String line = fileScanner.nextLine();
            contentList[i] = new MediaContent();
            contentList[i].parse(line);
        }
        fileScanner.close();

        String inputId = scanner.nextLine();
        MediaContent[] selectedContent = new MediaContent[1368];
        int selectedCount = 0;
        while(!inputId.equals("FIM")){
            Integer id = Integer.parseInt(inputId.substring(1,inputId.length()));
            selectedContent[selectedCount++] = contentList[id - 1].copy();
            inputId = scanner.nextLine();
        }

        sortWithHeapSort(selectedContent, selectedCount);

        for(int i = 0; i < selectedCount; i++){
            selectedContent[i].display();
        }

        scanner.close();
    }
}