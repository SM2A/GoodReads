#include "../Interfaces/Users.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Users::Users() {}

Users::Users(int user_id, string user_name, string place_of_birth, Date date_of_register,
             vector<Authors *> user_favorite_authors, vector <string> user_favorite_genre,
             vector <vector<Books *>> user_shelves, vector<Reviews *> user_reviews, double user_credit) {

    id = user_id;
    name = user_name;
    birth_place = place_of_birth;
    register_date = date_of_register;
    favorite_authors = user_favorite_authors;
    favorite_genre = user_favorite_genre;
    shelves = user_shelves;
    reviews = user_reviews;
    credit = user_credit;
}

users_data Users::read_users(string path, authors_data &all_authors, books_data &all_books, 
                                                                reviews_data &all_reviews) {

    path += USERS_FILE;
    ifstream file(path);
    string input_content;
    users_data users;

    string columns_name;
    getline(file, columns_name);

    while (getline(file, input_content)) {

        stringstream stream(input_content);
        string input_id;
        string input_name;
        string input_birth_place;
        string input_register_date;
        string input_favorite_author;
        string input_favorite_genres;
        string input_shelf;

        getline(stream, input_id, COLUMN_SEPARATOR);
        getline(stream, input_name, COLUMN_SEPARATOR);
        getline(stream, input_birth_place, COLUMN_SEPARATOR);

        getline(stream, input_register_date, COLUMN_SEPARATOR);
        stringstream date_stream(input_register_date);
        string day, month, year;
        getline(date_stream, month, DATE_SEPARATOR);
        getline(date_stream, day, DATE_SEPARATOR);
        getline(date_stream, year, DATE_SEPARATOR);

        getline(stream, input_favorite_author, COLUMN_SEPARATOR);
        vector < Authors * > user_favorite_authors = find_favorite_authors(input_favorite_author, all_authors);
        getline(stream, input_favorite_genres, COLUMN_SEPARATOR);
        vector <string> all_genres = get_genres(input_favorite_genres);

        vector <vector<Books *>> books_on_shelf(SHELF_COUNT);
        getline(stream, input_shelf, COLUMN_SEPARATOR);
        books_on_shelf[want_to_read] = find_shelf_books(input_shelf, all_books);
        getline(stream, input_shelf, COLUMN_SEPARATOR);
        books_on_shelf[currently_reading] = find_shelf_books(input_shelf, all_books);
        getline(stream, input_shelf);
        books_on_shelf[read] = find_shelf_books(input_shelf, all_books);

        double user_credit = calculate_credit(stoi(input_id), all_reviews);

        users.push_back(Users(stoi(input_id), input_name, input_birth_place,
                              Date(month, stoi(day), stoi(year)), user_favorite_authors, all_genres,
                              books_on_shelf, Reviews().user_reviews(stoi(input_id), all_reviews), user_credit));
    }

    return users;
}

vector <string> Users::get_genres(string genres) {

    vector <string> all_genres;
    stringstream stream(genres);
    string genre;

    while (getline(stream, genre, MULTI_SEPARATOR))
        all_genres.push_back(genre);
        
    return all_genres;
}

vector<Authors *> Users::find_favorite_authors(string authors, authors_data &all_authors) {

    vector < Authors * > user_favorite_authors;
    string author_id;
    stringstream stream(authors);

    while (getline(stream, author_id, MULTI_SEPARATOR))
        user_favorite_authors.push_back(Authors().author_reference(stoi(author_id), all_authors));

    return user_favorite_authors;
}

vector<Books *> Users::find_shelf_books(string shelf_data, books_data &all_books) {

    vector < Books * > shelf_books;
    string book_id;
    stringstream stream(shelf_data);

    while (getline(stream, book_id, MULTI_SEPARATOR))
        shelf_books.push_back(Books().book_reference(stoi(book_id), all_books));

    return shelf_books;
}

void Users::users_ff(string path, users_data &all_users) {

    path+=FOLLOW_EDGES_FILE;
    ifstream file(path);
    string input_content;

    string columns_name;
    getline(file, columns_name);

    while (getline(file,input_content)){

        stringstream stream(input_content);
        string user_id;
        string user_followings;
        string user_followers;

        getline(stream,user_id,COLUMN_SEPARATOR);
        getline(stream,user_followings,COLUMN_SEPARATOR);
        getline(stream,user_followers,COLUMN_SEPARATOR);

        user_pointer(stoi(user_id),all_users)->followings=find_followings(user_followings,all_users);
        user_pointer(stoi(user_id),all_users)->followers=find_followers(user_followers,all_users);
    }
}

users_pointer Users::find_followers(string followers_string,users_data& all_users){

    users_pointer pointer;
    stringstream stream(followers_string);
    string follower_id;

    while (getline(stream,follower_id,MULTI_SEPARATOR))
        if((follower_id!="")&&(follower_id!="\r"))
            pointer.push_back(user_pointer(stoi(follower_id),all_users));

    return pointer;
}

users_pointer Users::find_followings(string followings_string,users_data& all_users){

    users_pointer pointer;
    stringstream stream(followings_string);
    string following_id;

    while (getline(stream,following_id,MULTI_SEPARATOR))
        if((following_id!="")&&(following_id!="\r"))
            pointer.push_back(user_pointer(stoi(following_id),all_users));

    return pointer;
}

double Users::calculate_credit(int user_id, reviews_data &all_reviews) {

    int reviews_count = all_reviews.size();
    int likes_count = 0;
    int users_likes = 0;
    int user_reviews = 0;

    for (Reviews review:all_reviews) {
        likes_count += review.getLikes();
        if (user_id == review.getUserId()) {
            user_reviews++;
            users_likes += review.getLikes();
        }
    }

    double likes_credit = ((double) users_likes / (double) likes_count);
    if (likes_count == 0) likes_credit = 0;
    double reviews_credit = ((double) user_reviews / (double) reviews_count);
    if (reviews_count == 0) reviews_credit = 0;
    double user_credit = (0.5 * (likes_credit + reviews_credit));
    return user_credit;
}

double Users::getCredit() { return credit; }

Users Users::user_data(int user_id, const users_data &all_users) {

    for (Users user : all_users)
        if (user_id == user.id) return user;
    return Users();
}

Users* Users::user_pointer(int user_id,users_data &all_users) {

    for (Users &user : all_users)
        if (user_id == user.id) return &user;
    return nullptr;
}

int Users::shelf_type_num(string shelf_name) {

    if (shelf_name == "read") return read;
    else if (shelf_name == "want_to_read") return want_to_read;
    else if (shelf_name == "currently_reading")return currently_reading;
}

void Users::show_user_shelf(int user_id, string shelf_type,string genre,
                                users_data &all_users,authors_data &all_authors) {

    int shelf_num = shelf_type_num(shelf_type);
    Books().show_book_info(user_data(user_id, all_users).shelves[shelf_num], genre, all_authors);
}

void Users::calculate_user_likes(users_data &users) {

    for (Users &user : users) {
        int likes = 0;
        for (Reviews *review : user.reviews)
            likes += review->getLikes();
        user.review_likes = likes;
    }
}

void Users::show_best_reviewer(users_data &users) {

    sort(users.begin(),users.end(),sort_by_likes);
    Users user = users[users.size() - 1];

    cout << "id: " << user.id << endl;
    cout << "Name: " << user.name << endl;
    cout << "Place of Birth: " << user.birth_place << endl;
    cout << "Member Since: " << user.register_date.getMonth() << ' '
         << user.register_date.getDay() << ' ' << user.register_date.getYear() << endl;
    show_favorite_genres(user.favorite_genre);
    show_favorite_authors(user.favorite_authors);
    cout << "Number of Books in Read Shelf: " << user.shelves[read].size() << endl;
    cout << "Number of Books in Want to Read Shelf: " << user.shelves[want_to_read].size() << endl;
    cout << "Number of Books in Currently Reading Shelf: " << user.shelves[currently_reading].size() << endl;
    cout << "Number of Likes: " << user.review_likes << endl;
}

void Users::show_favorite_genres(vector <string> genres) {

    sort(genres.begin(),genres.end(),sort_genre_by_name);
    cout << "Favorite Genres:";
    for (int index = 0; index < genres.size(); index++) {
        if (index == genres.size() - 1) cout << ' ' << genres[index] << endl;
        else if (index != genres.size() - 1) cout << ' ' << genres[index] << ',';
    }
}

void Users::show_favorite_authors(vector<Authors *> authors) {

    sort(authors.begin(),authors.end(),sort_authors_by_name);
    cout << "Favorite Authors:";
    for (int index = 0; index < authors.size(); index++) {
        if (index == authors.size() - 1) cout << ' ' << authors[index]->getName() << endl;
        else if (index != authors.size() - 1) cout << ' ' << authors[index]->getName() << ',';
    }
}

void Users::recommend_book_first_approach(int user_id, const users_data &all_users,
                                            const books_data &books,authors_data &all_authors) {

    vector <string> genres = user_data(user_id, all_users).favorite_genre;
    Books recommended = Books().recommend_book_first_approach(books, genres);
    Books().show_book_info(recommended, all_authors);
    Reviews().show_reviews(recommended.getReviews());
}

void Users::recommend_book_second_approach(int user_id,users_data &all_users,
                                        const books_data& all_books,authors_data &all_authors) {

    Users* user = user_pointer(user_id,all_users);
    vector<int> recommended_books;

    find_deep_recommend_books(user,recommended_books);
    int book_id=find_most_common(recommended_books);
    Books book = Books().book_data(book_id,all_books);
    book.show_book_info(book,all_authors);
    Reviews().show_reviews(book.getReviews());
}

bool Users::find_deep_recommend_books(Users* user, vector<int>& recommended_books,users_pointer checked_users) {

    if(user->followings.size()==0) return false;
    for(Users* check_user : checked_users) if (user->id==check_user->id) return false;
    checked_users.push_back(user);

    for (int i = 0; i <user->followings.size() ; ++i) {

        bool is_checked = false;
        for (Users* check_user : checked_users)if(check_user->id==user->followings[i]->id) is_checked= true;
        if (is_checked) continue;

        vector<int> books = Books().recommend_book_second_approach(user->followings[i]->shelves[read]);
        for (int book : books)recommended_books.push_back(book);

        if (find_deep_recommend_books(user->followings[i], recommended_books, checked_users))
            return true;

    }

    return false;
}

int Users::find_most_common(vector<int> id) {

    vector<pair<int,int>> id_repeat;

    for (int i = 0; i <id.size() ; ++i) {

        pair<int,int> current_num;
        current_num.first=id[i];
        current_num.second=count(id.begin(),id.end(),id[i]);
        id_repeat.push_back(current_num);
    }

    sort(id_repeat.begin(),id_repeat.end(),sort_by_repeat);
    sort_repeat_id(id_repeat);

    return id_repeat[0].first;
}

void Users::sort_repeat_id(vector<pair<int, int>> &books) {

    int begin =0 ;
    int end = 0;

    for (int index = 0; index <books.size() ; ++index) {

        if (books[begin].second==books[end].second){
            end++;
            if (index!=(books.size()-1)) continue;
        }
        sort(books.begin()+begin,books.begin()+end,sort_by_id);
        begin=end;
        end++;
    }
}

int Users::getReviewLikes() {return review_likes;}

bool sort_by_repeat(pair<int ,int > one, pair<int ,int > two){

    return one.second>two.second;
}

bool sort_by_id(pair<int ,int > one, pair<int ,int > two){

    return one.first<two.first;
}

bool sort_by_likes(Users users1,Users users2){

    return users2.getReviewLikes() > users1.getReviewLikes();
}

bool sort_genre_by_name(std::string one,std::string two){

    return two>one;
}

bool sort_authors_by_name(Authors* author1,Authors* author2){

    return author2->getName()>author1->getName();
}