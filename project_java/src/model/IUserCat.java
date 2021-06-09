package model;

import java.util.Map;

public interface IUserCat {
    void addUser(User us);
    Map<String,User> getUsers();
    boolean containsId(String id);
}
