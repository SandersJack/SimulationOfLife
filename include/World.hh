#ifndef World_H
#define World_H

#include "WObject.hh"
#include "Organism.hh"

#include <vector>

// Forward declaration of Organism class
class Organism;


class World {
    
    public:
        World(int gridsize);
        ~World();

        int getGridSize(){return fGridSize;}

        void setElement(WObject* obj, int x, int y);
        WObject* GetElement(int x, int y){return fGrid[x][y];}

        void removeElement(WObject* obj);
        void moveElement(WObject* obj, int x_new, int y_new);

        void displayGrid() const;

        std::vector<Organism*> GetOrganisms(){return fOrganisms;}

        bool isOccupied(int posX, int posY){return fGrid[posX][posY] != nullptr;}

        void step();

    private:

        WObject* **fGrid;
        int fGridSize;

        std::vector<Organism*> fOrganisms;

        std::vector<WObject*> fWObjects;
        
};

#endif