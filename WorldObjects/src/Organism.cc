#include "Organism.hh"

#include <iostream>

Organism::Organism(World& world): fWorld(world), fAge(0), fHunger(100), fHealth(100), fAlive(true), 
    fHealth_loss(50), fHunger_loss(50){

}

Organism::~Organism(){
}

void Organism::moveRandom() {
    int direction = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

    switch (direction) {
        case 0:
            moveUp();
            break;
        case 1:
            moveDown();
            break;
        case 2:
            moveLeft();
            break;
        case 3:
            moveRight();
            break;
        default:
            break;
    }
}

void Organism::moveUp() {
    if (y - 1 >= 0 && !fWorld.isOccupied(x, y - 1)) {
        fWorld.moveElement(this, x, y - 1);
    }
}

void Organism::moveDown() {
    if (y + 1 < fWorld.getGridSize() && !fWorld.isOccupied(x, y + 1)) {
        fWorld.moveElement(this, x, y + 1);
    }
}

void Organism::moveLeft() {
    if (x - 1 >= 0 && !fWorld.isOccupied(x - 1, y)) {
        fWorld.moveElement(this, x - 1, y);
    }
}

void Organism::moveRight() {
    if (x + 1 < fWorld.getGridSize() && !fWorld.isOccupied(x + 1, y)) {
        fWorld.moveElement(this, x + 1, y);
    }
}

void Organism::die(){
    fAlive = false;
    fWorld.removeElement(this);
    delete this;
}

void Organism::removeHealth(double val){
    if (fHealth > val){
        fHealth -= val;
    } else {
        die();
    }
}

void Organism::removeHunger(double val){
    if (fHunger > val){
        fHunger -= val;
    } else {
        removeHealth(fHealth_loss);
    }
}


int Organism::step(){
    moveRandom();
    removeHunger(fHunger_loss);
    return fAlive;
}
