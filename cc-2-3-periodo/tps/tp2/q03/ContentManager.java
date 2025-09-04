
import java.util.Scanner;
import java.io.File;
import java.io.FileWriter;
import java.io.FileNotFoundException;
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
        this.contentCategories = categories;
    }

    public String[] getContentCategories() {
        return this.contentCategories;
    }

    public String castMembersToString(){
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
            + " ## [" + castMembersToString() +"] ## " + contentCountry + " ## " + dateString + " ## " + contentReleaseYear 
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

        String id = "";
        String type = "";
        String title = "";
        String director = "";
        String[] cast = new String[1];
        String country = "";
        LocalDate dateAdded = LocalDate.now();
        Integer releaseYear = 0;
        String rating = "";
        String duration = "";
        String[] categories = new String[1];

        for(int i = 0; i < 11; i++){
            switch(i){
                case 0:
                    id = new String(dataFields[i]);
                    setContentId(id);
                    break;
                case 1:
                    type = new String(dataFields[i]);
                    setContentType(type);
                    break;
                case 2:
                    title = new String(dataFields[i]);
                    setContentTitle(title);
                    break;
                case 3:
                    director = new String(dataFields[i]);
                    setContentDirector(director);
                    break;
                case 4:
                    Integer castCount = 1;
                    Integer castLength = dataFields[i].length();

                    for(int j = 0; j < castLength; j++){
                        if(dataFields[i].charAt(j) == ',')
                            castCount++;
                    }

                    cast = new String[castCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < castLength; j++){
                        if(dataFields[i].charAt(j) != ','){
                            builder.append(dataFields[i].charAt(j));
                        }else if(dataFields[i].charAt(j) == ','){
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
                    country = new String(dataFields[i]);
                    setContentCountry(country);
                    break;
                case 6:
                    if(!dataFields[i].equals("NaN")){
                        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("MMMM d, yyyy");
                        dateAdded = LocalDate.parse(dataFields[i],formatter);
                        setContentDateAdded(dateAdded);
                    }else{
                        setContentDateAdded(null);
                    }
                    break;
                case 7:
                    releaseYear = Integer.parseInt(dataFields[i]);
                    setContentReleaseYear(releaseYear);
                    break;
                case 8:
                    rating = new String(dataFields[i]);
                    setContentRating(rating);
                    break;
                case 9:
                    duration = new String(dataFields[i]);
                    setContentDuration(duration);
                    break;
                case 10:
                    Integer categoryCount = 1;
                    Integer categoryLength = dataFields[i].length();

                    for(int j = 0; j < categoryLength; j++){
                        if(dataFields[i].charAt(j) == ',')
                            categoryCount++;
                    }

                    categories = new String[categoryCount];
                    
                    builder = new StringBuilder();
                    for(int j = 0, k = 0; j < categoryLength; j++){
                        if(dataFields[i].charAt(j) != ','){
                            builder.append(dataFields[i].charAt(j));
                        }else if(dataFields[i].charAt(j) == ','){
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

    public MediaContent duplicateContent(){
        MediaContent duplicate = new MediaContent(this.contentId, this.contentType, this.contentTitle, 
            this.contentDirector, this.contentCast, this.contentCountry, this.contentDateAdded, 
            this.contentReleaseYear, this.contentRating, this.contentDuration, this.contentCategories);
        return duplicate;
    }
}

public class ContentManager {
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

        MediaContent[] searchResults = new MediaContent[1368];

        String inputId = inputScanner.nextLine();
        Integer resultCount = 0;
        while(!inputId.equals("FIM")){
            Integer contentId = Integer.parseInt(inputId.substring(1,inputId.length()));
            searchResults[resultCount++] = contentDatabase[contentId - 1].duplicateContent();
            inputId = inputScanner.nextLine();
        }

        File outputFile = new File("./853431_sequencial.txt");
        Integer comparisonCount = 0;
        long startTime = System.nanoTime();

        String searchQuery = inputScanner.nextLine();
        while(!searchQuery.equals("FIM")){
            Boolean found = false;
            for(int i = 0; i < resultCount; i++){
                comparisonCount++;
                if(searchResults[i].getContentTitle().equals(searchQuery)){
                    found = true;
                }
            }
            if(found)
                System.out.println("SIM");
            else
                System.out.println("NAO");
            searchQuery = inputScanner.nextLine();
        }

        long endTime = System.nanoTime();

        long duration = endTime - startTime;
        try{
            FileWriter writer = new FileWriter(outputFile);
            writer.write("853431\t" + (duration / 1_000_000.0) + "ms\t" + comparisonCount);
            writer.close();
        }catch (IOException e){
            e.printStackTrace();
        }
        inputScanner.close();
    }
}