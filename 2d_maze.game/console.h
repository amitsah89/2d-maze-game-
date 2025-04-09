#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>
#include <conio.h>
#include <iostream>

class Console
{
public:
    static void setup()
    {
        // Set console to UTF-8 mode
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        // Get console handle
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        // Set console size
        COORD bufferSize = {51, 26};
        SMALL_RECT windowSize = {0, 0, 50, 25};

        // Set buffer size first (must be larger than window)
        SetConsoleScreenBufferSize(consoleHandle, bufferSize);
        SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize);

        // Enable ANSI escape sequences
        DWORD consoleMode;
        GetConsoleMode(consoleHandle, &consoleMode);
        SetConsoleMode(consoleHandle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        // Hide cursor
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }

    static void clearScreen()
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD topLeft = {0, 0};
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(consoleHandle, &screen);
        FillConsoleOutputCharacterA(consoleHandle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
        FillConsoleOutputAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
                                   screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
        SetConsoleCursorPosition(consoleHandle, topLeft);
    }

    static char getKeyPress()
    {
        if (_kbhit())
        {
            return _getch();
        }
        return 0;
    }
};

#endif // CONSOLE_H