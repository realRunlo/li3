package model.QueryClasses;

import java.util.HashMap;

public class ReviewedPerMonth {
    private int totalReviews;
    private int uniqueReviews;
    private float average;
    private float totalScore;
    private HashMap<String,Integer> uniqueReviewsHash;

    /**
     * Construtor de ReviewedPerMonth
     */
    public ReviewedPerMonth(){
        totalReviews = 0;
        uniqueReviews = 0;
        average = 0;
        totalScore = 0;
        uniqueReviewsHash = new HashMap<>();
    }

    /**
     * Retorna o numero total de reviews registados
     * @return total de reviews
     */
    public int getTotalReviews(){return totalReviews;}

    /**
     * Retorna o numero total de reviews feitas por users distintos
     * @return total de reviews
     */
    public int getUniqueReviews() {
        return uniqueReviews;
    }

    /**
     * Retorna o score medio
     * @return score medio
     */
    public float getAverage() {
        return average;
    }

    /**
     * Adiciona o score de uma review, verificando se o user que a fez
     * ja tinha feito reviews antes, caso contrario e um user novo
     * Tambem atualiza a media
     * @param score score da review
     * @param user_id user que realizou a review
     */
    public void incTotalReviews(float score,String user_id){
        totalScore += score;
        totalReviews++;
        if(!uniqueReviewsHash.containsKey(user_id)) {
            uniqueReviews++;
            uniqueReviewsHash.put(user_id,0);
        }
        average = totalScore/totalReviews;
    }

    /**
     * ToString de ReviewedPerMonth
     * @return ReviewedPerMonth em formato string
     */
    public String toString(){
        return "Total reviews: " + totalReviews +"\nUnique reviews: " + uniqueReviews + "\nAverage: " + average +"\n";
    }


}
