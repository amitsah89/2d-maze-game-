#include "Maze.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "console.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <windows.h>
#include <sstream>

// Add this helper function at the top of the file
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Maze::initializeMaze()
{
    // Initialize empty maze
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            grid[i][j] = ' ';
        }
    }

    // Add walls around the edges
    for (int i = 0; i < SIZE; i++)
    {
        grid[0][i] = '#';
        grid[SIZE - 1][i] = '#';
        grid[i][0] = '#';
        grid[i][SIZE - 1] = '#';
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, SIZE - 2);

    // Level-specific configurations
    int numWalls, numItems, numEnemies;
    switch (currentLevel)
    {
    case 1: // Easy level
        numWalls = 15;
        numItems = 5;
        numEnemies = 2;
        break;
    case 2: // Medium level
        numWalls = 20;
        numItems = 4;
        numEnemies = 3;
        break;
    case 3: // Hard level
        numWalls = 25;
        numItems = 3;
        numEnemies = 4;
        break;
    default: // Extra hard levels
        numWalls = 25 + (currentLevel - 3) * 2;
        numItems = 3;
        numEnemies = 4 + (currentLevel - 3);
        break;
    }

    // Add random walls
    for (int i = 0; i < numWalls; i++)
    {
        int x, y;
        do
        {
            x = dis(gen);
            y = dis(gen);
        } while (grid[x][y] != ' ');
        grid[x][y] = '#';
    }

    // Place player at start position
    grid[1][1] = 'P';

    // Place exit
    grid[SIZE - 2][SIZE - 2] = 'E';

    // Add items
    for (int i = 0; i < numItems; i++)
    {
        int x, y;
        do
        {
            x = dis(gen);
            y = dis(gen);
        } while (grid[x][y] != ' ');
        grid[x][y] = '*';
    }

    // Add enemies
    for (int i = 0; i < numEnemies; i++)
    {
        int x, y;
        do
        {
            x = dis(gen);
            y = dis(gen);
        } while (grid[x][y] != ' ');
        grid[x][y] = 'X';
    }
}

void Maze::display()
{
    // Clear the screen first
    Console::clearScreen();

    // Move cursor to top-left
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPos = {0, 0};
    SetConsoleCursorPosition(consoleHandle, cursorPos);

    // Build the entire display string first
    std::stringstream ss;
    ss << "\n\n";
    ss << "   +------------------------+\n";
    ss << "   | Level: " << currentLevel << " | Score: " << score << " | Moves: " << moves << " |\n";
    ss << "   +------------------------+\n\n";

    for (int i = 0; i < SIZE; i++)
    {
        ss << "   ";
        for (int j = 0; j < SIZE; j++)
        {
            switch (grid[i][j])
            {
            case 'P':
                ss << "\033[1;32mP\033[0m "; // Green player
                break;
            case 'X':
                ss << "\033[1;31mX\033[0m "; // Red enemies
                break;
            case '*':
                ss << "\033[1;33m*\033[0m "; // Yellow items
                break;
            case 'E':
                ss << "\033[1;36mE\033[0m "; // Cyan exit
                break;
            case '#':
                ss << "\033[1;37m#\033[0m "; // White walls
                break;
            default:
                ss << "  ";
            }
        }
        ss << "\n";
    }
    ss << "\n   W:Up S:Down A:Left D:Right Q:Quit\n";

    // Output everything at once
    std::cout << ss.str();
}

bool Maze::movePlayer(char direction)
{
    int newX = -1, newY = -1;
    int playerX = -1, playerY = -1;

    // Find current player position
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == 'P')
            {
                playerX = i;
                playerY = j;
                break;
            }
        }
        if (playerX != -1)
            break;
    }

    // Calculate new position based on direction
    switch (toupper(direction))
    {
    case 'W':
        newX = playerX - 1;
        newY = playerY;
        break;
    case 'S':
        newX = playerX + 1;
        newY = playerY;
        break;
    case 'A':
        newX = playerX;
        newY = playerY - 1;
        break;
    case 'D':
        newX = playerX;
        newY = playerY + 1;
        break;
    default:
        return false;
    }

    // Check if move is valid
    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE || grid[newX][newY] == '#')
    {
        return false;
    }

    // Handle collisions with items and enemies
    if (grid[newX][newY] == '*')
    {
        score += 10;
    }
    else if (grid[newX][newY] == 'X')
    {
        return false; // Game over
    }

    // Move player
    grid[playerX][playerY] = ' ';
    grid[newX][newY] = 'P';
    moves++;
    return true;
}

void Maze::updateEntities()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, SIZE - 2);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (grid[i][j] == 'X')
            {
                int playerX = getPlayerX();
                int playerY = getPlayerY();

                int dx = playerX - i;
                int dy = playerY - j;

                int newX = i;
                int newY = j;

                // Adjust enemy movement speed based on level
                int moveChance = (currentLevel <= 2) ? 4 : 3; // Faster movement in higher levels

                if (abs(dx) > abs(dy))
                {
                    if (dx > 0 && dis(gen) % moveChance != 0)
                        newX = i + 1;
                    else if (dx < 0 && dis(gen) % moveChance != 0)
                        newX = i - 1;
                }
                else
                {
                    if (dy > 0 && dis(gen) % moveChance != 0)
                        newY = j + 1;
                    else if (dy < 0 && dis(gen) % moveChance != 0)
                        newY = j - 1;
                }

                if (newX > 0 && newX < SIZE - 1 && newY > 0 && newY < SIZE - 1 &&
                    grid[newX][newY] == ' ')
                {
                    grid[i][j] = ' ';
                    grid[newX][newY] = 'X';
                }
            }
        }
    }
}

bool Maze::checkCollision(int x, int y) const
{
    return grid[x][y] == '#' || grid[x][y] == 'X';
}

void Maze::addEntity(Entity *entity)
{
    entities.push_back(entity);
    grid[entity->getX()][entity->getY()] = entity->getSymbol();
}

void Maze::removeEntity(Entity *entity)
{
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end())
    {
        entities.erase(it);
        grid[entity->getX()][entity->getY()] = ' ';
    }
}

bool Maze::saveMaze(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            file << grid[i][j];
        }
        file << '\n';
    }

    file << score << ' ' << moves << ' ' << currentLevel << '\n';
    return true;
}

bool Maze::loadMaze(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            file >> grid[i][j];
        }
    }

    file >> score >> moves >> currentLevel;
    return true;
}

void Maze::generateNewLevel()
{
    currentLevel++;
    score = 0; // Reset level score
    moves = 0;
    initializeMaze();
}

void Maze::setCell(int x, int y, char value)
{
    grid[x][y] = value;
}