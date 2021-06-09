package model;

import java.time.LocalDateTime;

public interface IReview {
    String getReview_id();
    String getUser_id();
    String getBusiness_id();
    float getStars();
    int getUseful();
    int getFunny() ;
    int getCool();
    LocalDateTime getDate();
    String getTxt();
    String toString();
    Review clone();    
}
