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
    // Window
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper-Dasher");


    // Acceleration due to gravity (pixel/s)/s
    const int gravity{1'000};


    // Nebula variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    
    /*
    AnimData nebData
    { 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowDimensions[0], windowDimensions[1] - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };
    */


    // Array for nebula hazards
    AnimData nebulae[3]{};

    for(int i = 0; i < 3; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;

    // Nebula velocity (pixel/senconds)
    int nebulaVel{-200};


    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    int velocity{};
    int jumpVel{-600}; // Jump velocity (pixels/s)
    bool isInAir{};   // Is the rectangle in the air?


    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dt{GetFrameTime()};

        // Start drawing
        BeginDrawing();
        ClearBackground(WHITE);


        // Ground check
        if(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
        

        for (int i = 0; i < 3; i++)
        {
            // Update nebula position
            nebulae[i].pos.x += nebulaVel * dt;
        }

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


        for(int i = 0; i < 3; i++)
        {
            // Update nebula animation frame
            nebulae[i].runningTime += dt;

            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0;

                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width;
                nebulae[i].frame++;

                if(nebulae[i].frame > 7)
                    nebulae[i].frame = 0;
            }
        }
        
        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);


        // Draw hazards
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, WHITE);
        DrawTextureRec(nebula, nebulae[2].rec, nebulae[2].pos, WHITE);


        // End drawing
        EndDrawing();
    }


    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
    
}