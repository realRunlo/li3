package model;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Review implements IReview{

    private String review_id;
    private String user_id;
    private String business_id;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String txt;

    /**
     * Construtor de Review
     * @param review_id id da review
     * @param user_id id do user que fez a review
     * @param business_id id do negocio reviewed
     * @param stars avaliacao
     * @param useful impacto-util
     * @param funny impacto-comico
     * @param cool impacto-fixe
     * @param date data de criacao da review
     * @param txt texto da review
     */
    public Review(String review_id,String user_id,String business_id,
                  float stars,int useful,int funny,int cool,LocalDateTime date,String txt){

        this.review_id = review_id;
        this.user_id = user_id;
        this.business_id = business_id;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.txt = txt;
    }

    /**
     * Construtor de Review
     * @param line string a analisar de modo a carregar uma review
     */
    public Review(String line){
        String[] data = line.split(";",9);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        this.review_id = data[0];
        this.user_id = data[1];
        this.business_id = data[2];
        this.stars = Float.parseFloat(data[3]);
        this.useful = Integer.parseInt(data[4]);
        this.funny = Integer.parseInt(data[5]);
        this.cool = Integer.parseInt(data[6]);
        this.date = LocalDateTime.parse(data[7],formatter);
        this.txt = data[8];
    }

    /**
     * Construtor de Review
     * @param rev review a copiar
     */
    public Review(Review rev){
        this.review_id = rev.review_id;
        this.user_id = rev.user_id;
        this.business_id = rev.business_id;
        this.stars = rev.stars;
        this.useful = rev.useful;
        this.funny = rev.funny;
        this.cool = rev.cool;
        this.date = rev.date;
        this.txt = rev.txt;

    }

    /**
     * Getter do id da review
     * @return id da review
     */
    public String getReview_id() { return review_id; }

    /**
     * Getter do id do user que criou a review
     * @return id do user
     */
    public String getUser_id() { return user_id; }

    /**
     * Getter do id do negocio avaliado
     * @return id do negocio
     */
    public String getBusiness_id() { return business_id; }

    /**
     * Getter do score da review
     * @return score da review
     */
    public float getStars() { return stars; }

    /**
     * Getter do impatco-util
     * @return impacto-util
     */
    public int getUseful() { return useful; }

    /**
     * Getter do impacto-comico
     * @return impacto-comico
     */
    public int getFunny() { return funny; }

    /**
     * Getter do impacto-fixe
     * @return impacto-fixe
     */
    public int getCool() { return cool; }

    /**
     * Getter da data de criacao da review
     * @return data de criacao
     */
    public LocalDateTime getDate() { return date; }

    /**
     * Getter do texto da review
     * @return texto da review
     */
    public String getTxt() { return txt; }

    /**
     * Metodo utilizado para validar se uma string
     * representa uma review
     * @param line linha possivelmente representante de uma review
     * @return resultado da validacao
     */
    public static boolean validReview (String line){
        String[] data = line.split(";",9);

        return !data[0].equals("") && !data[1].equals("") && !data[2].equals("") &&
                data[3].matches("[-+]?[0-9]*\\.?[0-9]+") && data[4].matches("[-+]?[0-9]*")
                && data[5].matches("[-+]?[0-9]*") && data[6].matches("[-+]?[0-9]*")
                && !data[7].equals("");
    }

    /**
     * ToString de Review
     * @return Review em formato string
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Review {\n");
        sb.append("ID = '").append(review_id).append("'\n");
        sb.append("BusinessID = '").append(business_id).append("'\n");
        sb.append("UserID = '").append(user_id).append("'\n");
        sb.append("Stars : '").append(stars).append("'\n");
        sb.append("Useful: ").append(useful).append("'\n");
        sb.append("Funny: ").append(funny).append("'\n");
        sb.append("Cool: ").append(cool).append("'\n");
        sb.append("Date: ").append(date).append("'\n");;
        sb.append("Text: ").append(txt).append("'\n");
        sb.append("\n}");
        return sb.toString();
    }

    /**
     * Clone de Review
     * @return clone
     */
    public Review clone(){return new Review(this);}




}
