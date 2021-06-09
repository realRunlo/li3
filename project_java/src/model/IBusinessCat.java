package model;

import java.util.Map;

public interface IBusinessCat {
    void addBusiness(Business biz) ;
    Map <String,Business> getBusinesses();
    boolean containsId(String id);
    int size();
    
}
