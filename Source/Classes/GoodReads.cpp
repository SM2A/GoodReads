#include "../Interfaces/GoodReads.hpp"
#include <iostream>
#include <iomanip>

#define SHOW_AUTHOR_INFO "show_author_info"
#define SHOW_SORTED_SHELF "show_sorted_shelf"
#define BEST_BOOK "best_book"
#define CREDIT "credit"
#define BEST_REVIEWER "best_reviewer"
#define RECOMMEND_FIRST_APPROACH "recommend_first_approach"
#define RECOMMEND_SECOND_APPROACH "recommend_second_approach"
#define USER_CREDIT_PRECISION 6

using namespace std;

GoodReads::GoodReads(string path) {

    reviews = Reviews().read_reviews(path);
    books = Books().read_book(path, reviews);
    authors = Authors().read_authors(path, books);
    users = Users().read_users(path, authors, books, reviews);
    Books().calculate_rating(books, users);
    Books().calculate_average_rating(books);
    Users().calculate_user_likes(users);
    Users().users_ff(path,users);
}

void GoodReads::get_command(string command) {

    if (command == SHOW_AUTHOR_INFO) {
        int id;
        cin >> id;
        Authors().show_author_info(id, authors);

    } else if (command == SHOW_SORTED_SHELF) {
        int id;
        string shelf_type, genre;
        cin >> id >> shelf_type;
        getline(cin,genre);
        genre.erase(genre.begin());
        Users().show_user_shelf(id, shelf_type, genre, users, authors);

    } else if (command == CREDIT) {
        int id;
        cin >> id;
        cout << fixed << setprecision(USER_CREDIT_PRECISION) << Users().user_data(id, users).getCredit() << endl;

    } else if (command == BEST_BOOK) {
        Books().show_best_book(books, authors);

    } else if (command == BEST_REVIEWER) {
        Users().show_best_reviewer(users);

    } else if (command == RECOMMEND_FIRST_APPROACH) {
        int id;
        cin >> id;
        Users().recommend_book_first_approach(id, users, books, authors);

    } else if(command==RECOMMEND_SECOND_APPROACH){
        int id;
        cin>>id;
        Users().recommend_book_second_approach(id,users,books,authors);
    }
}