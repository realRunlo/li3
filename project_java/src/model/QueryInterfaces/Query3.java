package model.QueryInterfaces;

import model.QueryClasses.ReviewedPerMonth;

import java.util.ArrayList;

public interface Query3 {
    public ArrayList<ReviewedPerMonth> query3(String user_id);
}
