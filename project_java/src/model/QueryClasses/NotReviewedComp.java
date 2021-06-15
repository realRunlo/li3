package model.QueryClasses;

import model.Business;

import java.util.Comparator;

public class NotReviewedComp implements Comparator<Business> {

    @Override
    public int compare(Business b1, Business b2){

        return b1.getName().compareTo(b2.getName());
    }
}
