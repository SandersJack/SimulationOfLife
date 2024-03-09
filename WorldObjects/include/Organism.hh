#ifndef Organism_H
#define Organism_H

#include "WObject.hh"
#include "World.hh"

#include <cstdlib>

// Forward declaration of World class
class World;

class Organism: public WObject {

    public:
        Organism();
        ~Organism();

        const char* className() const override {return "Organism";}

        void moveRandom(World& world);
        void moveUp(World& world);
        void moveDown(World& world);
        void moveLeft(World& world);
        void moveRight(World& world);
        
    private:

        int fAge;
        double fHunger;
        double fHealth;

};


#endif