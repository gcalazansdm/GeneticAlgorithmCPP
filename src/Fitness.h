//
// Created by root on 15/09/2019.
//

#ifndef UNTITLED_FITNESS_H
#define UNTITLED_FITNESS_H

#include <vector>
#include "City.h"

class Fitness {
private:
    static std::vector<City> allCities;
    Fitness();
public:
    static void parseFile(const char* cityDir);
    static float calculateFitness(const std::vector<char>& values);
};


#endif //UNTITLED_FITNESS_H
