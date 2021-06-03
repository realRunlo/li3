package model;

import java.io.File;
import java.io.IOException;
import java.io.Serializable;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ReviewCat implements Serializable {

    private Map<String,Review> reviews;


    public ReviewCat(){
        this.reviews = new HashMap<>();
    }

    public void addReview(Review rev){
        this.reviews.put(rev.getReview_id(),rev.clone());
    }


    public void loadFromFile(String filename){

        List<String> lines = new ArrayList<>();

        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                String[] data = line.split(";",2);
                Review rev = new Review(data[0],data[1],data[2],Float.parseFloat(data[3]),Integer.parseInt(data[4]),
                                        Integer.parseInt(data[5]), Integer.parseInt(data[6]), LocalDateTime.parse(data[7]),
                                         data[8]);
                addReview(rev);

            }

        } catch (IOException e) {
            //faz qualque coisa,se for dar printf usar metodos da view
        }

    }





}
