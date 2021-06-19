package model.QueryInterfaces;

import model.QueryClasses.NotReviewed;

/**
 * Interface query1
 */
public interface Query1 {
    /**
     * Query1
     * @return lista ordenada alfabeticamente com os identificadores dos negócios nunca
     * avaliados e o seu respetivo total
     */
    public NotReviewed query1();
}
