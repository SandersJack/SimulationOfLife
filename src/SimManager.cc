#include "SimManager.hh"

#include <cstdlib>
#include <iostream>
#include <random>

SimManager::SimManager() {

}

SimManager::~SimManager(){

}

SimManager *SimManager::fInstance = nullptr;

SimManager *SimManager::GetInstance() {
    if(!fInstance){
        fInstance = new SimManager();
    }
    return fInstance;
}

void SimManager::Init(const int numOrganisms, const int numFood) {
    fWorld = new World(fGridSize);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 32767);

    for (int i = 0; i < numOrganisms; ++i) {
        int x = dis(gen) % fGridSize;
        int y = dis(gen) % fGridSize;

        if (fWorld->GetElement(x,y) == nullptr) {
            fWorld->setElement(new Organism(*fWorld), x,y);
        } else {
            // Retry if the position is already occupied
            --i;
        }
    }

    for (int i = 0; i < numFood; ++i) {
        int x = dis(gen) % fGridSize;
        int y = dis(gen) % fGridSize;

        if (fWorld->GetElement(x,y) == nullptr) {
            fWorld->setElement(new FoodItem(*fWorld), x,y);
        } else {
            --i;
        }
    }

    fFoods = fWorld->GetFoods();
    fOrganisms = fWorld->GetOrganisms();
    fWorld->displayGrid();
}

void SimManager::Step(){
    fWorld->step();
    fWorld->displayGrid();
}