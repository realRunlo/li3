package model;

public interface IUser {
    String getUser_id();
    String getName();
    String getFriends();
    User clone();
    String toString();
}
