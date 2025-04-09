#include "Maze.h"
#include "console.h"
#include <iostream>
#include <chrono>

int main()
{
    Console::setup();
    Maze game;
    char input;
    bool gameRunning = true;
    bool gameOver = false;

    // Timing variables
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    const auto frameTime = std::chrono::milliseconds(50);        // 20 FPS
    const auto enemyUpdateTime = std::chrono::milliseconds(500); // Enemy update every 500ms
    const auto inputDelay = std::chrono::milliseconds(100);      // Input delay for better control

    TimePoint lastFrameTime = Clock::now();
    TimePoint lastEnemyUpdate = Clock::now();
    TimePoint lastInputTime = Clock::now();
    bool needsDisplay = true; // Flag to track if display needs updating

    // Title screen
    Console::clearScreen();
    std::cout << "\n\n";
    std::cout << "   +------------------------+\n";
    std::cout << "   |      MAZE ESCAPE!      |\n";
    std::cout << "   +------------------------+\n\n";
    std::cout << "   Collect items (*) for points\n";
    std::cout << "   Avoid enemies (X)\n";
    std::cout << "   Reach the exit (E)\n\n";
    std::cout << "   Controls:\n";
    std::cout << "   W - Up\n";
    std::cout << "   S - Down\n";
    std::cout << "   A - Left\n";
    std::cout << "   D - Right\n";
    std::cout << "   Q - Quit\n\n";
    std::cout << "   Press any key to start...\n";
    while (!Console::getKeyPress())
        Sleep(1); // Reduced sleep time for better responsiveness

    while (gameRunning)
    {
        auto currentTime = Clock::now();

        // Handle input with delay
        char key = Console::getKeyPress();
        if (key && (currentTime - lastInputTime >= inputDelay))
        {
            input = toupper(key);
            lastInputTime = currentTime;
            needsDisplay = true; // Mark display as needed when input is received

            if (input == 'Q')
            {
                gameRunning = false;
                break;
            }

            if (input == 'W' || input == 'A' || input == 'S' || input == 'D')
            {
                if (!game.movePlayer(input))
                {
                    if (game.getCell(game.getPlayerX(), game.getPlayerY()) == 'X')
                    {
                        gameOver = true;
                        break;
                    }
                }
            }
        }

        // Update display only when needed or at frame rate
        if (needsDisplay || (currentTime - lastFrameTime >= frameTime))
        {
            game.display();
            lastFrameTime = currentTime;
            needsDisplay = false;
        }

        // Update enemies at slower rate
        if (currentTime - lastEnemyUpdate >= enemyUpdateTime)
        {
            game.updateEntities();
            lastEnemyUpdate = currentTime;
            needsDisplay = true; // Mark display as needed when enemies move
        }

        // Check win condition
        if (game.getCell(game.getPlayerX(), game.getPlayerY()) == 'E')
        {
            Console::clearScreen();
            std::cout << "\n\n";
            std::cout << "   +------------------------+\n";
            std::cout << "   |    LEVEL " << game.getCurrentLevel() << " COMPLETE!    |\n";
            std::cout << "   +------------------------+\n\n";
            std::cout << "   Level Score: " << game.getScore() << "\n";
            std::cout << "   Total Score: " << game.getTotalScore() << "\n";
            std::cout << "   Moves: " << game.getMoves() << "\n\n";
            std::cout << "   Press any key for next level...\n";
            while (!Console::getKeyPress())
                Sleep(1); // Reduced sleep time for better responsiveness
            game.generateNewLevel();
            lastFrameTime = Clock::now();
            lastEnemyUpdate = Clock::now();
            lastInputTime = Clock::now();
        }

        Sleep(1); // Reduced sleep time for better responsiveness
    }

    // Game over screen
    Console::clearScreen();
    std::cout << "\n\n";
    if (gameOver)
    {
        std::cout << "   +------------------------+\n";
        std::cout << "   |      GAME OVER!        |\n";
        std::cout << "   +------------------------+\n\n";
    }
    else
    {
        std::cout << "   +------------------------+\n";
        std::cout << "   |    THANKS FOR PLAYING! |\n";
        std::cout << "   +------------------------+\n\n";
    }
    std::cout << "   Final Score: " << game.getTotalScore() << "\n";
    std::cout << "   Total Moves: " << game.getMoves() << "\n";
    std::cout << "   Levels Completed: " << game.getCurrentLevel() - 1 << "\n\n";
    std::cout << "   Press any key to exit...\n";
    while (!Console::getKeyPress())
        Sleep(1); // Reduced sleep time for better responsiveness

    return 0;
}