package model.QueryClasses;

import java.time.LocalDateTime;
import java.util.List;
import java.util.Map;

public class UserReviewsByMonth {

    private int totalReviews;
    private int variety;
    private double average;


    public UserReviewsByMonth(int totalReviews,int variety,double average){
        this.totalReviews = totalReviews;
        this.variety = variety;
        this.average = average;
    }



    public int getTotalReviews(){
        return totalReviews;
    }

    public int getVariety(){
        return variety;
    }

    public double getAverage(){
        return average;
    }


    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("Total reviews: ").append(totalReviews).append(", Variety: ").append(variety).append(", Average: ").append(average);

        return sb.toString();
    }










}
