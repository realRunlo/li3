package model.QueryInterfaces;

import model.QueryClasses.ReviewedPerMonth;

/**
 * Interface query2
 */
public interface Query2 {
    /**
     * Query2
     * @param month mes das reviews a procurar
     * @param year ano das reviews a procurar
     * @return número total global de reviews
     * realizadas e o número total de users distintos que as realizaram
     */
    public ReviewedPerMonth query2(int year, int month);
}
