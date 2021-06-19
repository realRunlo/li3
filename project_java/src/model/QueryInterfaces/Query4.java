package model.QueryInterfaces;

import model.QueryClasses.ReviewedPerMonth;

import java.util.ArrayList;

/**
 * Interface query4
 */
public interface Query4 {
    /**
     * Query4
     * @param b_id codigo do negocio a analisar
     * @return mês a mês, quantas vezes foi avaliado,
     * por quantos users diferentes e a média de classificação
     */
    public ArrayList<ReviewedPerMonth> query4(String b_id);
}
