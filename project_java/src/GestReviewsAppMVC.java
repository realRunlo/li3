import model.Model;

import java.io.IOException;


public class GestReviewsAppMVC {

    public static void main(String[] args) throws IOException {

/*
NÂO sei o que é mas estava na outra class que apagieo
    public public static void main(String[] args) {
        Irevie model = new ReMa();
        IDataLoader l = new StreamLoader();
        boolean load = loader.load(model);

        if(! loadeed) {out.printly("Error")}

        IReviewManView v = new ReviewManView(); }
    IreviewManControl control = new;
        control.setModel(model);
        control.setView(view);

        control.start();
        System.exit(0);

*/
        Model model = new Model();

        model.load("src/input_files/users_full.csv",
                "src/input_files/reviews_1M.csv",
                "src/input_files/business_full.csv");

        /*
        ReviewCat revs = new ReviewCat();
        revs.loadFromFile("src/input_files/reviews_1M.csv");
        //Review rev = revs.getReview("vEptHcIE9GqBES5fAR6AHw");
        revs.print();*/
        //System.out.println(rev.getBusiness_id());

/*
        UserCat users = new UserCat();
        users.loadFromFile("src/input_files/users_full.csv");
        users.print();*/

    }
}
