#ifndef REVIEWS_HPP
#define REVIEWS_HPP

#include <vector>
#include "Date.hpp"

#define REVIEW_FILE "/reviews.csv"
#define COLUMN_SEPARATOR ','
#define DATE_SEPARATOR ' '

class Reviews;
typedef std::vector<Reviews> reviews_data;

class Reviews {

public:

    Reviews();

    Reviews(int review_id, int review_book_id, int review_user_id, int review_rating,
            Date review_submit_date, int review_likes);

    reviews_data read_reviews(std::string path);
    std::vector<Reviews *> reviews_references(int review_book_id, reviews_data &all_reviews);
    std::vector<Reviews *> user_reviews(int review_user_id, reviews_data &all_reviews);
    void show_reviews(std::vector<Reviews *> reviews);
    int getUserId();
    int getLikes();
    int getRating();

private:

    int id;
    int book_id;
    int user_id;
    int rating;
    Date submit_date;
    int likes;
};

#endif