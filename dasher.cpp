#include <iostream>
#include "raylib.h"

int main()
{
    // Window size
    const int win_width{512};
    const int win_height{380};

    // Window
    InitWindow(win_width, win_height, "Dapper-Dasher");

    // Acceleration due to gravity (pixel/frame)/frame
    const int gravity{1};

    // Rectangle dimensions
    const int rec_width{50};
    const int rec_height{80};
    int rec_posY{win_height - rec_height};

    int velocity{0};

    // Jump velocity
    int jumpVel{-22};

    bool isInAir{};


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        // Ground check
        if(rec_posY >= win_height - rec_height)
        {
            // Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // Rectangle is in the air
            velocity += gravity;
            isInAir = true;
        }

        // Check for jumping
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }
        

        // Update Y position of the rectangle
        rec_posY += velocity;
        DrawRectangle(win_width/2, rec_posY, rec_width, rec_height, BLUE);


        EndDrawing();
    }

    CloseWindow();
    
}