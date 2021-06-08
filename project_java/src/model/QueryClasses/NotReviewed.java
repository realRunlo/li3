package model.QueryClasses;

import model.Business;

import java.util.Comparator;
import java.util.TreeSet;

public class NotReviewed  {
    private TreeSet<Business> notReviewed;
    private Integer total;

    public NotReviewed(){
        notReviewed = new TreeSet<>(new NotReviewedComp());
        total = 0;
    }

    public void addBusiness(Business b){
        notReviewed.add(b.clone());
        total++;
    }

    public int getTotal(){
        return notReviewed.size();
    }


    public String toString(){
        StringBuilder sb = new StringBuilder();

        notReviewed.forEach(b-> sb.append(b.getName()).append(";\n"));

        sb.append("Total: ").append(total);

        return sb.toString();
    }




}
