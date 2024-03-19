#include "FoodItem.hh"
#include "Organism.hh"

#include <iostream>
#include <random>
#include <cstring>

Organism::Organism(World& world): fWorld(world), fGenetics(0), fMaxStepDistance(3.0), fAge(0), fHunger(100), fHealth(100), fAlive(true), 
    fHealth_loss(50), fHunger_loss(20){
        MakeRandomGeneticProfile();
}

Organism::~Organism(){
}

void Organism::MakeRandomGeneticProfile() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1);
    for(U8 i = 0; i < 16; ++i) {
        bool hasGene = dis(gen);
        if(hasGene)
            fGenetics |= 1ULL << i;
    }
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

void Organism::moveToFood(const int searchRadius) {
    // Steps the organism towards the nearest source of nourishment (including rot)
    const int gridSize = fWorld.getGridSize();
    std::pair<int, int> closestFood = std::make_pair(-1, -1);
    float bestDistToFood = 999999.;

    // TODO: this actually searches a square currently rather than a radius but it'll do
    for(int dx = -searchRadius; dx < searchRadius; ++dx) {
        for(int dy = -searchRadius; dy < searchRadius; ++dy) {
            const int xNew = abs((x + dx) % gridSize);
            const int yNew = abs((y + dy) % gridSize); // % to allow wrap-around
            if(fWorld.isOccupied(xNew, yNew)) {
                if(strcmp(fWorld.GetElement(xNew, yNew)->className(), "FoodItem") != 0)
                    continue;
                // Food item exists at xnew ynew
                float dist = sqrt(pow(dx,2)+pow(dy,2));
                if(dist < bestDistToFood) {
                    bestDistToFood = dist;
                    closestFood = std::make_pair(dx, dy);
                }
            }
        }
    }

    // Found food in the search radius to look for
    if(bestDistToFood < 999999.) {
        // Calculate the next step as the unit vector towards the food
        double stepX = std::min(fMaxStepDistance, bestDistToFood) * (closestFood.first / bestDistToFood);
        double stepY = std::min(fMaxStepDistance, bestDistToFood) * (closestFood.second / bestDistToFood);
        // Step towards the food in both x and y by 1 unit
        move((int)stepX, (int)stepY, false);
    }
}

int Organism::step() {
    //moveRandom();
    moveToFood(8);

    if(get_bit(fGenetics, (U8)Trait::SlowMetabolism)) {
        // Organisms with a slower metabolism lose hunger slower
        removeHunger(fHunger_loss / 2);
    } else {
        removeHunger(fHunger_loss);
    }
    return fAlive;
}
