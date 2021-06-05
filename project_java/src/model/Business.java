package model;

import java.time.format.DateTimeFormatter;

public class Business{
    private String id;
    private String name;
    private String city;
    private String state;
    private String categories;

    public Business (String id, String name,String city,String categ){
        this.id = id;
        this.name = name;
        this.city = city;
        this.categories = categ;
    }
    public Business(String line){
        String[] data = line.split(";",5);
        this.id = data[0];
        this.name = data[1];
        this.city = data[2];
        this.state = data[3];
        this.categories = data[4];
    }

    public Business (Business b){
        this.id = b.getId();
        this.name = b.getName();
        this.city = b.getCity();
        this.categories = b.getCategories();
    }

    public String getId() {
        return this.id;
    }
    public String getName() {
        return this.name;
    }
    public String getCity() {
        return this.city;
    }
    public String getState(){
        return this.state;
    }
    public String getCategories(){
        return this.categories;
    }

    public Boolean validBusiness(String line){
        String[] data = line.split(";",5);
        return !data[0].equals("") && !data[1].equals("") && !data[2].equals("") && !data[3].equals("")
                && !data[4].equals("");
    }
    public Business clone (){
        return new Business(this);
    }
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
