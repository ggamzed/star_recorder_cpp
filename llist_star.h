#ifndef LLIST_STAR_H
#define LLIST_STAR_H

#include <string>
#include "star_data.h"

class llist_star
{
    private:
        star_data* head;
        std::string file_name;
        int read_file();
        int write_file();
        void delete_all_records();
    public:
        llist_star(); // default constructor (zero-argument constructor)
        llist_star(std::string); // custom constructor (used to initialize data members with the values provided by the user.)
        ~llist_star();  // destructor
        int add_data(std::string, std::string, double, double); // name color mass lifetime
        int print_data(std::string);
        int modify_data(std::string, std::string, double, double);
        void print_all_datas();
        int delete_data(std::string);
        void reverse_datas();
};
#endif