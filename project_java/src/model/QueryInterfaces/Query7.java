package model.QueryInterfaces;

import model.QueryClasses.Query7aux;

import java.util.List;
/**
 * Interface query7
 */
public interface Query7 {
    /**
     * Query7
     * @return para cada cidade, a lista dos três mais famosos negócios em termos de
     * número de reviews;
     */
    public List<Query7aux> query7();
}
