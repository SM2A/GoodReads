#ifndef USERS_HPP
#define USERS_HPP

#include <string>
#include <vector>
#include "Date.hpp"
#include "Authors.hpp"
#include "Reviews.hpp"
#include "Books.hpp"

#define SHELF_COUNT 3
#define USERS_FILE "/users.csv"
#define FOLLOW_EDGES_FILE "/follow_edges.csv"
#define COLUMN_SEPARATOR ','
#define MULTI_SEPARATOR '$'
#define DATE_SEPARATOR ' '

class Users;
enum shelf {want_to_read, currently_reading, read};
typedef std::vector<Users> users_data;
typedef std::vector<Users*> users_pointer;

class Users {

public:

    Users();

    Users(int user_id, std::string user_name, std::string place_of_birth,
          Date date_of_register, std::vector<Authors *> user_favorite_authors,
          std::vector<std::string> user_favorite_genre,
          std::vector<std::vector<Books *>> user_shelves, std::vector<Reviews *> user_reviews, double user_credit);

    users_data read_users(std::string path, authors_data &all_authors, 
                            books_data &all_books, reviews_data &all_reviews);

    void users_ff(std::string path, users_data &all_users);
    Users user_data(int user_id, const users_data &all_users);
    
    void show_user_shelf(int user_id, std::string shelf_type, std::string genre_pick,
                            users_data &all_users,authors_data &all_authors);

    void recommend_book_first_approach(int user_id, const users_data &all_users, 
                                        const books_data &books,authors_data &all_authors);

    void recommend_book_second_approach(int user_id, users_data &all_users,
                                    const books_data& all_books,authors_data &all_authors);

    void show_best_reviewer(users_data &users);
    void calculate_user_likes(users_data &users);
    int getReviewLikes();
    double getCredit();

private:

    int id;
    std::string name;
    std::string birth_place;
    Date register_date;
    std::vector<Authors *> favorite_authors;
    std::vector<std::string> favorite_genre;
    std::vector<std::vector<Books *>> shelves = std::vector<std::vector<Books *>>(SHELF_COUNT);
    std::vector<Reviews *> reviews;
    users_pointer followings;
    users_pointer followers;
    double credit;
    int review_likes;

    std::vector<std::string> get_genres(std::string genres);
    std::vector<Authors *> find_favorite_authors(std::string authors, authors_data &all_authors);
    std::vector<Books *> find_shelf_books(std::string shelf_data, books_data &all_books);
    double calculate_credit(int user_id, reviews_data &all_reviews);
    int shelf_type_num(std::string shelf_name);
    void show_favorite_genres(std::vector<std::string> genres);
    void show_favorite_authors(std::vector<Authors *> authors);
    Users* user_pointer(int user_id,users_data &all_users);
    users_pointer find_followers(std::string followers_string,users_data& all_users);
    users_pointer find_followings(std::string followers_string,users_data& all_users);
    bool find_deep_recommend_books(Users* user,std::vector<int>& recommended_books,
                                    users_pointer checked_users=users_pointer());
    int find_most_common(std::vector<int> numbers);
    void sort_repeat_id(std::vector<std::pair<int ,int>> &books);
};

bool sort_by_repeat(std::pair<int ,int > one, std::pair<int ,int > two);
bool sort_by_id(std::pair<int ,int > one, std::pair<int ,int > two);
bool sort_genre_by_name(std::string one,std::string two);
bool sort_authors_by_name(Authors* author1,Authors* author2);
bool sort_by_likes(Users users1,Users users2);

#endif