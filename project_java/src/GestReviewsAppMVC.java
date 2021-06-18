import controller.GestReviews;
import model.Model;

import java.io.IOException;
import java.util.Scanner;


public class GestReviewsAppMVC {

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        
        GestReviews execute = new GestReviews();
        execute.run();
    }
}
