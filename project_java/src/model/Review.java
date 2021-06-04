package model;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Review {

    private String review_id;
    private String user_id;
    private String business_id;
    private float stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDateTime date;
    private String txt;


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

    public Review(){
        this.review_id = "";
        this.user_id = "";
        this.business_id = "";
        this.stars = 0;
        this.useful = 0;
        this.funny = 0;
        this.cool = 0;
       // this.date =
        this.txt = "";
    }

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

    public String getReview_id() { return review_id; }

    public String getUser_id() { return user_id; }

    public String getBusiness_id() { return business_id; }

    public float getStars() { return stars; }

    public int getUseful() { return useful; }

    public int getFunny() { return funny; }

    public int getCool() { return cool; }

    public LocalDateTime getDate() { return date; }

    public String getTxt() { return txt; }


    public static boolean validReview(String line){
        String[] data = line.split(";",9);

        return !data[0].equals("") && !data[1].equals("") && !data[2].equals("") &&
                data[3].matches("[-+]?[0-9]*\\.?[0-9]+") && data[4].matches("[-+]?[0-9]*")
                && data[5].matches("[-+]?[0-9]*") && data[6].matches("[-+]?[0-9]*")
                && !data[7].equals("");

    }

    public static Review createReview(String line){
            String[] data = line.split(";",9);
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
            return new Review(
                    data[0],data[1],data[2],Float.parseFloat(data[3]),Integer.parseInt(data[4]),
                    Integer.parseInt(data[5]), Integer.parseInt(data[6]), LocalDateTime.parse(data[7],formatter),
                    data[8]);
    }



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
    public Review clone(){return new Review(this);}




}
