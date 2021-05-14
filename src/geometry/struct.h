#pragma once

#include <string>
#include <vector>

struct object {
    int id;
    std::string name;
    std::vector<double> points;
    double perimetr;
    double square;
    std::vector<object*> collision;
};
