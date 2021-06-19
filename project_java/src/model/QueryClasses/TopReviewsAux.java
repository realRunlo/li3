package model.QueryClasses;

import java.util.HashSet;
import java.util.Set;

/**
 * Elementos da classe TopReviews
 */
public class TopReviewsAux {
    private int date;
    private int total;
    private float totalScore;
    private String value;
    private Set<String> unique = new HashSet<>();

    /**
     * Construtor de TopReviewsAux
     * @param value id do elemento a guardar
     * @param date data da review
     */
    public TopReviewsAux(String value, int date){
        this.date = date;
        this.value = value;
        this.total = 0;
        this.totalScore = 0;
    }

    /**
     * Adiciona uma review verificando se o user que a realizou
     * ja tinha feito review antes na data da classe
     * @param key user/business da review
     */
    public void addReview(String key,float score){
        unique.add(key);
        total++;
        totalScore+=score;
    }

    /**
     * Retorna o numero de users distintos que fizeram reviews
     * @return total de users distintos
     */
    public int getUnique(){return unique.size();}

    /**
     * Retorna o total de reviews feitas
     * @return reviews feitas
     */
    public int getTotal(){return total;}

    /**
     * Retorna o id
     * @return id
     */
    public String getValue(){return this.value;}

    /**
     * Devolve a data
     * @return data
     */
    public int getDate(){return date;}

    /**
     * Getter do totalScore
     * @return totalScore
     */
    public float getTotalScore(){return totalScore;}

    /**
     * Calcula e retorna a media de reviews guardadas
     * @return media
     */
    public float getAverage(){
        if(total == 0) return 0;
        return totalScore/total;
    }
}
