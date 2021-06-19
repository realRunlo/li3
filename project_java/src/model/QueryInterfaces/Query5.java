package model.QueryInterfaces;

import model.QueryClasses.ReviewsByBizName;

import java.util.ArrayList;

/**
 * Interface query5
 */
public interface Query5 {
    /**
     * Query5
     * @param user_id codigo do user a analisar
     * @return lista de nomes de negócios que mais
     * avaliou (e quantos), ordenada por ordem decrescente de quantidade e, para
     * quantidades iguais, por ordem alfabética dos negócios
     */
    public ArrayList<ReviewsByBizName> query5(String user_id);
}
