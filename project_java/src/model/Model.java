package model;

import model.QueryClasses.*;
import model.QueryInterfaces.*;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

public class Model implements Query1, Query3, Query4, Query7, Query10 {

    private UserCat users;
    private ReviewCat reviews;
    private BusinessCat businesses;


    public Model(){
        this.users = new UserCat();
        this.businesses = new BusinessCat();
        this.reviews = new ReviewCat();
    }

    public Model(String userFile, String businessFile, String reviewFile) throws IOException {
        this.users = new UserCat();
        this.businesses = new BusinessCat();
        this.reviews = new ReviewCat();
        load(userFile, businessFile, reviewFile);
    }



    public void load(String users_file,String businesses_file, String reviews_file) throws IOException {
        loadUsers(users_file);
        loadBusinesses(businesses_file);
        loadReviews(reviews_file);
    }

    private void loadUsers(String filename) throws IOException {
        List<String> lines;
        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                if(User.validUser(line)){
                    User us = new User(line);
                   this.users.addUser(us);
                }

            }

        } catch (IOException e) {
            e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");
        }
    }

    private void loadBusinesses(String filename) throws  IOException{
        List<String> lines;
        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines) {
                if (Business.validBusiness(line)) {
                    Business biz = new Business(line);
                    this.businesses.addBusiness(biz);
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");
        }
    }

    private void loadReviews(String filename){
        List<String> lines;
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        try{
            lines = Files.readAllLines(Paths.get(filename), StandardCharsets.UTF_8);

            for(String line : lines){
                if(Review.validReview(line)){ //validate fields of review
                    Review rev = new Review(line);
                    if(this.users.containsId(rev.getUser_id()) && this.businesses.containsId(rev.getBusiness_id())){ //check if users and businesses exist
                        this.reviews.addReview(rev);
                    }

                }
            }

        } catch (IOException e) {
            e.printStackTrace();
            //faz qualque coisa,se for dar printf usar metodos da view
            System.out.println("error");
        }



    }

    public Map<String, Review> getReviews(){return reviews.getReviews();}

    public Map<String, Business> getBusinesses(){return businesses.getBusinesses();}

    public Map<String, User> getUsers() {
        return users.getUsers();
    }

    public boolean businessReviewed(String businessId){
        return reviews.businessReviewed(businessId);
    }

    //Lista ordenada alfabeticamente com os identificadores dos negócios nunca
    //avaliados e o seu respetivo total;
    public NotReviewed query1(){
        NotReviewed results = new NotReviewed();
        Map<String,Business> businesses = getBusinesses();
        Map<String,Review> reviewsSearch = getReviews();

        reviewsSearch.forEach((k,v) -> {
            businesses.remove(v.getBusiness_id());
        });

        businesses.forEach((k,v) -> results.addBusiness(v));
        return results;
    }


    public ArrayList<UserReviewsByMonth> query3(String user_id){

        //contem reviews do dado user
        Map<String,Review> reviews = getReviews().values().stream()
                                    .filter((r)->r.getUser_id().equals(user_id))
                                    .collect(Collectors.toMap(Review::getReview_id, r->r));
        ArrayList<UserReviewsByMonth> reviewsByMonth= new ArrayList<>();
        int totalRevs = 0;
        int variety = 0;
        int totalStars = 0;
        ArrayList<String> varietyList = new ArrayList<>(12);
        for(int i = 1;i<=12;i++){
            for(Review rev : reviews.values()){
                String busId = rev.getBusiness_id();
                if(!varietyList.contains(busId)){
                    varietyList.add(busId);
                    variety++;
                }

                if(rev.getDate().getMonthValue() == i){
                    totalRevs++;
                    totalStars += rev.getStars();

                }
                varietyList.clear();

            }

            reviewsByMonth.add(new UserReviewsByMonth(totalRevs,variety,(double) totalStars/totalRevs));
            totalRevs = 0;
            totalStars = 0;
            variety = 0;
        }

        return reviewsByMonth;
    }



    //Dado o código de um negócio, determinar, mês a mês, quantas vezes foi avaliado,
    //por quantos users diferentes e a média de classificação;
    public ArrayList<ReviewedPerMonth> query4(String b_id){
        //filtrar para ter apenas as reviews sobre o negocio em questao
        Map<String,Review> reviews = getReviews().values().stream()
                .filter((r) -> r.getBusiness_id().equals(b_id))
                .collect(Collectors.toMap(Review::getReview_id, r->r));

        // TODO: apagar quando ja n for preciso testar
        System.out.println("Reviews neste negocio: " + reviews.size());

        ArrayList<ReviewedPerMonth> monthReviews = new ArrayList<>(12);
        for (int i =0; i<12;i++) {
            monthReviews.add(new ReviewedPerMonth());
        }

        reviews.forEach((k,v) -> {
            int month = v.getDate().getMonthValue();
            monthReviews.get(month - 1).incTotalReviews(v.getStars(),v.getUser_id());
                });

        return monthReviews;
    }

    public ArrayList<ReviewsByBizName> query5(String user_id){

        Map<String,Review> reviews = getReviews().values().stream()
                                    .filter((r)->r.getUser_id().equals(user_id))
                                    .collect(Collectors.toMap(Review::getReview_id, r->r));

        Map<String,ReviewsByBizName> reviews_bizs = new HashMap<>();

        for(Review rev : reviews.values()){
            if(reviews.containsKey(rev.getBusiness_id())){
                reviews_bizs.get(rev.getBusiness_id()).incTotal();
            }else{
                reviews_bizs.put(rev.getBusiness_id(),new ReviewsByBizName(rev.getBusiness_id(),1));
            }
        }
        
        ArrayList<ReviewsByBizName> reviews_bizsList = new ArrayList<>(reviews_bizs.values());
        reviews_bizsList.sort(new ReviewsByBizNameComp());

        return reviews_bizsList;

    }


    //Determinar, para cada cidade, a lista dos três mais famosos negócios em termos de
    //número de reviews;
    public Map<String, List<String>> query7(){

        //Hash das diferentes cidades
        //a key sera o numero de cidades e o value sera um hashMap com os business dessa cidade
        Map<String,Map<String,Integer>> cities = new HashMap<>();
        Map<String,Business> businesses = getBusinesses();

        getReviews().forEach((k,v) ->{
            //verifica se ja existe a cidade na hash
            String b_id_search = v.getBusiness_id();
            String city= businesses.get(b_id_search).getCity();

            if(cities.containsKey(city)){
                //verifica se ja foi adicionado o business na cidade
                if(cities.get(city).containsKey(b_id_search)) {
                    int total = cities.get(city).get(b_id_search) + 1;
                    cities.get(city).replace(b_id_search, total);
                }
                else{//senao cria uma entrada para o business
                    cities.get(city).put(b_id_search,1);
                }
            }
            else{//senao cria uma entrada para essa cidade
                cities.put(city,new HashMap<String,Integer>());
                cities.get(city).put(b_id_search,1);
            }
        });

        Map<String,List<String>> results = new HashMap<>();

        //par cada cidade ordena os negocios
        // , pelo numero total de reviews feito em cada um, de forma descendente
        cities.forEach((k,v) -> {
            List<String> sortedBusinesses = v.entrySet().stream()
                    .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder()))
                    .map(Map.Entry::getKey).collect(Collectors.toList());
            //pega no maximo apenas os top 3 negocios mais famosos
            if (sortedBusinesses.size() >= 3){
                results.put(k,sortedBusinesses.subList(0,3));
            }
            else results.put(k,sortedBusinesses);

        });

        return results;
    }

    //Determinar para cada estado, cidade a cidade, a média de classificação de cada
    //negócio.
    public StateBusiness query10(){
        //hash de estados em que para cada estado tera uma hash das cidades do estado,
        //que, por sua vez terao um hash dos negocios e respetiva media
        StateBusiness states = new StateBusiness();

        Map<String,Business> businesses = getBusinesses();

        businesses.forEach((k,v) -> {
            String state = v.getState();
            String city = v.getCity();
            String b_id = v.getId();
            states.addBusiness(state,city,b_id);
        });

        //percorre as reviews e vai dando update nos scores totais do business
        //correspondente
        Map<String,Review> reviews = getReviews();
        reviews.forEach((k,v)->{
            String b_id = v.getBusiness_id();
            String state = businesses.get(b_id).getState();
            String city = businesses.get(b_id).getCity();
            float score = v.getStars();
            states.updateBusinessScore(state,city,b_id,score);
        });

        return states;

    }



    //metodo de teste
    public void testeReviews(){
        reviews.getReviews().forEach((k,v)-> System.out.println(v.toString()));
    }


}
