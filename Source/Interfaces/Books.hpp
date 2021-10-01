#ifndef BOOKS_HPP
#define BOOKS_HPP

#include <string>
#include <vector>
#include "Reviews.hpp"

#define BOOKS_FILE "/books.csv"
#define COLUMN_SEPARATOR ','
#define DATE_SEPARATOR ' '

class Books;
class Users;
class Authors;
typedef std::vector<Books> books_data;
typedef std::vector<Users> users;
typedef std::vector<Authors> authors_d;

class Books {

public:

    Books();

    Books(int book_id, std::string book_title, std::string book_genre,
          int book_author_id, std::vector<Reviews *> book_reviews);

    books_data read_book(std::string path, reviews_data &all_reviews);
    std::vector<Books *> book_references(int book_author_id, books_data &all_books);
    Books *book_reference(int book_id, books_data &all_books);
    Books book_data(int book_id,const books_data &all_books);
    void calculate_rating(books_data &books, const users &all_users);
    Books recommend_book_first_approach(const books_data &books, std::vector<std::string> genres);
    std::vector<int> recommend_book_second_approach(std::vector<Books*> books);
    void calculate_average_rating(books_data &books);
    void show_book_info(std::vector<Books *> books);
    void show_book_info(std::vector<Books *> books, std::string genre_pick, authors_d &authors);
    void show_book_info(Books book, authors_d &authors);
    void show_best_book(books_data books, authors_d &authors);
    void sort_title_id(std::vector<Books*>& books);
    std::vector<Reviews *> getReviews();
    double getRating();
    double getAverageRating();
    std::string getTitle() ;
    int getId();

private:

    int id;
    std::string title;
    std::string genre;
    int author_id;
    double rating;
    double average_rating;
    std::vector<Reviews *> reviews;
};

bool sort_by_rating(Books book1,Books book2);
bool sort_by_rating_ptr(Books* book1,Books* book2);
bool sort_by_average_rating(Books book1,Books book2);
bool sort_books_by_name(Books* book1,Books* book2);
bool sort_book_by_id(Books* book1,Books* book2);

#endif