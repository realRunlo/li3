package model.QueryClasses;

import java.util.HashSet;
import java.util.Set;

/**
 * Reviews pelo nome do negócio
 */
public class ReviewsByBizName {
    private String business_name;
    private int total_reviews;
    private Set<String> uniqueUsers = new HashSet<>();

    public ReviewsByBizName(String business_name,int total_reviews){
        this.business_name = business_name;
        this.total_reviews = total_reviews;
    }

    public String getName(){return this.business_name;}
    public int getTotal(){return this.total_reviews;}
    public void incTotal(){this.total_reviews++;}

    public void incTotal(String u_id){
        uniqueUsers.add(u_id);
    }

    public int getUniqueReviews(){return uniqueUsers.size();}

}
