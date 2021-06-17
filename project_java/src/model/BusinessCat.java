package model;

import java.io.IOException;
import java.io.Serializable;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class BusinessCat implements IBusinessCat, Serializable {

    private Map<String,Business> bussinesses;

    /**
     * Construtor de BusinessCat
     */
    public BusinessCat(){
        this.bussinesses = new HashMap<>();
    }

    /**
     * Adiciona um business no catalogo
     * @param biz business a adicionar
     */
    public void addBusiness(Business biz) {
        this.bussinesses.put(biz.getId(),biz.clone());
    }

    /**
     * Getter do catalogo de negocios
     * @return catalogo de negocios
     */
    public Map<String,Business> getBusinesses(){
        return bussinesses.entrySet().stream().collect(Collectors.toMap(Map.Entry::getKey, e->e.getValue().clone()));
    }

    /**
     * Verifica se existe algum negocio no catalogo com o dado codigo
     * @param id codigo a procurar
     * @return resultado da procura
     */
    public boolean containsId(String id){return this.bussinesses.containsKey(id);}

    /**
     * Calculo a quantidade de negocios no catalogo
     * @return total de negocios
     */
    public int size(){
        return this.bussinesses.size();
    }

}
