package model;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BusinessCat{

    private Map<String,Business> bussinesses;

    public BusinessCat(){
        this.bussinesses = new HashMap<>();
    }

    public void addBusiness(Business biz) {
        this.bussinesses.put(biz.getId(),biz.clone());
    }

    public void loadFromFile(String filename){
        List<String> lines;
        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines) {
                if (Review.validReview(line)) {
                    Business biz = new Business(line);
                    addBusiness(biz);
                }
            }
            
        } catch (IOException e) {
            e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");
        }
    }

    public int size(){
        return this.bussinesses.size();
    }

}
