#include "src/Chromosome.h"
#include "src/GenesPool.h"

int main(int argc, char *argv[]) {
    std::string constants;
    if(argc > 1){
    printf("%s %d",argv[1],argc);
        constants = argv[1];
    }else{
        constants = "/home/calazans/Documents/projects/GeneticAlgorithmCPP/Constants.txt";
    }
    try{

        ConstMethods::initConstants(constants);
        GenesPool gp = GenesPool();
        gp.run();
        ConstMethods::terminateConstants();
    }catch (std::exception& e)
    {
        printf("%s\n",e.what());
    }return 0;
}
