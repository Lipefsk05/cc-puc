import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.annotation.Retention;
import java.util.*;
import java.util.random.RandomGenerator.StreamableGenerator;

class Show{
    private String SHOW_ID;
    private String TYPE;
    private String TITTLE;
    private String DIRECTOR;
    private String[] CAST;
    private String COUNTRY;
    private Date DATE_ADDED;
    private int RELEASE_YEAR;
    private String RATING;
    private String DURATION;
    private String[] LISTENED_IN;

    public Show(){
        SHOW_ID = "";
        TYPE = "";
        TITTLE = "";
        DIRECTOR = "";
        CAST = new String[0];
        COUNTRY = "";
        DATE_ADDED = new Date();
        RELEASE_YEAR = 0;
        RATING = "";
        DURATION = "";
        LISTENED_IN = new String[0];
    }


//  -----------------------------------------------    
    public String getShowId(){
        return SHOW_ID;
    }
    public void setShowId(String SHOW_ID){
        this.SHOW_ID = SHOW_ID;
    }
//  -----------------------------------------------    
    public String getType(){
        return TYPE;
    }
    public void setType(String TYPE){
        this.TYPE = TYPE;
    }
//  -----------------------------------------------    
    public String getTittle(){
        return TITTLE;
    }
    public void setTittle(String TITTLE){
        this.TITTLE = TITTLE;
    }
//  -----------------------------------------------    
    public String getDirector(){
        return DIRECTOR;
    }
    public void setDirector(String DIRECTOR){
        this.DIRECTOR = DIRECTOR;
    }
//  -----------------------------------------------    
    public String[] getCast(){
        return CAST;
    }
    public void setCast(String[] CAST){
        this.CAST = CAST;
    }
//  -----------------------------------------------    
    public String getCountry(){
        return COUNTRY;
    }
    public void setCountry(String COUNTRY){
        this.COUNTRY = COUNTRY;
    }
//  -----------------------------------------------    
    public Date getDate(){
        return DATE_ADDED;
    }
    public void setDate(Date DATE_ADDED){
        this.DATE_ADDED = DATE_ADDED;
    }
//  -----------------------------------------------    
    public int getReleaseYear(){
        return RELEASE_YEAR;
    }
    public void setReleaseYear(int RELEASE_YEAR){
        this.RELEASE_YEAR = RELEASE_YEAR;
    }
//  -----------------------------------------------    
    public String getRating(){
        return RATING;
    }
    public void setRating(String RATING){
        this.RATING = RATING;
    }
//  -----------------------------------------------    
    public String getDuration(){
        return DURATION;
    }
    public void setDuration(String DURATION){
        this.DURATION = DURATION;
    }
//  -----------------------------------------------    
    public String[] getListenedIn (){
        return LISTENED_IN;
    }
    public void setListenedIn (String[] LISTENED_IN){
        this.LISTENED_IN = LISTENED_IN;
    }
}

public class Main{

    public static Show setFilme(String[] filmeSplited){
        
        Show filme = new Show();

        filme.setShowId(filmeSplited[0]);
        filme.setType(filmeSplited[1]);
        filme.setTittle(filmeSplited[2]);
        filme.setDirector(filmeSplited[3]);
        // filme.setCast(filmeSplited[4]);
        filme.setCountry(filmeSplited[5]);
        // filme.setDate(filmeSplited[6]);
        // filme.setReleaseYear(filmeSplited[7]);
        filme.setRating(filmeSplited[8]);
        filme.setDuration(filmeSplited[9]);
        // filme.setListenedIn(filmeSplited[]);

        return filme;
    }
    public static void main(String[] args) {

        Show[] filmes = new Show[100000];

        try(BufferedReader br = new BufferedReader(new FileReader("disneyplus.csv"))){
            
            String filmeLinha = " ";
            while ((filmeLinha = br.readLine()) != null) {
                int i = 0;
                String[] filmeSplited = filmeLinha.split(",");
                filmes[i] = setFilme(filmeSplited);
                i++;
            }
        }
        catch (Exception e) {
            System.out.println(e);
        }

        System.out.println(filmes[0].getShowId() + " " + filmes[0].getDirector());
    }
}