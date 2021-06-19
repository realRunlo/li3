package model.QueryInterfaces;

import model.QueryClasses.ReviewedPerMonth;

import java.util.ArrayList;

/**
 * Interface query3
 */
public interface Query3 {
    /**
     * Query3
     * @param user_id
     * @return para cada mês, quantas reviews fez,
     * quantos negócios distintos avaliou e que nota média atribuiu
     */
    public ArrayList<ReviewedPerMonth> query3(String user_id);
}
