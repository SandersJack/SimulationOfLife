#include "SimManager.hh"

#include <iostream>
#include <string.h> 

int main(int argc, char* argv[]){

    int gridsize = 64;

    // Parse input arguments
    for (int i = 1; i < argc; i++)
    {  
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-gs") == 0) // GridSize
            {                 
                gridsize = std::stod(argv[i + 1]);
                i++;
            } 
        }
        if (strcmp(argv[i], "-h") == 0) // Help
            {                 
                std::cout << "-----------------------------------" << std::endl;
                std::cout << "Displaying Help Message:" << std::endl;
                std::cout << "-gs <int> : Grid size of the world (gridsize x gridsize)" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                exit(0);
        }
        // Call the sim manager
        SimManager *simMan = SimManager::GetInstance();
        // Set Simulation Paramters
        simMan->SetGridSize(gridsize);
        
        // Init the Simulation
        simMan->Init();

    }
    return 0;
}