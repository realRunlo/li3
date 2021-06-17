package model.QueryClasses;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StateBusiness {
    private Map<String,Map<String, Map<String, businessReviews>>> states;


    /**
     * Construtor de StateBusiness
     */
    public StateBusiness(){
        states = new HashMap<>();
    }

    /**
     * Adiciona um estado na hash,verificando se o mesmo
     * nao ja existe
     * @param state estado a adicionar
     */
    public void addState(String state){
        if(!existsState(state))
            states.put(state,new HashMap<>());
    }

    /**
     * Verifica se existe um estado
     * @param state estado a procurar
     * @return resultado da verificacao
     */
    public boolean existsState(String state){
        return states.containsKey(state);
    }

    /**
     * Adiciona uma cidade em uma hash de um estado,
     * verificando se tal estado e cidade existem,
     * criando o estado se necessario
     * @param state estado da cidade
     * @param city cidade a adicionar
     */
    public void addCity(String state, String city){
        if(!existsState(state)) addState(state);
        if(!existsCity(state,city))
            states.get(state).put(city,new HashMap<>());
    }

    /**
     * Verifica se existe uma cidade na hash de um certo estado
     * @param state estado da cidade
     * @param city cidade a procurar
     * @return resultado da procura
     */
    public boolean existsCity(String state, String city){
        if(existsState(state)) return states.get(state).containsKey(city);
        else return false;
    }

    /**
     * Adiciona um certo negocio na hash de uma cidade de um certo estado, verificando
     * se tal cidade e estado existem, criando-os se necessario
     * @param state estado do negocio
     * @param city cidade do negocio
     * @param b_id negocio a adicionar
     */
    public void addBusiness(String state, String city, String b_id){
        if(!existsState(state)){
            addState(state);
        }
        if(!existsCity(state,city)){
            addCity(state,city);
        }
        if(!existsBusiness(state,city,b_id))
            states.get(state).get(city).put(b_id,new businessReviews());
    }

    /**
     * Verifica se existe um negocio em uma cidade e estado especificados
     * @param state estado do negocio
     * @param city cidade do negocio
     * @param b_id negocio a procurar
     * @return reultado da procura
     */
    public boolean existsBusiness(String state, String city, String b_id){
        if(existsCity(state,city)) return states.get(state).get(city).containsKey(b_id);
        else return false;
    }

    /**
     * Atualiza o score total de umaum negocio, verificando se o negocio,cidade e estado
     * existem, criando-os se necessario
     * @param state estado do negocio
     * @param city cidade do negocio
     * @param b_id negocio a atualizar/criar
     * @param score score da review feita no negocio
     */
    public void updateBusinessScore(String state, String city, String b_id, float score){
        if(!existsBusiness(state,city,b_id)){
            addBusiness(state,city,b_id);
        }
        states.get(state).get(city).get(b_id).addReview(score);
    }

    /**
     * Torna a hash dos negocios em uma lista de forma a ser
     * facilmente printavel por pagina na view
     * @return hash em formato lista
     */
    public List<StateBusinessAux> toList(){
        List<StateBusinessAux> list = new ArrayList<>();
        states.forEach((state,c)->
                c.forEach((city,b)->
                        b.forEach((business,v)-> list.add(new StateBusinessAux(v,business,city,state)))));

        return list;
    }

    /**
     * ToString de StateBusiness
     * @return StateBusiness em formato string
     */
    public String toString(){
        StringBuilder sb = new StringBuilder();
        states.forEach((k,v) -> {
            sb.append("State: ").append(k).append("\n");
            v.forEach((l,b)->{
                sb.append("\tCity: ").append(l).append("\n");
                b.forEach((q,w) ->{
                    sb.append("\t\t").append(q).append(" :").append(w.calcAverage()).append("\n");
                });
            });
        });
        return sb.toString();
    }

}
