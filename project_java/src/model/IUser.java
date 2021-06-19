package model;

/**
 * Interface user
 */
public interface IUser {
    /**
     * Getter do id do user
     * @return id do user
     */
    String getUser_id();

    /**
     * Getter do nome do user
     * @return nome do user
     */
    String getName();

    /**
     * Getter dos amigos do user
     * @return amigos do user
     */
    String getFriends();

    /**
     * Clone de User
     * @return clone
     */
    User clone();

    /**
     * ToString de User
     * @return User em formato string
     */
    String toString();
}
