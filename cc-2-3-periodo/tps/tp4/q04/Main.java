import java.io.*;
import java.util.*;
import java.text.SimpleDateFormat;
import java.text.ParseException;

class No{
    No esq, dir;
    SHOW show;
    boolean cor;

    public No(SHOW show){
        this.show = show;
        esq = null; dir = null;
        cor = false;
    }

    public No(SHOW show, boolean cor){
        this.show = show;
        this.cor = cor;
        esq = null; dir = null;
    }

}


class Arvore{
    No raiz;
    int comparacoes = 0;
    public Arvore(){
        this.raiz = null;
    }

    public int getComparacoes() {
        return comparacoes;
    }

    public void inserir(SHOW s){
        if(raiz == null){
            raiz = new No(s);
        }
        else if(raiz.esq == null && raiz.dir == null){
            if(s.getTITLE().compareTo(raiz.show.getTITLE()) < 0){
                raiz.esq = new No(s);
            }
            else{
                raiz.dir = new No(s);
            }
        }
        else if(raiz.esq == null){
            if(s.getTITLE().compareTo(raiz.show.getTITLE()) < 0){
                raiz.esq = new No(s);
            }
            else if(s.getTITLE().compareTo(raiz.dir.show.getTITLE()) < 0){
                raiz.esq = new No(raiz.show);
                raiz.show = s;
            }
            else{
                raiz.esq = new No(raiz.show);
                raiz.show = raiz.dir.show;
                raiz.dir.show = s;
            }

            raiz.esq.cor = false; raiz.dir.cor = false;
        }
        else if(raiz.dir == null){
            if(s.getTITLE().compareTo(raiz.show.getTITLE()) > 0){
                raiz.dir = new No(s);
            }
            else if(s.getTITLE().compareTo(raiz.esq.show.getTITLE()) > 0){
                raiz.dir = new No(raiz.show);
                raiz.show = s;
            }
            else{
                raiz.dir = new No(raiz.show);
                raiz.show = raiz.esq.show;
                raiz.esq.show = s;
            }

            raiz.esq.cor = false; raiz.dir.cor = false;
        }
        else{
            inserir(s, null, null, null, raiz);
        }
        raiz.cor = false;
    }

    private void inserir(SHOW s, No bisavo, No avo, No pai, No i){
        if(i == null){
            if( s.getTITLE().compareTo(pai.show.getTITLE()) < 0){
                i = pai.esq = new No(s, true);
            }
            else{
                i = pai.dir = new No(s, true);
            }
            if(pai.cor == true){
                balancear(bisavo, avo, pai, i);
            }
        }
        else{
            if(i.esq != null && i.dir != null && i.esq.cor == true && i.dir.cor == true){
                i.cor = true; 
                i.esq.cor = false; 
                i.dir.cor = false;

                if(i == raiz){
                    i.cor = false;
                }
                else if(pai.cor == true){
                    balancear(bisavo, avo, pai, i);
                }
            }
            if(s.getTITLE().compareTo(i.show.getTITLE()) < 0){
                inserir(s, avo, pai, i, i.esq);
            }            
            else if(s.getTITLE().compareTo(i.show.getTITLE()) > 0){
                inserir(s, avo, pai, i, i.dir);
            }
        }
    }

    private void balancear(No bisavo, No avo, No pai, No i){
        comparacoes++; 
        if(pai.cor == true){
            comparacoes++;
            if(pai.show.getTITLE().compareTo(avo.show.getTITLE()) > 0){
                comparacoes++;
                if(i.show.getTITLE().compareTo(pai.show.getTITLE()) > 0){
                    avo = rotacaoEsq(avo);
                }
                else{
                    avo = rotacaoDirEsq(avo);
                }
            }
            else{
                comparacoes++;
                if(i.show.getTITLE().compareTo(pai.show.getTITLE()) < 0){
                    avo = rotacaoDir(avo);
                }
                else{
                    avo = rotacaoEsqDir(avo);
                }
            }
            if(bisavo == null){
                raiz = avo;
            } 
            else if(avo.show.getTITLE().compareTo(bisavo.show.getTITLE()) < 0){
                bisavo.esq = avo;
            } 
            else {
                bisavo.dir = avo;
            }
            avo.cor = false;
            avo.esq.cor = avo.dir.cor = true;
        }
    }

    private No rotacaoDir(No no){
        No noEsq = no.esq;
        No noEsqDir = noEsq.dir;
        
        noEsq.dir = no;
        no.esq = noEsqDir;
        return noEsq;
    }
    private No rotacaoEsq(No no){
        No noDir = no.dir;
        No noDirEsq = noDir.esq;

        noDir.esq = no;
        no.dir = noDirEsq;
        return noDir;
    }
    private No rotacaoDirEsq(No no){
        no.dir = rotacaoDir(no.dir);
        return rotacaoEsq(no);
    }
    private No rotacaoEsqDir(No no){
        no.esq = rotacaoEsq(no.esq);
        return rotacaoDir(no);
    }

    public boolean pesquisar(String nome){
        System.out.print("=>raiz  ");
        return pesquisar(nome, raiz);
    }
    private boolean pesquisar(String nome, No i){
        boolean resp;
        if(i == null){
            comparacoes++;
            resp = false;
        }
        else if(nome.compareTo(i.show.getTITLE()) == 0){
            comparacoes++;
            resp = true;
        }
        else if( nome.compareTo(i.show.getTITLE()) < 0){
            comparacoes++;
            System.out.print("esq ");
            resp = pesquisar(nome, i.esq);
        }
        else{
            comparacoes++;
            System.out.print("dir ");
            resp = pesquisar(nome, i.dir);
        }
        return resp;
    }
}

class SHOW {
    private String SHOW_ID;
    private String TYPE;
    private String TITLE;
    private String DIRECTOR[];
    private String[] CAST;
    private String COUNTRY;
    private Date DATE_ADDED;
    private int RELEASE_YEAR;
    private String RATING;
    private String DURATION;
    private String[] LISTED_IN;

    public SHOW() {
    }

    public SHOW(String SHOW_ID, String TYPE, String TITLE, String[] DIRECTOR, String[] CAST, String COUNTRY,
            Date DATE_ADDED, int RELEASE_YEAR, String RATING, String DURATION, String[] LISTED_IN) {

        setID(SHOW_ID);
        setTYPE(TYPE);
        setTITLE(TITLE);
        setDIRECTOR(DIRECTOR);
        setCAST(CAST);
        setCOUNTRY(COUNTRY);
        setDATE_ADDED(DATE_ADDED);
        setRELEASE_YEAR(RELEASE_YEAR);
        setRATING(RATING);
        setDURATION(DURATION);
        setLISTED_IN(LISTED_IN);
    }

    public SHOW clone() {
        SHOW clonado = new SHOW();

        clonado.setID(this.SHOW_ID);
        clonado.setTYPE(this.TYPE);
        clonado.setTITLE(this.TITLE);
        clonado.setDIRECTOR(this.DIRECTOR);
        clonado.setCAST(this.CAST);
        clonado.setCOUNTRY(this.COUNTRY);
        clonado.setRATING(this.RATING);
        clonado.setDATE_ADDED(this.DATE_ADDED);
        clonado.setRELEASE_YEAR(this.RELEASE_YEAR);
        clonado.setDURATION(this.DURATION);
        clonado.setLISTED_IN(this.LISTED_IN);

        return clonado;

    }

    // FUNÇÕES SET

    public void setID(String SHOW_ID) {
        this.SHOW_ID = SHOW_ID;
    }

    private void setTYPE(String TYPE) {
        if (TYPE == "") {
            TYPE = "NaN";
        }
        this.TYPE = TYPE;
    }

    private void setTITLE(String TITLE) {
        if (TITLE == "") {
            TITLE = "NaN";
        }
        this.TITLE = TITLE;
    }

    private void setDIRECTOR(String[] DIRECTOR) {
        if (DIRECTOR[0] == "") {
            DIRECTOR[0] = "NaN";
        }
        this.DIRECTOR = new String[DIRECTOR.length];
        for (int i = 0; i < DIRECTOR.length; i++) {
            this.DIRECTOR[i] = DIRECTOR[i].trim();
        }
    }

    private void setCAST(String[] CAST) {
        for (int i = 0; i < CAST.length; i++) {
            CAST[i] = CAST[i].trim();
        }
        ordenar(CAST);
        if (CAST[0] == "") {
            CAST[0] = "NaN";
        }
        this.CAST = new String[CAST.length];
        for (int i = 0; i < CAST.length; i++) {
            this.CAST[i] = CAST[i].trim();
        }
    }

    private void setCOUNTRY(String COUNTRY) {
        if (COUNTRY == "") {
            COUNTRY = "NaN";
        }
        this.COUNTRY = COUNTRY;
    }

    private void setDATE_ADDED(Date DATE_ADDED) {
        if (DATE_ADDED == null) {
            this.DATE_ADDED = null;
        } else {
            this.DATE_ADDED = DATE_ADDED;
        }

    }

    private void setRELEASE_YEAR(int RELEASE_YEAR) {
        this.RELEASE_YEAR = RELEASE_YEAR;
    }

    private void setRATING(String RATING) {
        if (RATING == "") {
            RATING = "NaN";
        }
        this.RATING = RATING;
    }

    private void setDURATION(String DURATION) {
        if (DURATION == "") {
            DURATION = "NaN";
        }
        this.DURATION = DURATION;
    }

    private void setLISTED_IN(String[] LISTED_IN) {
        for (int i = 0; i < LISTED_IN.length; i++) {
            LISTED_IN[i] = LISTED_IN[i].trim();
        }
        ordenar(LISTED_IN);
        if (LISTED_IN[0] == "") {
            LISTED_IN[0] = "NaN";
        }
        this.LISTED_IN = new String[LISTED_IN.length];
        for (int i = 0; i < LISTED_IN.length; i++) {
            this.LISTED_IN[i] = LISTED_IN[i].trim();
        }
    }

    // FUNÇÕES GET

    public String getID() {
        return SHOW_ID;
    }

    public String getTYPE() {
        return TYPE;
    }

    public String getTITLE() {
        return TITLE;
    }

    public void getDIRECTOR() {
        for (int i = 0; i < DIRECTOR.length - 1; i++) {
            System.out.print(DIRECTOR[i] + ", ");
        }
        System.out.print(DIRECTOR[DIRECTOR.length - 1] + " ## ");
    }

    public void getCAST() {
        System.out.print("[");
        for (int i = 0; i < CAST.length - 1; i++) {
            System.out.print(CAST[i] + ", ");
        }
        System.out.print(CAST[CAST.length - 1] + "] ## ");
    }

    public String getCOUNTRY() {
        return COUNTRY;
    }

    public Date getDATE_ADDED() {
        return DATE_ADDED;
    }

    public int getRELEASE_YEAR() {
        return RELEASE_YEAR;
    }

    public String getRATING() {
        return RATING;
    }

    public String getDURATION() {
        return DURATION;
    }

    public void getLISTED_IN() {
        System.out.print("[");
        for (int i = 0; i < LISTED_IN.length - 1; i++) {
            System.out.print(LISTED_IN[i] + ", ");
        }
        System.out.print(LISTED_IN[LISTED_IN.length - 1] + "] ##");
    }

    // OUTRAS FUNÇÕES

    public void Leitura(String entrada) {
        List<String> partes = new ArrayList<>();
        boolean dentroAspas = false;
        StringBuilder atual = new StringBuilder();

        for (int i = 0; i < entrada.length(); i++) {
            char c = entrada.charAt(i);

            if (c == '"') {
                dentroAspas = !dentroAspas; // alterna se está dentro de aspas
            } else if (c == ',' && !dentroAspas) {
                partes.add(atual.toString().trim());
                atual.setLength(0); // limpa o StringBuilder
            } else {
                atual.append(c); // adiciona o character no StringBuilder
            }
        }
        partes.add(atual.toString().trim());

        setID(partes.get(0));
        setTYPE(partes.get(1));
        setTITLE(partes.get(2));
        setDIRECTOR(partes.get(3).split(","));
        setCAST(partes.get(4).split(","));
        setCOUNTRY(partes.get(5));

        Date date_added = null;
        if (partes.get(6) != null && !partes.get(6).isEmpty()) {
            try {
                SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.US);
                date_added = sdf.parse(partes.get(6));
            } catch (ParseException e) {
                System.out.println("Erro ao converter a data do " + getID());
                date_added = null;
            }
        }
        setDATE_ADDED(date_added);

        setRELEASE_YEAR(Integer.parseInt(partes.get(7)));
        setRATING(partes.get(8));
        setDURATION(partes.get(9));
        setLISTED_IN(partes.get(10).split(","));

    }

    private void ordenar(String[] Lista) {
        for (int i = 0; i < Lista.length - 1; i++) {
            int menor = i;
            for (int j = i + 1; j < Lista.length; j++) {
                if (Lista[menor].compareTo(Lista[j]) > 0) {
                    menor = j;
                }
            }

            String temp = Lista[menor];
            Lista[menor] = Lista[i];
            Lista[i] = temp;
        }

    }

    public void imprimir() {
        System.out.print("=> " + getID() + " ## " + getTITLE() + " ## " + getTYPE() + " ## ");
        getDIRECTOR();
        getCAST();
        System.out.print(getCOUNTRY() + " ## ");

        SimpleDateFormat sdf = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH);
        if (getDATE_ADDED() != null) {
            System.out.print(sdf.format(getDATE_ADDED()) + " ## ");
        } else {
            System.out.print("NaN ## ");
        }

        System.out.print(getRELEASE_YEAR() + " ## " + getRATING() + " ## " + getDURATION() + " ## ");
        getLISTED_IN();
        System.out.println();
    }

}

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String entrada;
        Arvore arvore = new Arvore();

        long tempoInicial = System.currentTimeMillis();
 

        try {
            while (!(entrada = sc.nextLine()).equals("FIM")) {
                BufferedReader br = new BufferedReader(new FileReader("/tmp/disneyplus.csv"));
                String linha = br.readLine(); // pula o cabeçalho
                boolean encontrado = false;

                linha = br.readLine(); // lê a primeira linha de dados
                while (linha != null && !encontrado) {
                    if (linha.startsWith(entrada + ",")) {
                        SHOW tmp = new SHOW();
                        tmp.Leitura(linha);
                        arvore.inserir(tmp);
                        encontrado = true;
                    } else {
                        linha = br.readLine(); // só continua lendo se ainda não encontrou
                    }
                }

                if (!encontrado) {
                    System.out.println("Show ID " + entrada + " não encontrado.");
                }

                br.close();
            }
        } catch (IOException e) {
            System.out.println("Erro ao acessar o arquivo: " + e.getMessage());
        }

        
        String titulo = sc.nextLine();
        while(!titulo.equals("FIM"))
        {
            if(arvore.pesquisar(titulo) == true)
            {
                System.out.println("SIM");
            }
            else{
                System.out.println("NAO");
            }
            titulo = sc.nextLine();
        }

        long tempoFinal = System.currentTimeMillis();
        long tempoExecucao = tempoFinal - tempoInicial;

        //Criando arquivo.txt
        try {
            java.io.PrintWriter arquivo = new java.io.PrintWriter("matricula_alviNegra.txt", "UTF-8");
            arquivo.printf("858158\t%d\t%d \n", tempoExecucao, arvore.getComparacoes());
            arquivo.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

        sc.close();
    }
}
