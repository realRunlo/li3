package model.QueryInterfaces;

import model.QueryClasses.TopReviewsAux;

import java.util.List;

/**
 * Interface query9
 */
public interface Query9 {
    /**
     * Query9
     * @param b_id negocio cujas reviews procura
     * @param top top users
     * @return o conjunto dos top users que mais o
     * avaliaram e, para cada um, qual o valor médio de classificação
     */
    public List<TopReviewsAux> query9(String b_id,int top);
}
