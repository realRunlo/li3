package model.QueryInterfaces;

import model.QueryClasses.ReviewedPerMonth;
import model.QueryClasses.UserReviewsByMonth;

import java.util.ArrayList;

public interface Query3 {
    public ArrayList<UserReviewsByMonth> query3(String user_id);
}
