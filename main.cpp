#include "src/Chromosome.h"
#include "src/GenesPool.h"

int main() {

    try{
        ConstMethods::initConstants("/home/calazans/Documents/projects/01/build/Constants.txt");
        GenesPool gp = GenesPool();
        gp.run();
        ConstMethods::terminateConstants();
    }catch (std::exception& e)
    {
        printf("%s\n",e.what());
    }return 0;
}
