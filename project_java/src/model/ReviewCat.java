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
import java.util.stream.Collectors;

public class ReviewCat implements IReviewCat, Serializable {

    private Map<String,Review> reviews;

    /**
     * Construtor de ReviewCat
     */
    public ReviewCat(){
        this.reviews = new HashMap<>();
    }

    /**
     * Adiciona uma review no catalogo de reviews
     * @param rev review a adicionar
     */
    public void addReview(Review rev){ this.reviews.put(rev.getReview_id(),rev.clone()); }

    /**
     * Getter de uma review com um codigo especificado, caso exista
     * @param review_id codigo da review
     * @return review com o codigo especificado, ou nulo em caso de nao existir
     */
    public Review getReview(String review_id){
        if(reviews.containsKey(review_id)) return  this.reviews.get(review_id).clone();
        else return null;
    }

    /**
     * Getter do catalogo de reviews
     * @return catalogo de reviews
     */
    public Map<String,Review> getReviews(){
        return reviews.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e->e.getValue().clone()));
    }

    /**
     * Verifica se exista alguma review de um negocio especificado
     * @param businessId id do negocio a verificar se foi avaliado
     * @return resultado da procura
     */
    public boolean businessReviewed(String businessId){
        return reviews.values().stream().anyMatch(e->e.getBusiness_id().equals(businessId));
    }



    public void print(){
          System.out.println(this.reviews.size());
        /*
        for(Review r : this.reviews.values()) {
                  System.out.println(r.toString());
        }  */

    }

    /**
     * ToString de ReviewCat
     * @return ReviewCat em formato string
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for(Review r : this.reviews.values()) {
            System.out.println(r.toString());
        }
        return sb.toString();
    }





}
