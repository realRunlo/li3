package model.QueryClasses;

import model.Business;

import java.io.Serializable;
import java.util.Comparator;

/**
 * Comparador da classe NotReviewed
 */
public class NotReviewedComp implements Comparator<Business>, Serializable {
    /**
     * Comparator que ordena businesses alfabeticamente atraves do seu nome
     * @param b1 primeiro business
     * @param b2 business com que vai comparar
     * @return resultado da comparacao
     */
    @Override
    public int compare(Business b1, Business b2){

        return b1.getId().compareTo(b2.getId());
    }
}
