package model.QueryClasses;

import java.util.HashSet;
import java.util.Set;

public class TopReviewsAux {
    private int date;
    private int total;
    private String bus;
    private Set<String> uniqueUsers = new HashSet<>();

    /**
     * Construtor de TopReviewsAux
     * @param bus business_id do business a guardar
     * @param date data da review
     */
    public TopReviewsAux(String bus, int date){
        this.date = date;
        this.bus = bus;
        this.total = 0;
    }

    /**
     * Adiciona uma review verificando se o user que a realizou
     * ja tinha feito review antes na data da classe
     * @param u_id user quer fez a review
     */
    public void addReview(String u_id){
        uniqueUsers.add(u_id);
        total++;
    }

    /**
     * Retorna o numero de users distintos que fizeram reviews
     * @return total de users distintos
     */
    public int getUniqueUsers(){return uniqueUsers.size();}

    /**
     * Retorna o total de reviews feitas
     * @return reviews feitas
     */
    public int getTotal(){return total;}

    /**
     * Retorna o id
     * @return id
     */
    public String getBus(){return bus;}

    /**
     * Devolve a data
     * @return data
     */
    public int getDate(){return date;}
}
