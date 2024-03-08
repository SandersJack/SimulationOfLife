#ifndef SimManager_H
#define SimManager_H 

#include "World.hh"

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
};

#endif