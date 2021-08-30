#include <iostream>
#include "raylib.h"

int main()
{
    // Window size
    const int win_width{512};
    const int win_height{380};

    // Window
    InitWindow(win_width, win_height, "Dapper-Dasher");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        EndDrawing();
    }

    CloseWindow();
    
}