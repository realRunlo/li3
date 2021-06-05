package model;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BusinessCat{

    private Map<String,Business> bussinesses;

    public BusinessCat(){
        this.bussinesses = new HashMap<>();
    }

    public void addBusiness(Business biz) {
        this.bussinesses.put(biz.getId(),biz.clone());
    }

    public boolean containsId(String id){return this.bussinesses.containsKey(id);}


    public int size(){
        return this.bussinesses.size();
    }

}
