package model.QueryInterfaces;

import model.QueryClasses.TopReviewsAux;

import java.util.List;

/**
 * Interface query8
 */
public interface Query8 {
    /**
     * Query8
     * @param top numero de top user reviewers
     * @return códigos dos top utilizadores que
     * avaliaram mais negócios diferentes, indicando quantos, sendo o critério de
     * ordenação a ordem decrescente do número de negócios
     */
    public List<TopReviewsAux> query8(int top);
}
