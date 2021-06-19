package model;

import java.io.Serializable;

/**
 * User
 */
public class User implements IUser, Serializable {

    private String user_id;
    private String name;
    private String friends;
    private static final String notLoaded = "NotLoaded";

    /**
     * Construtor de User
     * @param user_id id do user
     * @param name nome do user
     * @param friends amigos do user
     */
    public User(String user_id,String name,String friends){
        this.user_id = user_id;
        this.name = name;
        this.friends = friends;
    }

    /**
     * Construtor de User
     * @param line string a analisar de modo a carregar um user
     * @param loadFriends booleano que indica se os friends sao ou nao
     * carregados de line
     */
    public User(String line,boolean loadFriends){
        String[] data = line.split(";",3);
        this.user_id = data[0];
        this.name = data[1];
        if(loadFriends) this.friends = data[2];
        else this.friends = notLoaded;
    }

    /**
     * Construtor de user
     * @param us user a copiar
     */
    public User(User us){
        this.user_id = us.user_id;
        this.name = us.name;
        this.friends = us.friends;
    }


    public String getUser_id(){return this.user_id;}


    public String getName() {return this.name;}

    public String getFriends() { return this.friends;}

    public User clone(){ return new User(this);}

    /**
     * Metodo utilizado para validar se uma string
     * representa um user
     * @param line linha possivelmente representante de um user
     * @return resultado da validacao
     */
    public static boolean validUser(String line) {
        String[] data = line.split(";",3);

        return !data[0].equals("") && !data[1].equals("");

    }

    public String toString() {
        StringBuilder sb = new StringBuilder("Review {\n");
        sb.append("ID = '").append(user_id).append("'\n");
        sb.append("BusinessID = '").append(name).append("'\n");
        sb.append("UserID = '").append(friends).append("'\n");
        sb.append("\n}");
        return sb.toString();
    }





}
