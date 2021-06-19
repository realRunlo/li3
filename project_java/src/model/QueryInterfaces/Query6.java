package model.QueryInterfaces;


import model.QueryClasses.TopReviewsAux;

import java.util.List;

/**
 * Interface query6
 */
public interface Query6 {
    /**
     * Query6
     * @param top numero de negocios por ano
     * @return conjunto dos top negócios mais avaliados (com mais reviews) em cada
     * ano, indicando o número total de distintos utilizadores que o avaliaram;
     */
    public List<TopReviewsAux> query6(int top);
}
