public interface IBusiness {
    void Business(String id, String name, String city, String categ) ;
    String getId();
    String getName();
    String getCity();
    String getState();
    String toString();
    Business clone();
}
