package queries;

import model.Business;
import model.Model;
import model.QueryClasses.NotReviewed;
import model.QueryClasses.ReviewsByBizName;
import model.QueryClasses.ReviewsByBizNameComp;
import model.Review;
import model.User;
import org.junit.Before;
import org.junit.Test;

import java.io.IOException;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

/**
 * Classe de teste de execucao de uma query com uso de diferentes collections
 * Procuramos ver as diferencas nos tempos de pesquisa assim como de insercao
 */
public class query5Test {
    private Model data = new Model();
    private List<Business> businessesList = new ArrayList<>();
    private Set<Business> businessesSet = new HashSet<>();
    private LinkedList<Business> businessesLinkedList = new LinkedList<>();
    private LinkedHashMap<String,Business> businessesLinkedHash = new LinkedHashMap<>();
    private static final String objectFile = "gestReviews.dat";
    private static final String userTestSearch = "ak0TdVmGKo4pwqdJSTLwWw"; //poucas reviews, poucos elementos a inserir no array
    private static final String userTestInsertion = "RtGqdDBvvBCjcu5dUqwfzA"; //muitas reviews, muitos elementos a inserir no array


    @Before
    public void setup() throws IOException, ClassNotFoundException {
        data = new Model(objectFile);
        data.getBusinesses().forEach((k,v)->{
            businessesList.add(v);
            businessesSet.add(v);
            businessesLinkedList.add(v);
            businessesLinkedHash.put(k,v);
        });
    }

    /**
     * Teste de procura de negocios com reviews
     */
    @Test
    public void query5Test(){
        double mili = (Math.pow(10,-6));
        Map<String,Business> bus = data.getBusinesses();
        double startTime = System.nanoTime();
        int elementNormalSearch = query5(userTestSearch,bus).size();
        double endTime = System.nanoTime();
        double timeNormalSearch = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementNormalInsertion = query5(userTestInsertion,bus).size();
        endTime = System.nanoTime();
        double timeNormalInsertion = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementsListSearch = query5TestList(businessesList,userTestSearch).size();
        endTime = System.nanoTime();
        double timeListSearch = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementsListInsertion = query5TestList(businessesList,userTestInsertion).size();
        endTime = System.nanoTime();
        double timeListInsertion= (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementSetSearch = query5TestSet(businessesSet,userTestSearch).size();
        endTime = System.nanoTime();
        double timeSetSearch = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementSetInsertion = query5TestSet(businessesSet,userTestInsertion).size();
        endTime = System.nanoTime();
        double timeSetInsertion = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementLinkedSearch = query5TestLinkedList(businessesLinkedList,userTestSearch).size();
        endTime = System.nanoTime();
        double timeLinkedSearch = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementLinkedInsertion = query5TestLinkedList(businessesLinkedList,userTestInsertion).size();
        endTime = System.nanoTime();
        double timeLinkedInsertion= (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementLinkedHashSearch = query5TestLinkedHashMap(businessesLinkedHash,userTestSearch).size();
        endTime = System.nanoTime();
        double timeLinkedHashSearch = (endTime - startTime) * mili;

        startTime = System.nanoTime();
        int elementLinkedHashInsertion = query5TestLinkedHashMap(businessesLinkedHash,userTestInsertion).size();
        endTime = System.nanoTime();
        double timeLinkedHashInsertion = (endTime - startTime) * mili;



        System.out.println("------------Query5----------\n"+

                "********Search********\n"+
                "Used method (elementos "+ elementNormalSearch+"): " + timeNormalSearch +" miliseconds\n"+
                "List method (elementos "+ elementsListSearch+"): " + timeListSearch +" miliseconds\n"+
                "Set method (elementos "+ elementSetSearch+"): " + timeSetSearch +" miliseconds\n"+
                "Linked method (elementos "+ elementLinkedSearch+"): " + timeLinkedSearch +" miliseconds\n"+
                "Linked Hash method (elementos "+ elementLinkedHashSearch+"): " + timeLinkedHashSearch +" miliseconds\n"+
                "**********************\n\n"+
                "*******Insertion******\n"+
                "Used method (elementos "+ elementNormalInsertion+"): " + timeNormalInsertion +" miliseconds\n"+
                "List method (elementos "+ elementsListInsertion+"): " + timeListInsertion +" miliseconds\n"+
                "Set method (elementos "+ elementSetInsertion+"): " + timeSetInsertion +" miliseconds\n"+
                "Linked method (elementos "+ elementLinkedInsertion+"): " + timeLinkedInsertion +" miliseconds\n"+
                "Linked Hash method (elementos "+ elementLinkedHashInsertion+"): " + timeLinkedHashInsertion +" miliseconds\n"+
                "**********************\n"+
                "-------------------------------------\n"
        );
    }

    /**
     * Query5, sem o gasto de tempo de fazer getBusinesses
     * @param user_id
     * @return
     */
    public ArrayList<ReviewsByBizName> query5(String user_id,Map<String,Business> bus){

        Map<String,Review> reviews = data.getReviews().values().stream()
                .filter((r)->r.getUser_id().equals(user_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();


        for(Review rev : reviews.values()){
            String b_id = rev.getBusiness_id();
            if(reviews_bizs.containsKey(b_id)){
                reviews_bizs.get(b_id).incTotal();
            }else{
                reviews_bizs.put(b_id,new ReviewsByBizName(bus.get(b_id).getName(),1));
            }
        }

        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());

        return reviews_bizsList;

    }


    /**
     * Teste para listas
     * @param list
     * @param user_id
     * @return
     */
    public ArrayList<ReviewsByBizName> query5TestList(List<Business> list,String user_id){
        Map<String,Review> reviews = data.getReviews().values().stream()
                .filter((r)->r.getUser_id().equals(user_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();


        reviews.forEach((k,v)->{
            String b_id = v.getBusiness_id();
            if(reviews_bizs.containsKey(b_id)){
                reviews_bizs.get(b_id).incTotal();
            }else{
                String name = list.stream().filter(b->b.getId().equals(b_id)).findFirst().get().getName();
                reviews_bizs.put(b_id,new ReviewsByBizName(name,1));
            }
        });

        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());
        return reviews_bizsList;
    }

    /**
     * Teste para set
     * @param set
     * @param user_id
     * @return
     */
    public ArrayList<ReviewsByBizName> query5TestSet(Set<Business> set,String user_id){
        Map<String,Review> reviews = data.getReviews().values().stream()
                .filter((r)->r.getUser_id().equals(user_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();


        reviews.forEach((k,v)->{
            String b_id = v.getBusiness_id();
            if(reviews_bizs.containsKey(b_id)){
                reviews_bizs.get(b_id).incTotal();
            }else{
                String name = set.stream().filter(b->b.getId().equals(b_id)).findFirst().get().getName();
                reviews_bizs.put(b_id,new ReviewsByBizName(name,1));
            }
        });

        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());
        return reviews_bizsList;
    }

    /**
     * Teste para linked lists
     * @param linkedList
     * @param user_id
     * @return
     */
    public ArrayList<ReviewsByBizName> query5TestLinkedList(LinkedList<Business> linkedList,String user_id){
        Map<String,Review> reviews = data.getReviews().values().stream()
                .filter((r)->r.getUser_id().equals(user_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();


        reviews.forEach((k,v)->{
            String b_id = v.getBusiness_id();
            if(reviews_bizs.containsKey(b_id)){
                reviews_bizs.get(b_id).incTotal();
            }else{
                String name = linkedList.stream().filter(b->b.getId().equals(b_id)).findFirst().get().getName();
                reviews_bizs.put(b_id,new ReviewsByBizName(name,1));
            }
        });

        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());
        return reviews_bizsList;
    }

    /**
     * Teste para linked hash
     * @param linkedHash
     * @param user_id
     * @return
     */
    public ArrayList<ReviewsByBizName> query5TestLinkedHashMap(LinkedHashMap<String,Business> linkedHash,String user_id){
        Map<String,Review> reviews = data.getReviews().values().stream()
                .filter((r)->r.getUser_id().equals(user_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();


        reviews.forEach((k,v)->{
            String b_id = v.getBusiness_id();
            if(reviews_bizs.containsKey(b_id)){
                reviews_bizs.get(b_id).incTotal();
            }else{
                String name =linkedHash.get(b_id).getName();
                reviews_bizs.put(b_id,new ReviewsByBizName(name,1));
            }
        });

        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());
        return reviews_bizsList;
    }



}
