#include "SimManager.hh"

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

void SimManager::Init() {
    fWorld = new World(fGridSize);
}

void SimManager::Step(){

}