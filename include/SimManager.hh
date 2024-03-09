#ifndef SimManager_H
#define SimManager_H 

#include "World.hh"
#include "Organism.hh"

#include <vector>

class SimManager {
    public:
        SimManager();
        ~SimManager();

        void Init(int numOrganisms);
        void Step();

        void SetGridSize(int val){fGridSize = val;}

        static SimManager *GetInstance();
    private:
        static SimManager *fInstance;
        
        int fGridSize;
        World *fWorld;

        std::vector<Organism*> fOrganisms;
};

#endif