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
template <class T>
bool vectorSafeAdd(std::vector<T>& vector, const T& elem){
    bool rValue = std::find(vector.begin(), vector.end(), elem) == vector.end();
    if(rValue)
    {
        vector.push_back(elem);
    }
    return rValue;
}
void GenesPool::mutatetoAdd(std::vector<Chromosome>& vector,Chromosome& elem)
{
    while(std::find(vector.begin(), vector.end(), elem) != vector.end()){
        elem.mutation();
    }
    vector.push_back(elem);
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
      //  printf("%d\n",this->pool.size());
        std::vector<Chromosome> crossOverCandidates = selectGenes(numElems,this->pool);
      //  printf("%d\n",crossOverCandidates.size());
        std::vector<Chromosome> newPool = this->pool;

        size_t size = crossOverCandidates.size();

        for (size_t i = 0; i < size; ++i) {
            Chromosome& fatherA = crossOverCandidates[i];
            for (size_t j = i+1; j < size; ++j) {
                Chromosome& fatherB = crossOverCandidates[j];
                performCrossover(childA,childB,fatherA,fatherB);
                mutatetoAdd(newPool,childA);
                mutatetoAdd(newPool,childB);
            }
        }
        std::vector<Chromosome> newElems = selectGenes(population,newPool);
      //  printf("%d\n",newElems.size());
        this->pool.swap(newElems);
        float best = this->pool[0].getFitness();
        if(best > maxValue){
            best_genes = this->pool[0].getGenes();
            maxValue = best;
            numInteractionsNotChanging = 0;
        }else{
            numInteractionsNotChanging++;
        }
        printf("%d -> %f %f | %d\n",inter++,best,maxValue,numEpochsNotChanging - numInteractionsNotChanging);
    }
    printf("Fim -> %s %f",best_genes.c_str(),100/this->pool[0].getFitness());
}

std::vector<Chromosome> GenesPool::selectGenes(int numElements,std::vector<Chromosome>& elems){
    auto constants =  ConstMethods::getConstants();
    SelectionType selectionType = constants->getSelectionType();
    std::sort(elems.begin(), elems.end());
    std::vector<Chromosome> selectedElems;
    switch(selectionType){
        case SELECTION_TYPE_ROULETTE:{
            std::vector<Chromosome> candidates;
            std::vector<Chromosome> addedElements;
            size_t size = elems.size();
            float max = 0;
            float random;
            float chance = 0;
            int addedValues = 0;
            for (int i = 0; i < size; ++i) {
                max += elems[i].getFitness();
            }

            auto rng = std::default_random_engine{};
            std::shuffle(std::begin(elems), std::end(elems), rng);

            for (int i = 0; addedValues < numElements; ++i) {
                i = i % size;

                chance =  elems[i].getFitness()/max;
                random = (float)(rand()%100)/100;
                if(random <= chance && vectorSafeAdd(candidates,elems[i])){
                        max -=  elems[i].getFitness();
                        addedValues++;
                }
            }
            selectedElems.swap(candidates);
            break;
        }

        case SELECTION_TYPE_TOURNAMENT:{
            std::vector<Chromosome> candidates;
            int numElems = elems.size();
            size_t divElems = std::max(int(numElems/(numElements)),2);
            auto rng = std::default_random_engine{};
            std::shuffle(std::begin(elems), std::end(elems), rng);
            int pos = 0;
            for (int i = 0; i < numElements; ++i) {
                for (int j = 0; j < divElems && pos < numElems; ++j) {
                    candidates.push_back(elems[pos]);
                    pos++;
                }
                if(!candidates.empty())
                {
                    std::sort(candidates.begin(), candidates.end());
                    selectedElems.push_back(candidates[0]);
                    candidates= std::vector<Chromosome>();
                }
            }
            break;
        }
        case SELECTION_TYPE_STOCHASTIC:
            for (int i = 0; i < numElements; ++i) {
                selectedElems.push_back(elems[i]);
            }
            break;
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
