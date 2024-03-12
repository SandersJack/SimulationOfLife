#ifndef Organism_H
#define Organism_H

#include "WObject.hh"
#include "World.hh"

#include <cstdlib>

// Forward declaration of World class
class World;
class FoodItem;

class Organism: public WObject {

    public:
        Organism(World& world);
        ~Organism();

        const char* className() const override {return "Organism";}

        void moveRandom();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void move(const int dx, const int dy, const bool noCollision);

        void die();
        bool isAlive() const { return fAlive; }

        void removeHealth(double val);
        void removeHunger(double val);
        void nourish(const double nourishment);

        void setHealthLoss(double val){fHealth_loss = val;}

        int step() override;
        
    private:
        World &fWorld;

        int fAge;
        double fHunger;
        double fHealth;
        bool fAlive;

        double fHealth_loss;
        double fHunger_loss;

};


#endif