#ifndef GOODREADS_HPP
#define GOODREADS_HPP

#include <vector>
#include "Users.hpp"
#include "Reviews.hpp"
#include "Authors.hpp"
#include "Books.hpp"

class GoodReads {

public:

    GoodReads(std::string path);
    void get_command(std::string command);

private:

    users_data users;
    authors_data authors;
    books_data books;
    reviews_data reviews;
};

#endif