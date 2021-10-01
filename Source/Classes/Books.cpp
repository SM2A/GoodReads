#include "../Interfaces/Books.hpp"
#include "../Interfaces/Users.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

#define AVERAGE_RATING_PRECISION 2
#define FAVORITE_GENRE_POINT 5

using namespace std;

Books::Books() {}

Books::Books(int book_id, string book_title, string book_genre,
			 int book_author_id, vector<Reviews *> book_reviews) {

	id = book_id;
	title = book_title;
	genre = book_genre;
	author_id = book_author_id;
	reviews = book_reviews;
}

books_data Books::read_book(string path, reviews_data &all_reviews) {

	path += BOOKS_FILE;
	ifstream file(path);
	string input_content;
	books_data books;

	string columns_name;
	getline(file, columns_name);

	while (getline(file, input_content)) {

		stringstream stream(input_content);
		string input_id;
		string input_title;
		string input_genre;
		string input_author_id;
		getline(stream, input_id, COLUMN_SEPARATOR);
		getline(stream, input_title, COLUMN_SEPARATOR);
		getline(stream, input_author_id, COLUMN_SEPARATOR);
		getline(stream, input_genre);
		if (input_genre[input_genre.size() - 1] == '\r')
			input_genre.erase(input_genre.size() - 1);
		books.push_back(Books(stoi(input_id), input_title, input_genre, stoi(input_author_id),
							  Reviews().reviews_references(stoi(input_id), all_reviews)));
	}

	return books;
}

vector<Books *> Books::book_references(int book_author_id, books_data &all_books) {

	vector < Books * > books_addresses;

	for (Books &book : all_books)
		if (book_author_id == book.author_id) books_addresses.push_back(&book);

	return books_addresses;
}

Books *Books::book_reference(int book_id, books_data &all_books) {

	for (Books &book : all_books)
		if (book_id == book.id) return &book;
	return nullptr;
}

Books Books::book_data(int book_id,const books_data &all_books) {

    for (Books book : all_books)
        if (book_id == book.id) return book;
    return Books();
}

void Books::calculate_rating(books_data &books, const users &all_users) {

	for (Books &book : books) {

		int review_count = book.reviews.size();
		double sum = 0;

		for (Reviews *review : book.reviews)
			sum += ((double) review->getRating() * Users().user_data(review->getUserId(), all_users).getCredit());

		double rate = sum / (double) review_count;
		if (review_count == 0) rate = 0;
		book.rating = rate;
	}
}

void Books::show_book_info(vector<Books *> books) {

	cout << "Books:" << endl;

	for (Books *book : books)
		cout << "id: " << book->id << ' ' << "Title: " << book->title << endl;
}

void Books::show_book_info(vector<Books *> books, string genre_pick, authors_data &authors) {

    sort(books.begin(),books.end(),sort_books_by_name);
    sort_title_id(books);

	for (Books *book : books) {
		if (book->genre == genre_pick) {
			cout << "id: " << book->id << endl;
			cout << "Title: " << book->title << endl;
			cout << "Genre: " << book->genre << endl;
			cout << "Author: " << Authors().author_reference(book->author_id, authors)->getName() << endl;
			cout << "***" << endl;
		}
	}
	for (Books *book : books) {
		if (book->genre != genre_pick) {
			cout << "id: " << book->id << endl;
			cout << "Title: " << book->title << endl;
			cout << "Genre: " << book->genre << endl;
			cout << "Author: " << Authors().author_reference(book->author_id, authors)->getName() << endl;
			cout << "***" << endl;
		}
	}
}

void Books::calculate_average_rating(books_data &books) {

	for (Books &book : books) {
		int rating_sum = 0;
		int rating_count = 0;
		for (Reviews *review : book.reviews) {
			rating_count++;
			rating_sum += review->getRating();
		}
		double average_rate = (double) rating_sum / (double) rating_count;
		if (rating_count == 0) average_rate = 0;
		book.average_rating = average_rate;
	}
}

void Books::show_best_book(books_data books, authors_data &authors) {

	sort(books.begin(),books.end(),sort_by_average_rating);
	Books book = books[books.size() - 1];

	cout << "id: " << book.id << endl;
	cout << "Title: " << book.title << endl;
	cout << "Genre: " << book.genre << endl;
	cout << "Author: " << Authors().author_reference(book.author_id, authors)->getName() << endl;
	cout << "Average Rating: " << fixed << setprecision(AVERAGE_RATING_PRECISION) << book.average_rating << endl;
}

Books Books::recommend_book_first_approach(const books_data &books, vector <string> genres) {

	books_data all_books = books;
	for (Books &book : all_books) {
		for (string genre : genres) {
			if (book.genre == genre) {
				book.rating += FAVORITE_GENRE_POINT;
				break;
			}
		}
	}
	sort(all_books.begin(),all_books.end(),sort_by_rating);

	return all_books[all_books.size()-1];
}

void Books::show_book_info(Books book, authors_d &authors) {

	cout << "id: " << book.id << endl;
	cout << "Title: " << book.title << endl;
	cout << "Genre: " << book.genre << endl;
	cout << "Author: " << Authors().author_reference(book.author_id, authors)->getName() << endl;
}

vector<Reviews *> Books::getReviews() { return reviews; }

vector<int> Books::recommend_book_second_approach(vector<Books*> books) {

    sort(books.begin(),books.end(),sort_by_rating_ptr);
    vector<int> recommended;

    if(books.size()==1){
        recommended.push_back(books[0]->id);
    } else if(books.size()==2){
        recommended.push_back(books[0]->id);
        recommended.push_back(books[1]->id);
    } else if(books.size()>=3){
        recommended.push_back(books[books.size()-1]->id);
        recommended.push_back(books[books.size()-2]->id);
        recommended.push_back(books[books.size()-3]->id);
    }
    return recommended;
}

double Books::getRating() {return rating;}

double Books::getAverageRating() {return average_rating;}

string Books::getTitle(){return title;}

int Books::getId() {return id;}

bool sort_by_rating(Books book1,Books book2){

    return book2.getRating()>book1.getRating();
}

bool sort_by_rating_ptr(Books* book1,Books* book2){

    return book2->getRating()>book1->getRating();
}

bool sort_by_average_rating(Books book1,Books book2){

    return book2.getAverageRating()>book1.getAverageRating();
}

bool sort_books_by_name(Books* book1,Books* book2){

    return book2->getTitle()>book1->getTitle();
}

void Books::sort_title_id(vector<Books*>& books){

    int begin =0 ;
    int end = 0;

    for (int index = 0; index <books.size() ; ++index) {

        if (books[begin]->title==books[end]->title){
            end++;
            if (index!=(books.size()-1)) continue;
        }
        sort(books.begin()+begin,books.begin()+end,sort_book_by_id);
        begin=end;
        end++;
    }
}

bool sort_book_by_id(Books* book1,Books* book2){

    return book2->getId()>book1->getId();
}