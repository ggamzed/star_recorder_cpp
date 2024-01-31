#include <string>

#ifndef STAR_DATA_H
#define STAR_DATA_H

struct star_data {
    std::string name;
    std::string color;
    double life_time;
    double Mass;
    struct star_data* next; 
};
#endif