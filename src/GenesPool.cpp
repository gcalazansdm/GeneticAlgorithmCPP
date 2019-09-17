#include "GenesPool.h"
#include "Fitness.h"
#include <cstdlib>
#include <algorithm>
#include <random>


void GenesPool::tryMutate(Chromosome& chromosome){
    auto constants =  ConstMethods::getConstants();
    float mutationRate = constants->getMutation();
    float random;
    random = (float)(rand()%100)/100;
    if(random <= mutationRate){
        chromosome.mutation();
    }
}

void GenesPool::run(){
    auto constants =  ConstMethods::getConstants();
    int numEpochsNotChanging = constants->getNumEpochsNotChanging();
    size_t numElems = constants->getNumElems();
    size_t population = constants->getPopulation();
  
    std::string best_genes;
    float maxValue = 0.0;
    int numInteractionsNotChanging = 0;


    Chromosome childA;
    Chromosome childB;
    int inter = 0;
    while(numInteractionsNotChanging < numEpochsNotChanging){
        std::vector<Chromosome> crossOverCandidates = selectGenes(numElems,this->pool);
        std::vector<Chromosome> newPool;

        size_t pos = this->pool.size();

        for (size_t i = 0; i <pos; ++i) {
            Chromosome& fatherA = crossOverCandidates[i];
            newPool.push_back(fatherA);
            for (size_t j = i+1; j < crossOverCandidates.size(); ++j) {
                Chromosome& fatherB = crossOverCandidates[j];
                newPool.push_back(fatherB);
                performCrossover(childA,childB,fatherA,fatherB);
                newPool.push_back(childA);
                newPool.push_back(childB);
            }
        }
        std::vector<Chromosome> newElems = selectGenes(population,newPool);
        this->pool.swap(newElems);
        float best = this->pool[0].getFitness();
        if(best > maxValue){
            printf("in\n");
            best_genes = this->pool[0].getGenes();
            maxValue = best;
            numInteractionsNotChanging = 0;
        }else{
            numInteractionsNotChanging++;
        }
        printf("%d -> %f %f\n",inter++,best,maxValue);
    }
    printf("Fim -> %s %f",best_genes.c_str(),this->pool[0].getFitness());
}

std::vector<Chromosome> GenesPool::selectGenes(int numElements, std::vector<Chromosome> elems){
    auto constants =  ConstMethods::getConstants();
    SelectionType selectionType = constants->getSelectionType();
    std::sort(elems.begin(), elems.end());
    std::vector<Chromosome> selectedElems;
    switch(selectionType){
        case SELECTION_TYPE_STOCHASTIC:
            for (int i = 0; i < numElements; ++i) {
                selectedElems.push_back(elems[i]);
            }
            break;
        case SELECTION_TYPE_TOURNAMENT:{
            std::vector<Chromosome> candidates;
            size_t divElems = elems.size()/numElements;
            auto rng = std::default_random_engine{};
            std::shuffle(std::begin(elems), std::end(elems), rng);
            int pos;
            for (int i = 0; i < numElements; ++i) {
                for (int j = 0; j < divElems; ++j) {
                    candidates.push_back(elems[i]);
                }
                std::sort(candidates.begin(), candidates.end());
                selectedElems.push_back(candidates[0]);
                candidates.clear();
            }
            break;
        }
        case SELECTION_TYPE_ROULETTE:{
            std::vector<Chromosome> candidates;
            size_t size = elems.size();
            int max = 0;
            for (int i = 0; i < size; ++i) {
                max = elems[i].getFitness();
            }
            int random;

            auto rng = std::default_random_engine{};
            std::shuffle(std::begin(elems), std::end(elems), rng);

            int chance = 0;
            int pos;
            int step = size /float(numElements);
            for (int i = 0; candidates.size() == 0; ++i) {
                i = i % size;
                chance =  elems[i].getFitness()/max;
                random = (float)(rand()%100)/100;
                if(random <= chance){
                    pos = i;
                    for (int j = 0; j < numElements; ++j) {
                        candidates.push_back(elems[pos]);
                        pos = (pos+step)%size;
                    }
                    break;
                }
            }
            selectedElems.swap(candidates);
            break;
        }

    }
    return selectedElems;
}
void GenesPool::performCrossover(Chromosome& childA,Chromosome& childB,const Chromosome& fatherA,const Chromosome& fatherB){
    auto constants =  ConstMethods::getConstants();
    CrossoverType crossoverType = constants->getCrossoverType();
    size_t numOfGenes = constants->getGenes();
    int randomA;
    int randomB;

    switch(crossoverType){
        case CROSSOVER_TYPE_ONE_CUT:
            {
                randomA = rand() % numOfGenes;

                childA = fatherA;
                childB = fatherB;

                const std::vector<char>& genesA = childA.crossover_remove(randomA);
                const std::vector<char>& genesB = childB.crossover_remove(randomA);

                childA.crossover_add(randomA,genesB);
                childB.crossover_add(randomA,genesA);

                childA.fixChromosome();
                childB.fixChromosome();

                tryMutate(childA);
                tryMutate(childB);

                childA.calculateFitness();
                childB.calculateFitness();
            }

            break;
        case CROSSOVER_TYPE_TWO_CUT:
            {
                randomA = (rand() % numOfGenes);
                randomB = (rand() % numOfGenes);
                int randomMax = std::max(randomA,randomB);
                randomB = std::min(randomA,randomB);
                if(randomB == randomMax){
                    if(randomB == 0)
                    {
                        randomMax++;
                    }
                    else{
                        randomB--;
                    }
                }
                childA = fatherA;
                childB = fatherB;

                std::vector<char> genesA = childA.crossover_remove(randomB,randomMax);
                std::vector<char> genesB = childB.crossover_remove(randomB,randomMax);

                childA.crossover_add(randomB,randomMax,genesB);
                childB.crossover_add(randomB,randomMax,genesA);

                childA.fixChromosome();
                childB.fixChromosome();

                tryMutate(childA);
                tryMutate(childB);

                childA.calculateFitness();
                childB.calculateFitness();
            }
            break;
    }
}
