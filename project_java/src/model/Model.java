package model;

import model.QueryClasses.NotReviewed;
import model.QueryClasses.ReviewedPerMonth;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

public class Model {

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
                    if(this.users.containsId(rev.getReview_id()) && this.businesses.containsId(rev.getBusiness_id())){ //check if users and businesses exist
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



    //metodo de teste
    public void testeReviews(){
        reviews.getReviews().forEach((k,v)-> System.out.println(v.toString()));
    }


}
