#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include <random>

class Enemy : public Entity {
private:
    std::random_device rd;
    std::mt19937 gen;
    int moveCounter;
    static const int MOVE_INTERVAL = 3;

public:
    Enemy(int startX, int startY) 
        : Entity(startX, startY, 'X', "Enemy")
        , gen(rd())
        , moveCounter(0) {}

    void update() override {
        moveCounter++;
        if (moveCounter >= MOVE_INTERVAL) {
            moveCounter = 0;
            // Random movement logic will be implemented in Maze class
        }
    }

    bool isCollidable() const override { return true; }
};

#endif // ENEMY_H 