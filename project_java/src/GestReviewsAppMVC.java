import controller.GestReviews;
import model.Model;

import java.io.IOException;
import java.util.Scanner;


public class GestReviewsAppMVC {

    public static void main(String[] args) throws IOException, ClassNotFoundException {
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

        GestReviews execute = new GestReviews();
        execute.run();
    }
}
