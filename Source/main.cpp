#include "Interfaces/GoodReads.hpp"
#include <iostream>

#define DATA_ARGUMENTS 1

using namespace std;

int main(int argv, char *argc[]) {

    GoodReads good_reads(argc[DATA_ARGUMENTS]);

    string command;
    while (cin >> command)
        good_reads.get_command(command);

    return 0;
}