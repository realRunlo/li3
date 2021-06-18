package model;

import java.util.Map;

public interface IUserCat {

    /**
     * Adiciona um user no catalogo de users
     * @param us user a adicionar
     */
    void addUser(User us);

    /**
     * Getter do catalogo de users
     * @return catalogo de users
     */
    Map<String,User> getUsers();

    /**
     * Verifica se um determinado user existe no catalogo de users
     * @param id id do user a procurar
     * @return resultado da procura
     */
    boolean containsId(String id);
}
