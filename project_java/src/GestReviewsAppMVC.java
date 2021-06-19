import controller.GestReviews;
import model.Model;

import java.io.IOException;
import java.util.Scanner;

/**
 * APP
 */
public class GestReviewsAppMVC {
    /**
     * Programa principal
     * @param args
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public static void main(String[] args) throws IOException, ClassNotFoundException {

        GestReviews execute = new GestReviews();
        execute.run();
    }
}
