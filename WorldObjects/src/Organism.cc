#include "FoodItem.hh"
#include "Organism.hh"

#include <iostream>
#include <random>
#include <cstring>

Organism::Organism(World& world): fWorld(world), fAge(0), fHunger(100), fHealth(100), fAlive(true), 
    fHealth_loss(50), fHunger_loss(20){

}

Organism::~Organism(){
}

void Organism::moveRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-2, 2); // Inclusive range [-2,2]
    int xRand = dis(gen);
    int yRand = dis(gen);

    move(xRand, yRand, false);
}

void Organism::move(const int dx, const int dy, const bool noCollision) {
    const int gridSize = fWorld.getGridSize();
    // Avoid movements outside the defined grid
    const int xNew = abs((x + dx) % gridSize); // Wraps around the grid
    const int yNew = abs((y + dy) % gridSize); // Wraps around the grid

    // Check if some food exists, if so eat it
    if(fWorld.isOccupied(xNew,yNew)) {
        if(strcmp(fWorld.GetElement(xNew, yNew)->className(), "FoodItem") == 0) {
            FoodItem *food = static_cast<FoodItem *>(fWorld.GetElement(xNew, yNew));
            if(food->getIsDecayed()) {
                removeHealth(10.0);
            } else {
                nourish(food->getNourishment());
            }
            food->eat();
        }
    }

    if(noCollision || (!fWorld.isOccupied(xNew,yNew) && !noCollision))
        fWorld.moveElement(this, xNew, yNew);
}

void Organism::moveUp() {
    move(0, 1, false);
}

void Organism::moveDown() {
    move(0, -1, false);
}

void Organism::moveLeft() {
    move(-1, 0, false);
}

void Organism::moveRight() {
    move(1, 0, false);
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

void Organism::nourish(const double nourishment) {
    fHunger += nourishment;
    if(fHunger > 100.0)
        fHunger = 100.0; // Maximum hunger is 100 meaning you are full
}

void Organism::removeHunger(double val) {
    if (fHunger > val){
        fHunger -= val;
    } else {
        removeHealth(fHealth_loss);
    }
}


int Organism::step() {
    moveRandom();
    removeHunger(fHunger_loss);
    return fAlive;
}
