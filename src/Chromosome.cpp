#include <cstdlib>
#include "Chromosome.h"
#include "Fitness.h"
#include "Constants.h"
#include <vector>
#include <cassert>

#define EXISTS 1
#define DOES_NOT_EXISTS 0


void Chromosome::calculateFitness(){
    this->fitness = Fitness::calculateFitness(this->genes);
}

void Chromosome::mutation(){
    auto constants =  ConstMethods::getConstants();
    size_t numOfGenes = constants->getGenes();
    int posA = rand()%numOfGenes;
    int posB = rand()%numOfGenes;
    if(posB != posA){
        char tempGen = this->genes[posB];
        this->genes[posB] = this->genes[posA];
        this->genes[posA] = tempGen;
    }
    this->calculateFitness();
}

void Chromosome::randomGen(){
    auto constants =  ConstMethods::getConstants();
    size_t numOfGenes = constants->getGenes();
    char* possibleNumbers = new char[numOfGenes];
    memset( possibleNumbers, DOES_NOT_EXISTS, numOfGenes*sizeof(char) );
    int pos;
    for (int i = 0; i < numOfGenes; ++i) {
        pos = rand() % numOfGenes;
        while(possibleNumbers[pos] == EXISTS){
            pos = (pos+1)%numOfGenes;
        }
        this->genes.push_back(pos);
        possibleNumbers[pos] = EXISTS;
    }
    delete[] possibleNumbers;
}

std::vector<char> Chromosome::crossover_remove(int posCut){
    return this->crossover_remove(posCut,this->genes.size());
}
std::vector<char> Chromosome::crossover_remove(int iniPosCut,int endPosCut){
    assert(iniPosCut >= 0 && endPosCut > iniPosCut);
    //Pega o sub-Vector
    std::vector<char>::const_iterator begin = this->genes.begin() + iniPosCut;
    std::vector<char>::const_iterator end = this->genes.begin() + endPosCut;
    std::vector<char> rVector(begin, end);

    //Copia o sub-Vector
    std::vector<char> rValue = rVector;
    return rValue;
}

void Chromosome::crossover_add(int iniPosCut,int endPosCut,const std::vector<char>& elems){
    auto end = this->genes.begin()+(endPosCut);
    this->genes.erase(this->genes.begin()+iniPosCut,end);
    this->genes.insert(this->genes.begin()+iniPosCut, elems.begin(), elems.end());
}

void Chromosome::crossover_add(int posCut,const std::vector<char>& elems){
    this->crossover_add(posCut,this->genes.size(),elems);
}

void Chromosome::fixChromosome(void){
    auto constants =  ConstMethods::getConstants();
    size_t numOfGenes = constants->getGenes();
    assert(numOfGenes > 0 && numOfGenes < 10000);
    int numOfDuplicates = 0;

    char possibleNumbers[numOfGenes];

    for (int k = 0; k < numOfGenes; ++k) {
        possibleNumbers[k] = DOES_NOT_EXISTS;
    }

    int posDuplicate[numOfGenes];
    int pos;

    for (int i = 0; i < numOfGenes; ++i) {
        pos = this->genes[i];
        if(possibleNumbers[pos] == DOES_NOT_EXISTS){
            possibleNumbers[pos] = EXISTS;
        }
        else{
            posDuplicate[numOfDuplicates] = i;
            numOfDuplicates++;
        }
    }
    for (int j = 0; j < numOfGenes && numOfDuplicates > 0; ++j) {
        if(possibleNumbers[j] == DOES_NOT_EXISTS){
            numOfDuplicates--;
            pos = posDuplicate[numOfDuplicates];
            this->genes[pos] = j;
        }
    }
}

