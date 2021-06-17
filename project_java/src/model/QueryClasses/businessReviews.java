package model.QueryClasses;

import java.io.Serializable;

public class businessReviews implements Serializable {
    private int totalReviews;
    private int totalScore;

    /**
     * Construtor de businessReviews
     */
    public businessReviews(){
        totalReviews = 0;
        totalScore = 0;
    }

    /**
     * Construtor de businessReviews
     */
    public businessReviews(int totalReviews,int totalScore){
        this.totalReviews = totalReviews;
        this.totalScore = totalScore;
    }

    /**
     * Incrementar o valor total das estrelas de um negocio
     * assim como o numero de reviews feitas nele
     * @param score nova review a registar
     */
    public void addReview(double score){
        totalReviews++;
        totalScore += score;
    }

    /**
     * Calcula o score medio do business
     * @return score medio
     */
    public float calcAverage(){
        if(totalReviews > 0)
        return (float) (totalScore*1.0/totalReviews);
        else return 0;
    }

    /**
     * Clone de businessReviews
     * @return clone
     */
    public businessReviews clone(){
        return new businessReviews(totalReviews,totalScore);
    }

}
