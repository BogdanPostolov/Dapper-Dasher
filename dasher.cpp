#include <iostream>
#include "raylib.h"

int main()
{
    // Window size
    const int win_width{512};
    const int win_height{380};

    // Window
    InitWindow(win_width, win_height, "Dapper-Dasher");

    // Acceleration due to gravity (pixel/s)/s
    const int gravity{1'000};


    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    
    Vector2 scarfyPos;
    scarfyPos.x = win_width/2 - scarfyRec.width/2;
    scarfyPos.y = win_height - scarfyRec.height;


    int velocity{};

    // Jump velocity (pixels/s)
    int jumpVel{-600};
    
    // Is the rectangle in the air?
    bool isInAir{};

    // Animation frame
    int frame{};

    // Amount of time before updateing the animation frame
    const float updateTime{1.0 / 12.0};
    float runningTime{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dt{GetFrameTime()};

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);


        // Ground check
        if(scarfyPos.y >= win_height - scarfyRec.height)
        {
            // Rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // Rectangle is in the air
            velocity += gravity * dt;
            isInAir = true;
        }


        // Check for jumping
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
            velocity += jumpVel;
        

        // Update Y position of the rectangle
        scarfyPos.y += velocity * dt;

        // Update running time
        runningTime += dt;

        if (runningTime >= updateTime)
        {
            runningTime = 0.0;

            // Update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;

            if(frame > 5)
                frame = 0;
        }
        

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);


        EndDrawing();
    }

    UnloadTexture(scarfy);
    CloseWindow();
    
}