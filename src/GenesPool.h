//
// Created by root on 15/09/2019.
//

#ifndef UNTITLED_GENESPOOL_H
#define UNTITLED_GENESPOOL_H

#include <vector>
#include "Chromosome.h"
#include "Constants.h"

class GenesPool {
private:
    std::vector<Chromosome> pool;
    void tryMutate(Chromosome& chromosome);
    void mutatetoAdd(std::vector<Chromosome>& elems,Chromosome& chromosome);
    std::vector<Chromosome> selectGenes(int numElements, std::vector<Chromosome>& elems );
    void performCrossover(Chromosome& childA,Chromosome& childB,const Chromosome& fatherA,const Chromosome& fatherB);
public:
    GenesPool(){
        auto constants =  ConstMethods::getConstants();
        int population_ = constants->getPopulation();

        for (int i = 0; i < population_; ++i) {
            Chromosome tempChromosome = Chromosome();
            mutatetoAdd(this->pool,tempChromosome);
        }
    }
    void run();

};


#endif //UNTITLED_GENESPOOL_H
