#include <iostream>
#include "raylib.h"


struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    // Window size
    const int win_width{512};
    const int win_height{380};


    // Window
    InitWindow(win_width, win_height, "Dapper-Dasher");

    // Acceleration due to gravity (pixel/s)/s
    const int gravity{1'000};


    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    AnimData nebData
    { 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {win_width, win_height - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };

    AnimData neb2Data
    { 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {win_width + 300, win_height - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/16.0, // float updateTime
        0.0 // float runningTime
    };

    // Nebula velocity (pixel/senconds)
    int nebulaVel{-200};


    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = win_width/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = win_height - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    int velocity{};

    // Jump velocity (pixels/s)
    int jumpVel{-600};
    
    // Is the rectangle in the air?
    bool isInAir{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dt{GetFrameTime()};

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);


        // Ground check
        if(scarfyData.pos.y >= win_height - scarfyData.rec.height)
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
        

        // Update nebula position
        nebData.pos.x += nebulaVel * dt;

        // Update nebula2 position
        neb2Data.pos.x += nebulaVel * dt;

        // Update scarfy position
        scarfyData.pos.y += velocity * dt;

        // Update scrafy animation frame
        if(!isInAir)
        {
            // Update running time
            scarfyData.runningTime += dt;

            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;

                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;

                if(scarfyData.frame > 5)
                    scarfyData.frame = 0;
            }
        }


        // Update nebula animation frame
        nebData.runningTime += dt;

        if (nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;

            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;

            if(nebData.frame > 7)
                nebData.frame = 0;
        }


        // Update nebula animation frame
        neb2Data.runningTime += dt;

        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;

            neb2Data.rec.x = nebData.frame * neb2Data.rec.width;
            neb2Data.frame++;

            if(neb2Data.frame > 7)
                neb2Data.frame = 0;
        }
        

        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Draw nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        // Draw nebula2
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);


        // End drawing
        EndDrawing();
    }


    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
    
}