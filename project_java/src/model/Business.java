package model;

import java.io.Serializable;
import java.time.format.DateTimeFormatter;

public class Business implements IBusiness, Serializable {
    private String id;
    private String name;
    private String city;
    private String state;
    private String categories;

    /**
     * Construtor de Business
     * @param id id do negocio
     * @param name nome do negocio
     * @param city cidade do negocio
     * @param categ categorias do negocio
     */
    public Business (String id, String name,String city,String state,String categ){
        this.id = id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = categ;
    }

    /**
     * Construtor de Business
     * @param line string a analisar de modo a carregar um negocio
     */
    public Business(String line){
        String[] data = line.split(";",5);
        this.id = data[0];
        this.name = data[1];
        this.city = data[2];
        this.state = data[3];
        this.categories = data[4];
    }

    /**
     * Construtor de Business
     * @param b negocio a copiar
     */
    public Business (Business b){
        this.id = b.getId();
        this.name = b.getName();
        this.city = b.getCity();
        this.state = b.getState();
        this.categories = b.getCategories();
    }

    /**
     * Getter do id do negocio
     * @return id do negocio
     */
    public String getId() {
        return this.id;
    }

    /**
     * Getter do nome do negocio
     * @return nome do negocio
     */
    public String getName() {
        return this.name;
    }

    /**
     * Getter da cidade do negocio
     * @return cidade do negocio
     */
    public String getCity() {
        return this.city;
    }

    /**
     * Getter do estado do negocio
     * @return estado do negocio
     */
    public String getState(){
        return this.state;
    }

    /**
     * Getter das categorias do negocio
     * @return categorias do negocio
     */
    public String getCategories(){
        return this.categories;
    }

    /**
     * Metodo utilizado para validar se uma string
     * representa um negocio
     * @param line linha possivelmente representante de um negocio
     * @return resultado da validacao
     */
    public static Boolean validBusiness (String line){
        String[] data = line.split(";",5);
        return !data[0].equals("") && !data[1].equals("") && !data[2].equals("") && !data[3].equals("")
                && !data[4].equals("");
    }

    /**
     * Clone de Business
     * @return clone
     */
    public Business clone (){
        return new Business(this);
    }

    /**
     * ToString de Business
     * @return Business em formato string
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(this.getId());
        sb.append(this.getName());
        sb.append(this.getState());
        sb.append(this.getCity());
        sb.append(this.getCategories());
        sb.append("\n");
        return sb.toString();
    }
    
}
