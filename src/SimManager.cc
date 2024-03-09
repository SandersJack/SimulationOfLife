#include "SimManager.hh"

#include <cstdlib>


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

void SimManager::Init(int numOrganisms) {
    fWorld = new World(fGridSize);

    for (int i = 0; i < numOrganisms; ++i) {
        int x = std::rand() % fGridSize;
        int y = std::rand() % fGridSize;

        if (fWorld->GetElement(x,y) == nullptr) {
            fWorld->setElement(new Organism(), x,y);
        } else {
            // Retry if the position is already occupied
            --i;
        }
    }

    fOrganisms = fWorld->GetOrganisms();
}

void SimManager::Step(){
    fWorld->displayGrid();

    for(auto o : fOrganisms){
        o->moveRandom(*fWorld);
    }
}