package model;

import java.util.Map;

/**
 * Interface review catalogo
 */
public interface IReviewCat {

    /**
     * Adiciona uma review no catalogo de reviews
     * @param rev review a adicionar
     */
    void addReview(Review rev);

    /**
     * Getter de uma review com um codigo especificado, caso exista
     * @param review_id codigo da review
     * @return review com o codigo especificado, ou nulo em caso de nao existir
     */
    Review getReview(String review_id);

    /**
     * Getter do catalogo de reviews
     * @return catalogo de reviews
     */
    Map<String,Review> getReviews();

    /**
     * ToString de ReviewCat
     * @return ReviewCat em formato string
     */
    String toString();
}
