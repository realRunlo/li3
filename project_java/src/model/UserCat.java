package model;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class UserCat implements IUserCat{

    private Map<String,User> users;

    /**
     * Construtor de UserCat
     */
    public UserCat(){
        this.users = new HashMap<>();
    }

    /**
     * Adiciona um user no catalogo de users
     * @param us user a adicionar
     */
    public void addUser(User us){
        this.users.put(us.getUser_id(),us.clone());
    }

    /**
     * Getter do catalogo de users
     * @return catalogo de users
     */
    public Map<String,User> getUsers(){
        return users.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e->e.getValue().clone()));
    }

    /**
     * Verifica se um determinado user existe no catalogo de users
     * @param id id do user a procurar
     * @return resultado da procura
     */
    public boolean containsId(String id){
        return users.containsKey(id);
    }

    public void print(){
        System.out.println(this.users.size());
        /*
        for(User r : this.users.values()) {
            System.out.println(r.toString());
        }*/

    }
}
