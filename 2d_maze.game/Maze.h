#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <string>
#include <fstream>
#include "Entity.h"

class Maze
{
private:
    static const int SIZE = 15;
    char grid[SIZE][SIZE];
    std::vector<Entity *> entities;
    int score = 0;
    int totalScore = 0;
    int moves = 0;
    int currentLevel = 1;

public:
    Maze() { initializeMaze(); }

    ~Maze()
    {
        for (Entity *entity : entities)
        {
            delete entity;
        }
    }

    void initializeMaze();
    void display();
    bool movePlayer(char direction);
    void updateEntities();
    bool checkCollision(int x, int y) const;
    void addEntity(Entity *entity);
    void removeEntity(Entity *entity);
    bool saveMaze(const std::string &filename) const;
    bool loadMaze(const std::string &filename);
    void generateNewLevel();
    void setCell(int x, int y, char value);

    // Getters
    char getCell(int x, int y) const { return grid[x][y]; }
    int getScore() const { return score; }
    int getTotalScore() const { return totalScore + score; }
    int getMoves() const { return moves; }
    int getCurrentLevel() const { return currentLevel; }
    int getPlayerX() const
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (grid[i][j] == 'P')
                    return i;
        return -1;
    }
    int getPlayerY() const
    {
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (grid[i][j] == 'P')
                    return j;
        return -1;
    }

    // Setters
    void incrementScore(int points)
    {
        score += points;
        totalScore += points;
    }
    void incrementMoves() { moves++; }
};

#endif // MAZE_H