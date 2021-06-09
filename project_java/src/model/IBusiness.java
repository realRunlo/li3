package model;

public interface IBusiness {
    String getId() ;
    String getName();
    String getCity() ;
    String getState();
    String getCategories();
    Business clone ();
    String toString();    
}
