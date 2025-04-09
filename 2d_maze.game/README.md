# Maze Escape Game

A 2D maze game where you navigate through increasingly difficult levels, collect items, and avoid enemies to reach the exit.

## Features
- Multiple levels with increasing difficulty
- Collectible items for points
- Enemy AI that chases the player
- Color-coded display
- Score tracking
- Move counter

## Controls
- W - Move Up
- S - Move Down
- A - Move Left
- D - Move Right
- Q - Quit Game

## Requirements
- Windows operating system
- C++ compiler (MinGW-w64 recommended)
- Windows.h header (included with Windows SDK)

## Compilation and Running

### Method 1: Using the Batch File
1. Open Command Prompt or PowerShell
2. Navigate to the game directory
3. Run the compile script:
   ```
   compile.bat
   ```
4. The game will start automatically after compilation

### Method 2: Manual Compilation
1. Open Command Prompt or PowerShell
2. Navigate to the game directory
3. Compile the game using g++:
   ```
   g++ -o maze.exe main.cpp Maze.cpp Player.cpp Enemy.cpp Item.cpp console.cpp -I.
   ```
4. Run the game:
   ```
   maze.exe
   ```

## Game Rules
1. Start from the top-left corner (marked with 'P')
2. Collect yellow items (*) for 10 points each
3. Avoid red enemies (X) - touching them ends the game
4. Reach the green exit (E) to complete the level
5. Each level increases in difficulty with:
   - More walls
   - More enemies
   - Fewer items
   - Faster enemy movement

## Troubleshooting
If you encounter compilation errors:
1. Ensure you have MinGW-w64 installed
2. Verify that g++ is in your system PATH
3. Check that all source files are present in the directory
4. Make sure you're using a Windows system (the game uses Windows-specific console functions)

## File Structure
- `main.cpp` - Main game loop and initialization
- `Maze.cpp` - Maze generation and game logic
- `Player.cpp` - Player movement and collision
- `Enemy.cpp` - Enemy AI and movement
- `Item.cpp` - Item handling
- `console.cpp` - Console display and input handling
- `*.h` files - Header files for each class
- `compile.bat` - Compilation script 