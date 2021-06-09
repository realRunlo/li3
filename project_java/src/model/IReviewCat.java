package model;

import java.util.Map;

public interface IReviewCat {
    void addReview(Review rev);
    Review getReview(String review_id);
    Map<String,Review> getReviews();
    String toString();
}
