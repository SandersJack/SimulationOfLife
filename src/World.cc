#include "World.hh"

#include <iostream>
#include <cstring>

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

void World::setElement(int x, int y, WObject* obj) {
    if (x >= 0 && x < fGridSize && y >= 0 && y < fGridSize) {
        // Delete existing object at the position
        delete fGrid[x][y];

        // Set the new object
        fGrid[x][y] = obj;
    } else {
        std::cerr << "Invalid position." << std::endl;
    }
}

void World::displayGrid() const {
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
    }
