package model;

public interface IBusiness {

    /**
     * Getter do id do negocio
     * @return id do negocio
     */
    String getId() ;

    /**
     * Getter do nome do negocio
     * @return nome do negocio
     */
    String getName();

    /**
     * Getter da cidade do negocio
     * @return cidade do negocio
     */
    String getCity();

    /**
     * Getter do estado do negocio
     * @return estado do negocio
     */
    String getState();

    /**
     * Getter das categorias do negocio
     * @return categorias do negocio
     */
    String getCategories();

    /**
     * Clone de Business
     * @return clone
     */
    Business clone ();

    /**
     * ToString de Business
     * @return Business em formato string
     */
    String toString();    
}
