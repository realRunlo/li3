package model;

import model.QueryClasses.NotReviewed;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.format.DateTimeFormatter;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.stream.Stream;

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


    public NotReviewed query1(){
        NotReviewed results = new NotReviewed();
        Map<String,Business> businesses = this.businesses.getBusinesses();
        Map<String,Review> reviewsSearch = this.reviews.getReviews();

        reviewsSearch.forEach((k,v) -> {
            businesses.remove(v.getBusiness_id());
        });

        businesses.forEach((k,v) -> results.addBusiness(v));
        return results;
    }




    //metodo de teste
    public void testeReviews(){
        reviews.getReviews().forEach((k,v)-> System.out.println(v.toString()));
    }


}
