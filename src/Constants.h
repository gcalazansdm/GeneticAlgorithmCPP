//
// Created by root on 16/09/2019.
//

#ifndef UNTITLED_CONSTANTS_H
#define UNTITLED_CONSTANTS_H

#include <cstdio>
#include <string>

enum SelectionType{
    SELECTION_TYPE_ROULETTE,
    SELECTION_TYPE_TOURNAMENT,
    SELECTION_TYPE_STOCHASTIC
};
enum CrossoverType{
    CROSSOVER_TYPE_ONE_CUT,
    CROSSOVER_TYPE_TWO_CUT
};

class Constants {
private:
    size_t numOfGenes;
    size_t population;
    size_t numElems;
    float mutationRate;
    CrossoverType crossoverType;
    SelectionType selectionType;
    int numEpochsNotChanging;
    std::string cities;
public:
    Constants(size_t numOfGenes_,size_t population_,size_t numElems_,float mutationRate_,
            CrossoverType crossoverType_,SelectionType selectionType_,int numEpochsNotChanging_,const std::string& cities_):numOfGenes(numOfGenes_),
            population(population_),numElems(numElems_),mutationRate(mutationRate_),crossoverType(crossoverType_),
            selectionType(selectionType_),numEpochsNotChanging(numEpochsNotChanging_),cities(cities_){}
    size_t getGenes() const {
        return numOfGenes;
    }
    std::string getCities() const {
        return cities;
    }
    int getPopulation() const {
        return population;
    }
    int getNumElems() const {
        return numElems;
    }
    float getMutation() const {
        return mutationRate;
    }
    CrossoverType getCrossoverType() const {
        return crossoverType;
    }
    SelectionType getSelectionType() const {
        return selectionType;
    }
    int getNumEpochsNotChanging() const {
        return numEpochsNotChanging;
    }
};
namespace ConstMethods{
    void initConstants(const std::string& constants);

    const Constants* getConstants();

    void terminateConstants();
}
#endif //UNTITLED_CONSTANTS_H
