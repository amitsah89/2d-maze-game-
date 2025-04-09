@echo off
chcp 65001 > nul
g++ -o maze_game main.cpp Maze.cpp -std=c++11 -I"C:\msys64\ucrt64\include" -L"C:\msys64\ucrt64\lib" -luser32 -lkernel32
if %errorlevel% equ 0 (
    echo Compilation successful!
    echo Running the game...
    cls
    maze_game
) else (
    echo Compilation failed!
    pause
) 