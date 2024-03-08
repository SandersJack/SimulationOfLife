#ifndef World_H
#define World_H

#include "WObject.hh"

class World {
    
    public:
        World(int gridsize);
        ~World();

        void setElement(int x, int y, WObject* obj);
        WObject* GetElement(int x, int y){return fGrid[x][y];}

        void displayGrid() const;

    private:

        WObject* **fGrid;
        int fGridSize;
        
};

#endif