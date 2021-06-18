package model;

import java.util.Map;

public interface IBusinessCat {

    /**
     * Adiciona um business no catalogo
     * @param biz business a adicionar
     */
    void addBusiness(Business biz) ;

    /**
     * Getter do catalogo de negocios
     * @return catalogo de negocios
     */
    Map <String,Business> getBusinesses();

    /**
     * Verifica se existe algum negocio no catalogo com o dado codigo
     * @param id codigo a procurar
     * @return resultado da procura
     */
    boolean containsId(String id);

    /**
     * Calculo a quantidade de negocios no catalogo
     * @return total de negocios
     */
    int size();
    
}
