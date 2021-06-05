package model;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ReviewCat implements Serializable {

    private Map<String,Review> reviews;


    public ReviewCat(){
        this.reviews = new HashMap<>();
    }

    public void addReview(Review rev){ this.reviews.put(rev.getReview_id(),rev.clone()); }

    public Review getReview(String review_id){
       return  this.reviews.get(review_id).clone();
    }


    public void loadFromFile(String filename) throws IOException {

        List<String> lines;
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                if(Review.validReview(line)){
                    Review rev = new Review(line);
                    addReview(rev);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");
        }

    }

    public void print(){
          System.out.println(this.reviews.size());
        /*
        for(Review r : this.reviews.values()) {
                  System.out.println(r.toString());
        }  */

    }





}
