package model;

import model.QueryClasses.ReviewedPerMonth;

import java.util.List;

public interface Statistics {

    /**
     * Retorna a lista dos ficheiros lidos
     * @return lista dos ficheiros lidos
     */
    List<String> getFilesLoaded();

    /**
     * Retorna o numero de reviews invalidadas
     * @return total de reviews invalidadas
     */
    int getInvalidReviews();

    /**
     * Metodo que retorna o numero total de negocios
     * @return numero total de negocios
     */
    int getNumberOfBusinesses();

    /**
     * Calcula o numero total de negocios distintos avaliados
     * @return numero total de negocios distintos avaliados
     */
    int getDistinctBusinessesReviewed();

    /**
     * Calcula o numero de users diferentes
     * @return numero de users
     */
    int getNumberOfUsers();

    /**
     * Calcula o numero de users ativos (realizaram reviews)
     * @return numero de users ativos
     */
    int getNumberOfUserReviewers();

    /**
     * Calcula o numero de users inativos (nao realizaram reviews)
     * @return numero de users inativos
     */
    int getUsersNotReviewers();

    /**
     * Calcula o numero de reviews sem impacto (somatorio dos parametros cool,funny ou useful igual a 0)
     * @return numero de reviews sem impacto
     */
    int getNonImpactReviews();

    /**
     * Calcula, mes a mes, o numero total de reviews, numero de users distintos que
     * fizeram reviews, o score medio
     * @return lista dos calculos dos varios meses
     */
    List<ReviewedPerMonth> getReviewsPerMonth();

    /**
     * Torna os dados das estatisticas em formato string
     * @return estatisticas
     */
    String statistics();
}
