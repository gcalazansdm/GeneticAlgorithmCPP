//
// Created by root on 16/09/2019.
//

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdio.h>
#include <cstring>
#include "Constants.h"
#include "Fitness.h"

Constants* instance;
std::string getExePath(){
    char path[PATH_MAX];
    char dest[PATH_MAX];
    memset(dest,0,sizeof(dest)); // readlink does not null terminate!
    struct stat info;
    pid_t pid = getpid();
    sprintf(path, "/proc/%d/exe", pid);
    if (readlink(path, dest, PATH_MAX) == -1)
        perror("readlink");

    return dest;
}
void getText(char *message, char *variable,char *variable2, int size){
    printf("\n %s: ", message);
    fgets(variable, sizeof(char) * size, stdin);
    sscanf(variable, "%s %[^\n]",variable2,variable);

}

void readText(const std::string& constants){
    int numOfGenes;
    int population;
    int numElems;
    float mutationRate;
    CrossoverType crossoverType;
    SelectionType selectionType;
    int numEpochsNotChanging;
    char cities[150];

    char name[150];
    //getExePath() +'/'+
    std::string path = constants.c_str();
    printf("%s\n",path.c_str());
    FILE* f = fopen(path.c_str(), "r");

    fscanf (f, "%s %d\n", name,&numOfGenes);
    printf("%s->%d\n",name,numOfGenes);

    fscanf (f, "%s %d\n", name,&population);
    printf("%s->%d\n",name,population);

    fscanf (f, "%s %d\n", name,&numElems);
    printf("%s->%d\n",name,numElems);

    fscanf (f, "%s %d\n", name,&numEpochsNotChanging);
    printf("%s->%d\n",name,numEpochsNotChanging);

    fscanf (f, "%s %f\n", name,&mutationRate);
    printf("%s->%f\n",name,mutationRate);
    int temp = 0;
    fscanf (f, "%s %d\n", name, &temp);
    crossoverType = (CrossoverType)temp;
    printf("%s->%d\n",name,crossoverType);

    fscanf (f, "%s %d\n", name,&temp);
    selectionType = (SelectionType)temp;
    printf("%s->%d\n",name,selectionType);

    fgets(cities, sizeof(cities), f);
    cities[strlen(cities)-1] = '\0';
    Fitness::parseFile(cities);
    instance = new Constants(numOfGenes,population,numElems,mutationRate,crossoverType,selectionType,numEpochsNotChanging,cities);
}

void ConstMethods::initConstants(const std::string& constants){
    if(instance == NULL)
    {
        readText(constants);
    }
}

const Constants* ConstMethods::getConstants(){
    return instance;
}

void ConstMethods::terminateConstants(){
    delete instance;
}