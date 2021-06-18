package model.QueryClasses;

import model.Business;

import java.util.*;
import java.util.stream.Collectors;

public class TopReviews {
    private int top;
    private Map<Integer, Map<String,TopReviewsAux>> busScore = new HashMap<>();

    /**
     * Construtor de TopReviews
     * @param top guarda o top pretendido para quando for a devolver
     *            o conjunto dos negocios mais avaliados
     */
    public TopReviews(int top){
        this.top = top;
    }

    /**
     * Adiciona uma review em um negocio em uma certa data
     * @param date data da review
     * @param b_id negocio a ser avaliado
     * @param u_id user que avaliou
     */
    public void addReview(int date,String b_id,String u_id,float score){
        if(!busScore.containsKey(date))
            busScore.put(date,new HashMap<>());
        if(!busScore.get(date).containsKey(b_id))
            busScore.get(date).put(b_id,new TopReviewsAux(b_id,date));

        busScore.get(date).get(b_id).addReview(u_id,score);
    }


    /**
     * Torna o map dos scores dos negocios em diferentes anos em uma lista
     * com apenas 'top' negocios em cada ano
     * @return lista de busScore
     */
    public List<TopReviewsAux> topBus(Comparator<TopReviewsAux> comparator){
        Map<Integer,TreeSet<TopReviewsAux>> sort = new HashMap<>();
        busScore.forEach((k,v)-> {
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
