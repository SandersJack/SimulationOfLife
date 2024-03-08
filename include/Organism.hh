#ifndef Organism_H
#define Organism_H

#include "WObject.hh"

class Orgainism: public WObject {

    public:
        Orgainism();
        ~Orgainism();

    private:

        int fAge;
        double fHunger;
        double fHealth;

};


#endif