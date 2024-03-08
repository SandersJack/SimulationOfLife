#ifndef World_H
#define World_H

#include "WObject.hh"

class World {
    
    public:
        World(int gridsize);
        ~World();

    private:

        WObject **grid;
        int fGridSize;
        
};

#endif