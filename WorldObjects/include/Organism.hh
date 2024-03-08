#ifndef Organism_H
#define Organism_H

#include "WObject.hh"

class Organism: public WObject {

    public:
        Organism();
        ~Organism();

        const char* className() const override {return "Organism";}
        
    private:

        int fAge;
        double fHunger;
        double fHealth;

};


#endif