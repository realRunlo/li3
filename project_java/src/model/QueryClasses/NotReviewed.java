package model.QueryClasses;

import model.Business;

import java.io.Serializable;
import java.util.Comparator;
import java.util.TreeSet;
import java.util.stream.Collectors;

/**
 * Guarda business não avaliados
 */
public class NotReviewed implements Serializable {
    private TreeSet<Business> notReviewed;
    private Integer total;

    /**
     * Construtor de NotReviewed
     */
    public NotReviewed(){
        notReviewed = new TreeSet<>(new NotReviewedComp());
        total = 0;
    }

    /**
     * Adiciona o business na treeSet, utilizando
     * o comparador que ordena por ordem alfabetica
     * @param b business a adicionar
     */
    public void addBusiness(Business b){
        notReviewed.add(b.clone());
        total++;
    }

    /**
     * Retorna o total de negocios registados
     * @return total de negocios
     */
    public int getTotal(){
        return notReviewed.size();
    }

    public TreeSet<Business> getNotReviewed(){
        TreeSet<Business> clone = new TreeSet<>(new NotReviewedComp());
        notReviewed.forEach(b-> clone.add(b.clone()));
        return clone;
    }

    /**
     * ToString da classe NotReviewed
     * @return NotReviewed em formato string
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();

        notReviewed.forEach(b-> sb.append(b.getName()).append(";\n"));

        sb.append("Total: ").append(total);

        return sb.toString();
    }




}
