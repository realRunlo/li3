package model.QueryClasses;

import java.util.Comparator;

public class TopReviewsAuxComp implements Comparator<TopReviewsAux> {


    @Override
    public int compare(TopReviewsAux rb1,TopReviewsAux rb2){
        if(rb1.getTotal() == rb2.getTotal()){
            return rb1.getBus().compareTo(rb2.getBus());
        }else{
            return rb2.getTotal() - rb1.getTotal();
        }


    }
}
