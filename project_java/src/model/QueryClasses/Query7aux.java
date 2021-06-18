package model.QueryClasses;

public class Query7aux {
    private String city;
    private String b_id;
    private int totalReviews;

    public Query7aux(String city, String b_id, int totalReviews){
        this.city = city;
        this.b_id = b_id;
        this.totalReviews = totalReviews;
    }

    public String getCity(){return city;}

    public String getB_id(){return b_id;}

    public int getTotalReviews() {
        return totalReviews;
    }
}
