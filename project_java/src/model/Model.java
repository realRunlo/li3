package model;

import java.io.IOException;

public class Model {

    private UserCat users;
    private ReviewCat reviews;
    private BusinessCat businesses;


    public Model(String users_file, String reviews_file, String businesses_file) throws IOException {

        //users = new UserCat();
       // users.loadFromFile(users_file);

        reviews = new ReviewCat();
        reviews.loadFromFile(reviews_file);

        businesses = new BusinessCat();
        businesses.loadFromFile(businesses_file);
    }

    public ReviewCat getReviews(){return reviews;}

}
