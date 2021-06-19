package model.QueryClasses;

import model.Business;

import java.util.*;
import java.util.stream.Collectors;

public class TopReviews {
    private int top;
    private Map<Integer, Map<String,TopReviewsAux>> elementScore = new HashMap<>();

    /**
     * Construtor de TopReviews
     * @param top guarda o top pretendido para quando for a devolver
     *            o conjunto dos elementos mais avaliados/ quem mais avaliaram
     */
    public TopReviews(int top){
        this.top = top;
    }

    /**
     * Adiciona uma review em um negocio em uma certa data
     * @param date data da review
     * @param key elemento a ser avaliado
     * @param value value que avaliou
     */
    public void addReview(int date,String key,String value,float score){
        if(!elementScore.containsKey(date))
            elementScore.put(date,new HashMap<>());
        if(!elementScore.get(date).containsKey(key))
            elementScore.get(date).put(key,new TopReviewsAux(key,date));

        elementScore.get(date).get(key).addReview(value,score);
    }


    /**
     * Torna o map dos scores em diferentes datas em uma lista
     * com apenas 'top' keys em cada data,
     * @param comparator comparador utilizador pelo treeSet
     * @return lista de elementScore
     */
    public List<TopReviewsAux> topBus(Comparator<TopReviewsAux> comparator){
        Map<Integer,TreeSet<TopReviewsAux>> sort = new HashMap<>();
        elementScore.forEach((k,v)-> {
            sort.put(k,new TreeSet<>(comparator));
            v.forEach((s,t) ->{
                sort.get(k).add(t);
            });
        });
        List<TopReviewsAux> result = new ArrayList<>();
        sort.forEach((k,v)->{
            List<TopReviewsAux> yearTop;
            if(v.size() < top){
                yearTop = new ArrayList<>(v).subList(0,v.size());
            }else{
                yearTop = new ArrayList<>(v).subList(0,top);
            }
            result.addAll(yearTop);
        });

        return result;
    }




}
