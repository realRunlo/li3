package model.QueryClasses;

/**
 * Auxiliar query7
 */
public class Query7aux {
    private String city;
    private String b_id;
    private int totalReviews;

    /**
     * Construtor de Query7aux
     * @param city cidade do negocio
     * @param b_id id do negocio
     * @param totalReviews total de reviews no negocio
     */
    public Query7aux(String city, String b_id, int totalReviews){
        this.city = city;
        this.b_id = b_id;
        this.totalReviews = totalReviews;
    }

    /**
     * Getter da cidade do negocio
     * @return cidade do negocio
     */
    public String getCity(){return city;}

    /**
     * Getter do id do negocio
     * @return id do negocio
     */
    public String getB_id(){return b_id;}

    /**
     * Getter do total de reviews do negocio
     * @return total de reviews do negocio
     */
    public int getTotalReviews() {
        return totalReviews;
    }
}
