#include "SimManager.hh"

#include "GUI.hh"

#include <cstdlib>
#include <iostream>
#include <random>

SimManager::SimManager(): fVisType(-1){

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
    if(fVisType == 0)
        fWorld->displayGrid();
    else if(fVisType == 1){
        GUI *in_GUI = GUI::GetInstance();
        in_GUI->Init(1000, 1000);
        in_GUI->Draw();
    }

}

void SimManager::Step(){
    fOrganisms = fWorld->GetOrganisms();
    fFoods = fWorld->GetFoods();
    fWorld->step();
    if(fVisType == 0)
        fWorld->displayGrid();
    else if(fVisType == 1)
        GUI::GetInstance()->Draw();
}