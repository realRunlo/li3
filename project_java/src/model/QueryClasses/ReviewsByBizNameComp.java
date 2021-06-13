package model.QueryClasses;

import java.util.Comparator;

public class ReviewsByBizNameComp implements Comparator<ReviewsByBizName> {


    @Override
    public int compare(ReviewsByBizName rb1,ReviewsByBizName rb2){
        if(rb1.getTotal() == rb2.getTotal()){
            return rb1.getName().compareTo(rb2.getName());
        }else{
            return rb2.getTotal() - rb1.getTotal();
        }


    }


}
