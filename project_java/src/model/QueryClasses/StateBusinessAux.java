package model.QueryClasses;

public class StateBusinessAux {
    private businessReviews b;
    private String id;
    private String city;
    private String state;

    /**
     * Construtor de StateBusinessAux
     */
    public StateBusinessAux(){
        b = new businessReviews();
        id = "";
        city = "";
        state = "";
    }

    /**
     * Construtor de StateBusinessAux
     * @param b informacao do total de reviews e score do negocio
     * @param id nome do negocio
     * @param city cidade do negocio
     * @param state estado do negocio
     */
    public StateBusinessAux(businessReviews b, String id, String city, String state){
        this.b = b.clone();
        this.id = id;
        this.city = city;
        this.state = state;
    }

    /**
     * Getter de businessReviews
     * @return businessReviews
     */
    public businessReviews getBusinessReviews(){return b.clone();}

    /**
     * Getter do nome do negocio
     * @return nome do negocio
     */
    public String getId(){return id;}

    /**
     * Getter da cidade do negocio
     * @return cidade do negocio
     */
    public String getCity(){return city;}

    /**
     * Getter do estado do negocio
     * @return estado do negocio
     */
    public String getState(){return state;}





}
