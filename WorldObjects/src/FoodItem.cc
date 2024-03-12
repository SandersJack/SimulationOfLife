#include "FoodItem.hh"

#include <iostream>

FoodItem::FoodItem(World &world) : fWorld(world), fNourishment(50.0), fDecayRate(0.3), fIsDecayed(false) { }

FoodItem::~FoodItem() { }

int FoodItem::step() {
    const float decayProb = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    // Rot the food if random number is below the decay rate
    if(decayProb < fDecayRate) {
        fIsDecayed = true;
        //fWorld.removeElement(this); // TODO: Eating rotten food harms you rather than removing?
        return 0;
    }

    return 1;
}

void FoodItem::eat() {
    fWorld.removeElement(this);
    delete this;
}