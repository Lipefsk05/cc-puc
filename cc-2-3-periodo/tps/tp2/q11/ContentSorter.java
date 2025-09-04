import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.time.format.DateTimeFormatter;
import java.time.LocalDate;
import java.io.IOException;

class MediaContent {
    private String contentId;
    private String contentType;
    private String contentTitle;
    private String contentDirector;
    private String[] contentCast;
    private String contentCountry;
    private LocalDate contentDateAdded;
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
        this.contentDateAdded = LocalDate.now();
        this.contentReleaseYear = 0;
        this.contentRating = "";
        this.contentDuration = "";
        this.contentCategories = new String[1];
    }

    public MediaContent(String id, String type, String title, String director, String[] cast, 
                      String country, LocalDate dateAdded, Integer releaseYear, 
                      String rating, String duration, String[] categories) {
        this.contentId = id;
        this.contentType = type;
        this.contentTitle = title;
        this.contentDirector = director;
        this.contentCast = cast;
        this.contentCountry = country;
        this.contentDateAdded = dateAdded;
        this.contentReleaseYear = releaseYear;
        this.contentRating = rating;
        this.contentDuration = duration;
        this.contentCategories = categories;
    }

    // Getters and setters with renamed methods
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

    public void setContentDateAdded(LocalDate dateAdded) {
        this.contentDateAdded = dateAdded;
    }

    public LocalDate getContentDateAdded() {
        return this.contentDateAdded;
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

    public void displayContent() {
        String dateString = "NaN";
        if(this.contentDateAdded != null){
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
            dateString = contentDateAdded.format(formatter);
        }
        System.out.println("=> " + contentId + " ## " + contentTitle + " ## " + contentType + " ## " + contentDirector 
            + " ## [" + castToString() +"] ## " + contentCountry + " ## " + dateString + " ## " + contentReleaseYear 
            + " ## " + contentRating + " ## " + contentDuration + " ## [" + categoriesToString() +"] ##");
    }

    public void parseContentData(String dataLine) {
        Integer length = dataLine.length();
        String[] dataFields = new String[11];
        StringBuilder builder = new StringBuilder();
        
        for(int i = 0, k = 0, l = 0; i < length && k < 11; i++){
            if(dataLine.charAt(i) != ','){
                if(dataLine.charAt(i) == '"'){
                    i++;
                    while(dataLine.charAt(i) != '"'){
                        builder.append(dataLine.charAt(i++));
                    }
                }else{
                    builder.append(dataLine.charAt(i));
                }
            }else if(dataLine.charAt(i) == ',' && dataLine.charAt(i + 1) == ','){
                dataFields[k] = new String(builder);
                builder = new StringBuilder();
                k++;
                l = 0;
                builder.append("NaN");
                dataFields[k] = new String(builder);
            }else if(dataLine.charAt(i) == ',' && dataLine.charAt(i + 1) != ','){
                dataFields[k] = new String(builder);
                builder = new StringBuilder();
                k++;
                l = 0;
            }
        }

        // Parse each field
        for(int i = 0; i < 11; i++){
            switch(i){
                case 0: setContentId(new String(dataFields[i])); break;
                case 1: setContentType(new String(dataFields[i])); break;
                case 2: setContentTitle(new String(dataFields[i])); break;
                case 3: setContentDirector(new String(dataFields[i])); break;
                case 4: {
                    Integer castCount = 1;
                    Integer castLength = dataFields[i].length();

                    for(int j = 0; j < castLength; j++){
                        if(dataFields[i].charAt(j) == ',')
                            castCount++;
                    }

                    String[] castArray = new String[castCount];
                    builder = new StringBuilder();
                    
                    for(int j = 0, k = 0; j < castLength; j++){
                        if(dataFields[i].charAt(j) != ','){
                            builder.append(dataFields[i].charAt(j));
                        }else if(dataFields[i].charAt(j) == ','){
                            j++;
                            castArray[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == castLength - 1){
                            j++;
                            castArray[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }
                    setContentCast(castArray);
                    break;
                }
                case 5: setContentCountry(new String(dataFields[i])); break;
                case 6: {
                    if(!dataFields[i].equals("NaN")){
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        setContentDateAdded(LocalDate.parse(dataFields[i],formatter));
                    }else{
                        dataFields[i] = "March 1, 1900";
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        setContentDateAdded(LocalDate.parse(dataFields[i],formatter));
                    }
                    break;
                }
                case 7: setContentReleaseYear(Integer.parseInt(dataFields[i])); break;
                case 8: setContentRating(new String(dataFields[i])); break;
                case 9: setContentDuration(new String(dataFields[i])); break;
                case 10: {
                    Integer categoryCount = 1;
                    Integer categoryLength = dataFields[i].length();

                    for(int j = 0; j < categoryLength; j++){
                        if(dataFields[i].charAt(j) == ',')
                            categoryCount++;
                    }

                    String[] categoryArray = new String[categoryCount];
                    builder = new StringBuilder();
                    
                    for(int j = 0, k = 0; j < categoryLength; j++){
                        if(dataFields[i].charAt(j) != ','){
                            builder.append(dataFields[i].charAt(j));
                        }else if(dataFields[i].charAt(j) == ','){
                            j++;
                            categoryArray[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                        if(j == categoryLength - 1){
                            j++;
                            categoryArray[k] = new String(builder);
                            k++;
                            builder = new StringBuilder();
                        }
                    }
                    setContentCategories(categoryArray);
                    break;
                }
            }
        }
    }

    public MediaContent duplicateContent(){
        return new MediaContent(this.contentId, this.contentType, this.contentTitle, 
            this.contentDirector, this.contentCast, this.contentCountry, this.contentDateAdded, 
            this.contentReleaseYear, this.contentRating, this.contentDuration, this.contentCategories);
    }
}

public class ContentSorter {
    public static Integer getMaxYear(MediaContent[] contentArray, int length){
        int max = contentArray[0].getContentReleaseYear();

        for(int i = 1; i < length; i++){
            if(contentArray[i].getContentReleaseYear() > max){
                max = contentArray[i].getContentReleaseYear();
            }
        }
        return max;
    }

    public static MediaContent[] sortByYear(MediaContent[] contentArray, Integer size){
        File logFile = new File("./853431_countingsort.txt");
        MediaContent[] sortedArray = new MediaContent[size];
        
        try{
            FileWriter logWriter = new FileWriter(logFile);

            long startTime = System.nanoTime();
            Integer moveCount = 0;
            Integer compareCount = 0;

            int[] count = new int[getMaxYear(contentArray, size) + 1];
            int countLength = count.length;

            // Initialize count array
            for(int i = 0; i < countLength; count[i++] = 0);

            // Count occurrences
            for(int i = 0; i < size; count[contentArray[i].getContentReleaseYear()]++, i++);

            // Cumulative count
            for(int i = 1; i < countLength; count[i] += count[i - 1], i++);

            // Build sorted array
            for(int i = size - 1; i >= 0; i--){
                sortedArray[count[contentArray[i].getContentReleaseYear()] - 1] = contentArray[i];
                count[contentArray[i].getContentReleaseYear()]--;
                moveCount++;
            }

            // Stable sort for titles with same year
            for(int i = 1; i < size; i++){
                MediaContent temp = sortedArray[i];
                int j = i - 1;

                while(j >= 0 && 
                    (temp.getContentReleaseYear().equals(sortedArray[j].getContentReleaseYear())) &&
                    (temp.getContentTitle().compareToIgnoreCase(sortedArray[j].getContentTitle()) < 0)){
                    compareCount += 2;
                    moveCount++;
                    sortedArray[j + 1] = sortedArray[j];
                    j--;
                }
                if(i != (j + 1)){
                    moveCount++;
                    sortedArray[j + 1] = temp;
                }
            }

            long endTime = System.nanoTime();
            long duration = endTime - startTime;

            logWriter.write("853431\t" + compareCount + "\t" + moveCount + "\t" + duration/1_000_000.0);
            logWriter.close();
        } catch(IOException e){
            e.printStackTrace();
        }
        return sortedArray;
    }

    public static void main(String[] args) throws FileNotFoundException {
        Scanner inputScanner = new Scanner(System.in);
        File dataFile = new File("/tmp/disneyplus.csv");
        Scanner fileScanner = new Scanner(dataFile,"UTF-8");
        fileScanner.nextLine();

        MediaContent[] contentDatabase = new MediaContent[1368];
        for(int i = 0; i < 1368; i++){
            String dataLine = fileScanner.nextLine();
            contentDatabase[i] = new MediaContent();
            contentDatabase[i].parseContentData(dataLine);
        }
        fileScanner.close();

        String inputId = inputScanner.nextLine();
        MediaContent[] contentArray = new MediaContent[1368];
        int arraySize = 0;
        
        while(!inputId.equals("FIM")){
            Integer id = Integer.parseInt(inputId.substring(1,inputId.length()));
            contentArray[arraySize++] = contentDatabase[id - 1].duplicateContent();
            inputId = inputScanner.nextLine();
        }

        MediaContent[] sortedContent = sortByYear(contentArray, arraySize);
        for(int i = 0; i < arraySize; i++){
            sortedContent[i].displayContent();
        }

        inputScanner.close();
    }
}