package model.QueryClasses;

import java.util.HashSet;
import java.util.Set;

/**
 * Reviews pelo nome do negócio
 */
public class ReviewsByBizName {
    private String business_name;
    private int total_reviews;
    private Set<String> uniqueUsers = new HashSet<>();

    /**
     * Construtor de ReviewsByBizName
     * @param business_name nome do negocio
     * @param total_reviews total de reviews no negocio
     */
    public ReviewsByBizName(String business_name,int total_reviews){
        this.business_name = business_name;
        this.total_reviews = total_reviews;
    }

    /**
     * Getter do nome do negocio
     * @return nome do negocio
     */
    public String getName(){return this.business_name;}

    /**
     * Getter do total de reviews no negocio
     * @return total de reviews no negocio
     */
    public int getTotal(){return this.total_reviews;}

    /**
     * Incrementa o numero de reviews do negocio
     */
    public void incTotal(){this.total_reviews++;}

    /**
     * Incrementa o total de reviews no negocio, verificando se o
     * user que fez a review ja tinha feito reviews antes
     * @param u_id user a verificar
     */
    public void incTotal(String u_id){
        incTotal();
        uniqueUsers.add(u_id);
    }

    /**
     * Getter da quantidade de users distintos que fizeram review
     * no negocio
     * @return quantidade de users unicos
     */
    public int getUniqueReviews(){return uniqueUsers.size();}

}
