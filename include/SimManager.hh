#ifndef SimManager_H
#define SimManager_H 

#include "World.hh"
#include "Organism.hh"
#include "FoodItem.hh"
#include "GUI.hh"

#include <vector>


class SimManager {
    public:
        SimManager();
        ~SimManager();

        void Init(const int numOrganisms, const int numFood);
        void Step();

        void SetGridSize(int val){fGridSize = val;}
        int GetGridSize(){return fGridSize;}

        void SetVisuliseType(int val){fVisType = val;}

        std::vector<Organism*> GetOrganisms(){return fOrganisms;};
        std::vector<FoodItem*> GetFoodItems(){return fFoods;};

        static SimManager *GetInstance();
    private:
        static SimManager *fInstance;
        
        int fGridSize;
        World *fWorld;

        int fVisType;

        std::vector<Organism*> fOrganisms;
        std::vector<FoodItem*> fFoods;
};

#endif