#include "World.hh"

#include <iostream>
#include <cstring>
#include <ctime>
#include <thread>

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

        if(strcmp(fGrid[x][y]->className(), "Organism") == 0){
            fOrganisms.push_back(static_cast<Organism*>(obj));
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
        fGrid[x_new][y_new] = obj;

        obj->SetPosition(x_new, y_new);

    } else {
        std::cerr << "Invalid position." << std::endl;
    }
}

void World::displayGrid() const {
    std::cout << clearScreen;

    for (int i = 0; i < fGridSize; ++i) {
        for (int j = 0; j < fGridSize; ++j) {
            if (fGrid[i][j] == nullptr) {
                std::cout << ". ";
            } else {
                if(strcmp(fGrid[i][j]->className(), "Organism") == 0){
                    std::cout << "O ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}
