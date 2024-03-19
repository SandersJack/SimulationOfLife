#include "World.hh"

#include <iostream>
#include <cstring>
#include <ctime>
#include <thread>
#include <algorithm>


const char* clearScreen = "\033[2J\033[H";

World::World(int gridsize): fGridSize(gridsize){
    fGrid = new WObject**[fGridSize];
    for (int i = 0; i < fGridSize; ++i) {
        fGrid[i] = new WObject*[fGridSize];
    }

    for (int i = 0; i < fGridSize; ++i) {
        for (int j = 0; j < fGridSize; ++j) {
            fGrid[i][j] = nullptr;
        }
    }
}

World::~World(){
    // Free memory
    for (int i = 0; i < fGridSize; ++i) {
        for (int j = 0; j < fGridSize; ++j) {
            delete fGrid[i][j];
        }
        delete[] fGrid[i];
    }
    delete[] fGrid;
}

void World::setElement(WObject* obj, int x, int y) {
    if (x >= 0 && x < fGridSize && y >= 0 && y < fGridSize) {
        // Delete existing object at the position
        delete fGrid[x][y];

        // Set the new object
        fGrid[x][y] = obj;
        obj->SetPosition(x,y);

        fWObjects.push_back(obj);
        if(strcmp(fGrid[x][y]->className(), "Organism") == 0){
            fOrganisms.push_back(static_cast<Organism*>(obj));
        } else if(strcmp(fGrid[x][y]->className(), "FoodItem") == 0) {
            fFoods.push_back(static_cast<FoodItem*>(obj));
        }

    } else {
        std::cerr << "Invalid position." << std::endl;
    }
}

void World::moveElement(WObject* obj, int x_new, int y_new) {
    int x_old, y_old;
    x_old = obj->GetX();
    y_old = obj->GetY();
    
    if (x_new >= 0 && x_new < fGridSize && y_new >= 0 && y_new < fGridSize) {
        fGrid[x_old][y_old] = nullptr;
        //if(isOccupied(x_new, y_new)) // Is the place the object is moving to occupied
        //    removeElement(GetElement(x_new, y_new)); // remove current occupier
        fGrid[x_new][y_new] = obj;
        obj->SetPosition(x_new, y_new);
    } else {
        std::cerr << "Invalid position." << std::endl;
    }
}

void World::removeElement(WObject* obj){
    fGrid[obj->GetX()][obj->GetY()] = nullptr;

    auto it = std::find_if(fWObjects.begin(), fWObjects.end(),
                           [obj](WObject* element) { return element == obj; });
    if (it != fWObjects.end()) {
        fWObjects.erase(it);
    }
    if(strcmp(obj->className(), "Organism") == 0){

        auto it_ = std::find_if(fOrganisms.begin(), fOrganisms.end(),
                           [obj](Organism* element) { return element == obj; });
        if (it_ != fOrganisms.end()) {
            fOrganisms.erase(it_);
        }
    } else if(strcmp(obj->className(), "FoodItem") == 0){
        auto it_ = std::find_if(fFoods.begin(), fFoods.end(),
                           [obj](FoodItem* element) { return element == obj; });
        if (it_ != fFoods.end()) {
            fFoods.erase(it_);
        }
    }
}

void World::displayGrid() const {
    std::cout << clearScreen;
    std::cout << "¦" << std::string(fGridSize*2 + 1, '-') << "¦" << std::endl;
    for (int y = 0; y < fGridSize; ++y) {
        std::cout << "¦ ";
        for (int x = 0; x < fGridSize; ++x) {
            if (fGrid[x][y] == nullptr) {
                std::cout << ". ";
            } else {
                if(strcmp(fGrid[x][y]->className(), "Organism") == 0){
                    std::cout << "O ";
                } else if(strcmp(fGrid[x][y]->className(), "FoodItem") == 0) {
                    if(static_cast<FoodItem*>(fGrid[x][y])->getIsDecayed()) {
                        std::cout << "R ";
                    } else {
                        std::cout << "F ";
                    }
                }
            }
        }
        std::cout << "¦" << std::endl;
    }
    std::cout << "¦" << std::string(fGridSize*2 + 1, '-') << "¦" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void World::step(){
    for (auto it = fWObjects.begin(); it != fWObjects.end();) {
        WObject* wo = *it;

        int response = wo->step();
        if(response)
            ++it;
    }
}