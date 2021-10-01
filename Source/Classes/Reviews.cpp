#include "../Interfaces/Reviews.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Reviews::Reviews() {}

Reviews::Reviews(int review_id, int review_book_id, int review_user_id, int review_rating,
                 Date review_submit_date, int review_likes) {

    id = review_id;
    book_id = review_book_id;
    user_id = review_user_id;
    rating = review_rating;
    submit_date = review_submit_date;
    likes = review_likes;

}

reviews_data Reviews::read_reviews(string path) {

    path += REVIEW_FILE;
    ifstream file(path);
    string input_content;
    reviews_data reviews;

    string columns_name;
    getline(file, columns_name);

    while (getline(file, input_content)) {

        stringstream stream(input_content);
        string input_id;
        string input_book_id;
        string input_user_id;
        string input_rating;
        string input_date;
        string input_likes;
        getline(stream, input_id, COLUMN_SEPARATOR);
        getline(stream, input_book_id, COLUMN_SEPARATOR);
        getline(stream, input_user_id, COLUMN_SEPARATOR);
        getline(stream, input_rating, COLUMN_SEPARATOR);

        getline(stream, input_date, COLUMN_SEPARATOR);
        stringstream date_stream(input_date);
        string input_day, input_month, input_year;
        getline(date_stream, input_month, DATE_SEPARATOR);
        getline(date_stream, input_day, DATE_SEPARATOR);
        getline(date_stream, input_year, DATE_SEPARATOR);

        getline(stream, input_likes);

        reviews.push_back(Reviews(stoi(input_id), stoi(input_book_id), stoi(input_user_id), stoi(input_rating),
                                  Date(input_month, stoi(input_day), stoi(input_year)), stoi(input_likes)));
    }

    return reviews;
}

vector<Reviews *> Reviews::reviews_references(int review_book_id, reviews_data &all_reviews) {

    vector < Reviews * > reviews_address;

    for (Reviews &review : all_reviews) {
        if (review_book_id == review.book_id) reviews_address.push_back(&review);
    }

    return reviews_address;
}

int Reviews::getUserId() { return user_id; }

int Reviews::getLikes() { return likes; }

vector<Reviews *> Reviews::user_reviews(int review_user_id, reviews_data &all_reviews) {

    vector < Reviews * > reviews_address;

    for (Reviews &review : all_reviews)
        if (review_user_id == review.user_id) reviews_address.push_back(&review);

    return reviews_address;
}

int Reviews::getRating() { return rating; }

void Reviews::show_reviews(vector<Reviews *> reviews) {

    cout << "Reviews:" << endl;

    for (Reviews *review : reviews) {
        cout << "id: " << review->id << ' ' << "Rating: " << review->rating << ' '
             << "Likes: " << review->likes << ' ' << "Date: " << review->submit_date.getMonth()
             << ' ' << review->submit_date.getDay() << ' ' << review->submit_date.getYear() << endl;
    }
}