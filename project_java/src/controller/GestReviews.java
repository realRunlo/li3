package controller;

import model.Business;
import model.Model;
import model.QueryClasses.NotReviewed;
import model.QueryClasses.ReviewedPerMonth;

import java.io.IOException;
import java.util.*;



public class GestReviews {
    private Model data;

    public GestReviews(){
        data = new Model();
    }


    public GestReviews(String userFile, String businessFile, String reviewFile) throws IOException {
        data = new Model(userFile,businessFile,reviewFile);
    }

    public void query1(){
        data.query1();
    }




    //TODO: metodo de teste,apagar para entrega
    public void teste(int teste){
        if(teste == 1 ) System.out.println(data.query1().toString());
        if(teste == 4) {
            ArrayList<ReviewedPerMonth> months = data.query4("8zehGz9jnxPqXtOc7KaJxA");
            months.forEach(k->System.out.println(k.toString()));
        }
        if(teste == 7){
            data.query7().forEach((k,v) -> {System.out.println();
                System.out.println(k);
                v.forEach(System.out::println);
            });
        }
        if(teste ==10){
            System.out.println(data.query10().toString());
        }
    }








}
