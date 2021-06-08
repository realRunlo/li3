package model.QueryClasses;

import java.util.HashMap;
import java.util.Map;

public class StateBusiness {
    private Map<String,Map<String, Map<String, businessReviews>>> states;



    public StateBusiness(){
        states = new HashMap<>();
    }


    public void addState(String state){
        if(!existsState(state))
            states.put(state,new HashMap<>());
    }

    public boolean existsState(String state){
        return states.containsKey(state);
    }

    public void addCity(String state, String city){
        if(!existsState(state)) addState(state);
        if(!existsCity(state,city))
            states.get(state).put(city,new HashMap<>());
    }

    public boolean existsCity(String state, String city){
        if(existsState(state)) return states.get(state).containsKey(city);
        else return false;
    }

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

    public boolean existsBusiness(String state, String city, String b_id){
        if(existsCity(state,city)) return states.get(state).get(city).containsKey(b_id);
        else return false;
    }

    public void updateBusinessScore(String state, String city, String b_id, float score){
        if(!existsBusiness(state,city,b_id)){
            addBusiness(state,city,b_id);
        }
        states.get(state).get(city).get(b_id).addReview(score);
    }

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
