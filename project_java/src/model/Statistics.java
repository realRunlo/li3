package model;

import model.QueryClasses.ReviewedPerMonth;

import java.util.List;

public interface Statistics {
    List<String> getFilesLoaded();

    int getInvalidReviews();

    int getNumberOfBusinesses();

    int getDistinctBusinessesReviewed();

    int getNumberOfUsers();

    int getNumberOfUserReviewers();

    int getUsersNotReviewers();

    int getNonImpactReviews();

    List<ReviewedPerMonth> getReviewsPerMonth();

    String statistics();
}
