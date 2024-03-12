#ifndef FOODITEM_H
#define FOODITEM_H

#include "WObject.hh"
#include "World.hh"

#include <cmath>
#include <cstdlib>

class World;

class FoodItem : public WObject {
    public:
        FoodItem(World &world);
        ~FoodItem();
        
        const char* className() const override { return "FoodItem"; }

        void eat();
        
        bool getIsDecayed() { return fIsDecayed; };
        float getNourishment() { return fNourishment; };
        void setNourishment(const float nourishment) { fNourishment = nourishment; };
        void setDecayRate(const float rate) { fDecayRate = rate; };

        int step() override;
    private:
        World &fWorld;
        float fNourishment; ///< Value of this food item (100 would completely satisfy the hunger)
        float fDecayRate; ///< Probability of the food to "rot/decay" each step once rotted food has no nourishment
        bool fIsDecayed; ///< True when the food item has rotted and provides no nourishment
};

#endif