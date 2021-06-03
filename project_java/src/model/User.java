package model;

public class User {

    private String user_id;
    private String name;
    private String friends;


    public User(String user_id,String name,String friends){
        this.user_id = user_id;
        this.name = name;
        this.friends = friends;
    }

    public User(User us){
        this.user_id = us.user_id;
        this.name = us.name;
        this.friends = us.friends;
    }


    public String getUser_id(){return this.user_id;}

    public String getName() {return this.name;}

    public String getFriends() { return this.friends;}

    public User clone(){ return new User(this);}





}
