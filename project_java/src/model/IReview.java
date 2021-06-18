package model;

import java.time.LocalDateTime;

public interface IReview {

    /**
     * Getter do id da review
     * @return id da review
     */
    String getReview_id();

    /**
     * Getter do id do user que criou a review
     * @return id do user
     */
    String getUser_id();

    /**
     * Getter do id do negocio avaliado
     * @return id do negocio
     */
    String getBusiness_id();

    /**
     * Getter do score da review
     * @return score da review
     */
    float getStars();

    /**
     * Getter do impatco-util
     * @return impacto-util
     */
    int getUseful();

    /**
     * Getter do impacto-comico
     * @return impacto-comico
     */
    int getFunny() ;

    /**
     * Getter do impacto-fixe
     * @return impacto-fixe
     */
    int getCool();

    /**
     * Getter da data de criacao da review
     * @return data de criacao
     */
    LocalDateTime getDate();

    /**
     * Getter do texto da review
     * @return texto da review
     */
    String getTxt();

    /**
     * ToString de Review
     * @return Review em formato string
     */
    String toString();

    /**
     * Clone de Review
     * @return clone
     */
    Review clone();    
}
