package model.QueryClasses;

import java.util.HashMap;

public class ReviewedPerMonth {
    private int totalReviews;
    private int uniqueReviews;
    private float average;
    private float totalScore;
    private HashMap<String,Integer> uniqueUserReviews;

    public ReviewedPerMonth(){
        totalReviews = 0;
        uniqueReviews = 0;
        average = 0;
        totalScore = 0;
        uniqueUserReviews = new HashMap<>();
    }

    public int getTotalReviews(){return totalReviews;}

    public int getUniqueReviews() {
        return uniqueReviews;
    }

    public float getAverage() {
        return average;
    }

    public void incTotalReviews(float score,String user_id){
        totalScore += score;
        totalReviews++;
        if(!uniqueUserReviews.containsKey(user_id)) {
            uniqueReviews++;
            uniqueUserReviews.put(user_id,0);
        }
        average = totalScore/totalReviews;
    }

    public String toString(){
        return "Total reviews: " + totalReviews +"\nUnique reviews: " + uniqueReviews + "\nAverage: " + average +"\n";
    }


}
