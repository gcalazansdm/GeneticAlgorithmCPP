//
// Created by root on 15/09/2019.
//

#ifndef UNTITLED_CHROMOSOME_H
#define UNTITLED_CHROMOSOME_H

#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>

class Chromosome {
private:
    std::vector<char> genes;
    float fitness;
public:
    Chromosome(){
        this->randomGen();
        this->calculateFitness();
    }
    Chromosome(const Chromosome& ref){
        this->fitness = (ref.fitness);
        this->genes = ref.genes;
    }
    float getFitness(){
        return this->fitness;
    }

    const std::string getGenes()const {
        char path[20];
        std::string rValue = "";
        if(this->genes.size() > 0){
            for (int i = 0; i < this->genes.size(); ++i) {
                sprintf(path,"%d -> ",genes[i]+1);
                rValue += path;
            }
            rValue.pop_back();
            rValue.pop_back();
            rValue.pop_back();
            rValue.pop_back();
        }
        return rValue;
    }

    void mutation();

    void calculateFitness();

    void randomGen();

    void fixChromosome();

    std::vector<char> crossover_remove(int posCut);

    std::vector<char> crossover_remove(int iniPosCut,int endPosCut);

    void crossover_add(int iniPosCut,int endPosCut,const std::vector<char>& elems);

    void crossover_add(int posCut,const std::vector<char>& elems);

    Chromosome& operator=(const Chromosome& other) // copy assignment
    {
        this->fitness = (other.fitness);
        this->genes = (other.genes);
        return *this;
    }

    bool operator==(const Chromosome& ref){
        bool isEquals = this->genes.size() == ref.genes.size();
        for(int i = 0 ; i < this->genes.size() && isEquals; i++ ){
            isEquals &= this->genes[i] == ref.genes[i];
        }
        return isEquals;
    }
    bool operator!=(const Chromosome& ref){ return !(*this == ref); }

    bool operator< (const Chromosome& ref){ return this->fitness > ref.fitness; }
    bool operator> (const Chromosome& ref){ return this->fitness < ref.fitness; }

    bool operator<=(const Chromosome& ref){ return this->fitness >= ref.fitness; }
    bool operator>=(const Chromosome& ref){ return this->fitness <= ref.fitness; }

};


#endif //UNTITLED_CHROMOSOME_H
