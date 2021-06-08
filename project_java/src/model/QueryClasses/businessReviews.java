package model.QueryClasses;

public class businessReviews {
    private int totalReviews;
    private int totalScore;

    public businessReviews(){
        totalReviews = 0;
        totalScore = 0;
    }

    public void addReview(double score){
        totalReviews++;
        totalScore += score;
    }

    public float calcAverage(){
        if(totalReviews > 0)
        return (float) (totalScore*1.0/totalReviews);
        else return 0;
    }

}
