#include "World.hh"

World::World(int gridsize): fGridSize(gridsize){
    grid = new WObject*[fGridSize];
    for (int i = 0; i < fGridSize; ++i) {
        grid[i] = new WObject[fGridSize];
    }
}

World::~World(){

}

