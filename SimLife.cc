#include "SimManager.hh"

#include <iostream>
#include <string.h> 

int main(int argc, char* argv[]){

    int gridsize = 64;

    int numOrganisms = 10;

    // Parse input arguments
    for (int i = 1; i < argc; i++)
    {  
        if (i + 1 != argc)
        {
            if (strcmp(argv[i], "-gS") == 0) // GridSize
            {                 
                gridsize = std::stod(argv[i + 1]);
                i++;
            } 
            if (strcmp(argv[i], "-nO") == 0) // GridSize
            {                 
                numOrganisms = std::stod(argv[i + 1]);
                i++;
            } 
        }
        if (strcmp(argv[i], "-h") == 0) // Help
            {                 
                std::cout << "-----------------------------------" << std::endl;
                std::cout << "Displaying Help Message:" << std::endl;
                std::cout << "-gS <int> : Grid size of the world (gridsize x gridsize)" << std::endl;
                std::cout << "-nO <int> : Number of Organisms" << std::endl;
                std::cout << "-----------------------------------" << std::endl;
                exit(0);
        }
    }

    // Call the sim manager
    SimManager *simMan = SimManager::GetInstance();
    // Set Simulation Paramters
    simMan->SetGridSize(gridsize);
    
    // Init the Simulation
    simMan->Init(numOrganisms);

    //First Step
    std::cout << "Step" << std::endl;
    simMan->Step();

    return 0;
}