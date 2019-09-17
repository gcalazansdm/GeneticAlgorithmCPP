//
// Created by root on 15/09/2019.
//

#include "Fitness.h"
#include <cmath>
#include <cstdio>
#include <cstring>

std::vector<City> Fitness::allCities;
void Fitness::parseFile(const char* cityDir){

    char line[170];
    float x,y;
    int num;
    FILE* f = fopen(cityDir,"r");
    if(f)
    {
        for(fgets(line, sizeof(line), f); strcmp(line,"NODE_COORD_SECTION\n");fgets(line, sizeof(line), f));

        //Lê as NODE_COORD_SECTION
        for(fgets(line, sizeof(line), f); strcmp(line,"EOF\n");fgets(line, sizeof(line), f)){
            sscanf(line,"%d %f %f\n",&num,&x,&y);
            Fitness::allCities.push_back(City(x,y));
        }
        printf("Loaded Cities\n");
    }
}
float equidianDistancie(int x0,int x1,int y0,int y1){
    int x = x0 - x1;
    int y = y0 - y1;

    return std::sqrt(x*x + y*y);
}

float Fitness::calculateFitness(const std::vector<char>& values){
    float distance = 0;
    int pos = values[0];
    City cityA = Fitness::allCities[pos];

    for (int i = 1; i < values.size(); ++i) {
        pos = values[i];
        City& cityB = Fitness::allCities[pos];
        distance += equidianDistancie(cityA.getX(),cityB.getX(),cityA.getY(),cityB.getY());
        cityA = cityB;
    }
    pos = values[0];
    City& cityB = Fitness::allCities[pos];
    distance += equidianDistancie(cityA.getX(),cityB.getX(),cityA.getY(),cityB.getY());
    return 100/float(distance);        
}
