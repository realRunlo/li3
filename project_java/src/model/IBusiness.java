package model;

public interface IBusiness {
    String getId();
    String getName();
    String getCity();
    String getState();
    String toString();
    Business clone();
}
