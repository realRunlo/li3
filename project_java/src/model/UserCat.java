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

public class UserCat {

    private Map<String,User> users;

    public UserCat(){
        this.users = new HashMap<>();
    }

    public void addUser(User us){
        this.users.put(us.getUser_id(),us.clone());
    }

    public Map<String,User> getUsers(){
        return users.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e->e.getValue().clone()));
    }

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
