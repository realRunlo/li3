package model;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class UserCat {

    private Map<String,User> users;

    public UserCat(){
        this.users = new HashMap<>();
    }

    public void addUser(User us){
        this.users.put(us.getUser_id(),us.clone());
    }


    public void loadFromFile(String filename){
        List<String> lines;

        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                if(User.validUser(line)){
                    User us = User.createUser(line);
                    addUser(us);
                }

            }

        } catch (IOException e) {
            e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");
        }
    }

    public void print(){
        System.out.println(this.users.size());
        /*
        for(User r : this.users.values()) {
            System.out.println(r.toString());
        }*/

    }
}
