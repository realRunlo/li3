package model;

public class Business implements IBusiness {
    private String id;
    private String name;
    private String city;
    private String state;
    private String categories;

    @Override
    public Business (String id, String name,String city,String categ){
        this.id = id;
        this.name = name;
        this.city = city;
        this.categories = categ;
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
