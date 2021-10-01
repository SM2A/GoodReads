#include "../Interfaces/Authors.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Authors::Authors() {}

Authors::Authors(int author_id, string author_name, string author_gender, Date author_register_date,
                 string author_birth_place, int author_birth_year, vector <string> author_genres,
                 vector<Books *> author_books) {

    id = author_id;
    name = author_name;
    gender = author_gender;
    register_date = author_register_date;
    birth_place = author_birth_place;
    birth_year = author_birth_year;
    genres = author_genres;
    books = author_books;
}

authors_data Authors::read_authors(string path, books_data &all_books) {

    path += AUTHOR_FILE;
    ifstream file(path);
    string input_content;
    authors_data authors;

    string columns_name;
    getline(file, columns_name);

    while (getline(file, input_content)) {

        stringstream stream(input_content);
        string input_id;
        string input_name;
        string input_gender;
        string input_register_date;
        string input_birth_year;
        string input_birth_place;
        string input_genres;
        getline(stream, input_id, COLUMN_SEPARATOR);
        getline(stream, input_name, COLUMN_SEPARATOR);
        getline(stream, input_gender, COLUMN_SEPARATOR);

        getline(stream, input_register_date, COLUMN_SEPARATOR);
        stringstream date_stream(input_register_date);
        string day, month, year;
        getline(date_stream, month, DATE_SEPARATOR);
        getline(date_stream, day, DATE_SEPARATOR);
        getline(date_stream, year, DATE_SEPARATOR);

        getline(stream, input_birth_year, COLUMN_SEPARATOR);
        getline(stream, input_birth_place, COLUMN_SEPARATOR);
        getline(stream, input_genres);
        vector <string> all_genres = get_genres(input_genres);

        authors.push_back(Authors(stoi(input_id), input_name, input_gender, Date(month, stoi(day), 
                        stoi(year)),input_birth_place,stoi(input_birth_year), all_genres, 
                        Books().book_references(stoi(input_id), all_books)));
    }

    return authors;
}

vector <string> Authors::get_genres(string genres) {

    vector <string> all_genres;
    stringstream stream(genres);
    string genre;

    while (getline(stream, genre, MULTI_SEPARATOR)) {

        if (genre[genre.size() - 1] == '\r')
            genre.erase(genre.size() - 1);
        all_genres.push_back(genre);
    }

    return all_genres;
}

Authors *Authors::author_reference(int author_id, authors_data &all_authors) {

    for (Authors &author : all_authors)
        if (author_id == author.id) return &author;
    return nullptr;
}

void Authors::show_author_info(int author_id, authors_data &all_authors) {

    Authors *author = Authors().author_reference(author_id, all_authors);

    cout << "id: " << author->id << endl;
    cout << "Name: " << author->name << endl;
    cout << "Year of Birth: " << author->birth_year << endl;
    cout << "Place of Birth: " << author->birth_place << endl;
    cout << "Member Since: " << author->register_date.getMonth() << ' ' <<
         author->register_date.getDay() << ' ' << author->register_date.getYear() << endl;
    show_genres(author->genres);
    Books().show_book_info(author->books);
}

void Authors::show_genres(vector <string> author_genres) {

    sort(author_genres.begin(),author_genres.end(),sort_author_genre_by_name);
    cout << "Genres: ";
    for (int index = 0; index < author_genres.size(); index++) {
        if (index == author_genres.size() - 1) cout << author_genres[index] << endl;
        else if (index != author_genres.size() - 1) cout << author_genres[index] << ',' << ' ';
    }
}

string Authors::getName() { return name; }

bool sort_author_genre_by_name(std::string one,std::string two){

    return two>one;
}