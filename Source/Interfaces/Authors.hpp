#ifndef AUTHORS_HPP
#define AUTHORS_HPP

#include <string>
#include <vector>
#include "Date.hpp"
#include "Books.hpp"

#define AUTHOR_FILE "/authors.csv"
#define COLUMN_SEPARATOR ','
#define MULTI_SEPARATOR '$'
#define DATE_SEPARATOR ' '

class Authors;
typedef std::vector<Authors> authors_data;

class Authors {

public:

    Authors();

    Authors(int author_id, std::string author_name, std::string author_gender,
            Date author_register_date, std::string author_birth_place,
            int author_birth_year, std::vector<std::string> author_genres,
            std::vector<Books *> author_books);

    authors_data read_authors(std::string path, books_data &all_books);
    Authors *author_reference(int author_id, authors_data &all_authors);
    void show_author_info(int author_id, authors_data &all_authors);
    std::string getName();

private:

    int id;
    std::string name;
    std::string gender;
    Date register_date;
    int birth_year;
    std::string birth_place;
    std::vector<std::string> genres;
    std::vector<Books *> books;

    std::vector<std::string> get_genres(std::string genres);
    void show_genres(std::vector<std::string> author_genres);
};

bool sort_author_genre_by_name(std::string one,std::string two);

#endif