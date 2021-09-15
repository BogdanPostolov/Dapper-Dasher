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

bool IsOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData UpdateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update running time
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;

        // Update animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if(data.frame > maxFrame)
            data.frame = 0;
    }

    return data;

}

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


    const int sizeOfNebulae{6};  // How many nebula hazards 
    AnimData nebulae[sizeOfNebulae]{};      // Array for nebula hazards

    for(int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
    }

    int start{0};
    for(int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].pos.x = windowDimensions[0] + start;
        start += 300;
    }

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
        if(IsOnGround(scarfyData, windowDimensions[1]))
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
        

        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // Update nebula position
            nebulae[i].pos.x += nebulaVel * dt;
        }

        // Update scarfy position
        scarfyData.pos.y += velocity * dt;

        // Update scrafy animation frame
        if(!isInAir)
        {
            scarfyData = UpdateAnimData(scarfyData, dt, 5);
        }


        for(int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i] = UpdateAnimData(nebulae[i], dt, 7);
        }
        
        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);


        // Draw hazards
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
        }

        // End drawing
        EndDrawing();
    }


    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
    
}