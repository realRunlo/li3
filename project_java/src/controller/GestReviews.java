package controller;

import model.Business;
import model.Model;
import model.QueryClasses.NotReviewed;

import java.io.IOException;
import java.util.*;



public class GestReviews {
    private Model data;

    public GestReviews(){
        data = new Model();
    }


    public GestReviews(String userFile, String businessFile, String reviewFile) throws IOException {
        data = new Model(userFile,businessFile,reviewFile);
    }

    public void query1(){
        System.out.println(data.query1().toString());
    }











}