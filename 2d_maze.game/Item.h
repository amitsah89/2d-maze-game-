#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"

class Item : public Entity {
private:
    int points;
    bool collected;

public:
    Item(int startX, int startY, int pointValue = 10)
        : Entity(startX, startY, '*', "Item")
        , points(pointValue)
        , collected(false) {}

    void update() override {} // Items don't need updates

    bool isCollidable() const override { return false; }
    
    int getPoints() const { return points; }
    bool isCollected() const { return collected; }
    void collect() { collected = true; }
};

#endif // ITEM_H 