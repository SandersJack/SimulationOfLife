#include "Organism.hh"

Organism::Organism(): fAge(0), fHunger(100), fHealth(100) {

}

Organism::~Organism(){
}

void Organism::moveRandom(World& world) {
    int direction = rand() % 4;  // 0: up, 1: down, 2: left, 3: right

    switch (direction) {
        case 0:
            moveUp(world);
            break;
        case 1:
            moveDown(world);
            break;
        case 2:
            moveLeft(world);
            break;
        case 3:
            moveRight(world);
            break;
        default:
            break;
    }
}

void Organism::moveUp(World& world) {
    if (x - 1 >= 0 && !world.isOccupied(x, y - 1)) {
        world.moveElement(this, x, y - 1);
    }
}

void Organism::moveDown(World& world) {
    if (y + 1 < world.getGridSize() && !world.isOccupied(x, y + 1)) {
        world.moveElement(this, x, y + 1);
    }
}

void Organism::moveLeft(World& world) {
    if (x - 1 >= 0 && !world.isOccupied(x - 1, y)) {
        world.moveElement(this, x - 1, y);
    }
}

void Organism::moveRight(World& world) {
    if (x + 1 < world.getGridSize() && !world.isOccupied(x + 1, y)) {
        world.moveElement(this, x + 1, y);
    }
}