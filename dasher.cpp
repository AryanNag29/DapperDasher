#include "raylib.h"
#include <math.h>

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame) data.frame = 0;
    }
    return data;
}

int main()
{
    // Window dimensions
    int windowDimension[2] = {512, 380};
    InitWindow(windowDimension[0], windowDimension[1], "Dapper Dasher");
    SetTargetFPS(60);

    // Game variables
    const int gravity = 1500;
    const int jumpVal = -600;
    int velocity = 0;
    bool isInAir = true;
    bool collision = false;
    bool gameOver = false;
    bool win = false;
    int level = 1;
    int nebulaCount = 3; // Start with 3 nebulae

    // Load textures
    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Texture2D nebula = LoadTexture("textures/nebula.png");

    // Initialize Scarfy
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimension[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimension[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // Initialize Nebulae (max 10)
    AnimData nebulae[10];
    float finishLine = 0;
    int nebVel = -230;

    // Function to initialize level
    auto initLevel = [&]() {
        for (int i = 0; i < nebulaCount; i++)
        {
            nebulae[i].rec.x = 0.0;
            nebulae[i].rec.y = 0.0;
            nebulae[i].rec.width = nebula.width / 8;
            nebulae[i].rec.height = nebula.height / 8;
            nebulae[i].pos.y = windowDimension[1] - nebula.height / 8;
            nebulae[i].frame = 0;
            nebulae[i].runningTime = 0.0;
            nebulae[i].updateTime = 1.0 / 16.0;
            nebulae[i].pos.x = windowDimension[0] + i * 300;
        }
        finishLine = nebulae[nebulaCount - 1].pos.x + 300;
        
        // Reset player
        scarfyData.pos.x = windowDimension[0] / 2 - scarfyData.rec.width / 2;
        scarfyData.pos.y = windowDimension[1] - scarfyData.rec.height;
        velocity = 0;
        isInAir = true;
        collision = false;
        win = false;
    };

    initLevel();

    // Background positions
    float bgX = 0, mgX = 0, fgX = 0;

    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        // Background drawing code (same as before)
        bgX -= 20 * dT;
        if (bgX <= -background.width * 2) bgX = 0.0;
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width * 2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        mgX -= 30 * dT;
        if (mgX <= -midground.width * 2) mgX = 0.0;
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        fgX -= 40 * dT;
        if (fgX <= -foreground.width * 2) fgX = 0.0;
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width * 2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        if (!gameOver && !win)
        {
            // Gameplay logic
            if (isOnGround(scarfyData, windowDimension[1]))
            {
                velocity = 0;
                isInAir = false;
            }
            else
            {
                velocity += gravity * dT;
                isInAir = true;
            }

            if (IsKeyPressed(KEY_SPACE) && !isInAir)
            {
                velocity += jumpVal;
            }

            scarfyData.pos.y += velocity * dT;

            // Update nebula positions
            for (int i = 0; i < nebulaCount; i++)
            {
                nebulae[i].pos.x += nebVel * dT;
            }
            finishLine += nebVel * dT;

            // Check collisions
            for (int i = 0; i < nebulaCount; i++)
            {
                float pad = 60.0;
                Rectangle nebRec{
                    nebulae[i].pos.x + pad,
                    nebulae[i].pos.y + pad,
                    nebulae[i].rec.width - 2 * pad,
                    nebulae[i].rec.height - 2 * pad};
                Rectangle scarfyRec{
                    scarfyData.pos.x,
                    scarfyData.pos.y,
                    scarfyData.rec.width,
                    scarfyData.rec.height};
                if (CheckCollisionRecs(nebRec, scarfyRec))
                {
                    collision = true;
                }
            }

            // Check win condition
            if (scarfyData.pos.x >= finishLine)
            {
                win = true;
            }
        }

        if (collision)
        {
            gameOver = true;
            DrawText("Game Over", windowDimension[0]/2 - 75, windowDimension[1]/2, 40, RED);
            DrawText("Press R to Restart", windowDimension[0]/2 - 100, windowDimension[1]/2 + 50, 20, RED);
            
            if (IsKeyPressed(KEY_R))
            {
                nebulaCount = 3;
                level = 1;
                initLevel();
                gameOver = false;
            }
        }
        else if (win)
        {
            DrawText("Level Complete!", windowDimension[0]/2 - 100, windowDimension[1]/2, 40, BLUE);
            DrawText(TextFormat("Level: %d", level), windowDimension[0]/2 - 50, windowDimension[1]/2 + 50, 30, BLUE);
            DrawText("Press SPACE to Continue", windowDimension[0]/2 - 120, windowDimension[1]/2 + 100, 20, BLUE);
            
            if (IsKeyPressed(KEY_SPACE))
            {
                level++;
                nebulaCount++;
                if (nebulaCount > 10) nebulaCount = 10;
                nebVel -= 10; // Make game faster each level
                initLevel();
            }
        }
        else
        {
            // Draw game elements
            for (int i = 0; i < nebulaCount; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }

        // Animation updates
        if (!isInAir && !gameOver && !win)
        {
            scarfyData = updateAnimData(scarfyData, dT, 5);
        }

        for (int i = 0; i < nebulaCount; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], dT, 7);
        }

        // Draw level info
        DrawText(TextFormat("Level: %d", level), 10, 10, 20, BLACK);

        EndDrawing();
    }

    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    return 0;
}