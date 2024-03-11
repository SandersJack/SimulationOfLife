#ifndef SimManager_H
#define SimManager_H 

#include "World.hh"
#include "Organism.hh"
#include "FoodItem.hh"

#include <vector>

class SimManager {
    public:
        SimManager();
        ~SimManager();

        void Init(const int numOrganisms, const int numFood);
        void Step();

        void SetGridSize(int val){fGridSize = val;}

        static SimManager *GetInstance();
    private:
        static SimManager *fInstance;
        
        int fGridSize;
        World *fWorld;

        std::vector<Organism*> fOrganisms;
        std::vector<FoodItem*> fFoods;
};

#endif