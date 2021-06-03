package model;

import java.util.HashMap;
import java.util.Map;

public class UserCat {

    private Map<String,User> users;

    public UserCat(){
        this.users = new HashMap<>();
    }

    public void addUser(User us){
        this.users.put(us.getUser_id(),us);
    }
}
