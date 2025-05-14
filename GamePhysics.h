#include "raylib.h"
#include "raymath.h"
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


class GamePhysics{
    public:
        GamePhysics(){


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
            int nebulaRate{250};
            nebulae[i].pos.x = windowDimension[0] + i * nebulaRate;
        }

        }
    }

    private:
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

        //textures
        Texture2D nebula = LoadTexture("textures/nebula.png");
        Texture2D background = LoadTexture("textures/far-buildings.png");
        Texture2D midground = LoadTexture("textures/back-buildings.png");
        Texture2D foreground = LoadTexture("textures/foreground.png");
        // Initialize Nebulae (max 10)
        AnimData nebulae[10];
        float finishLine = 0;
        int nebVel = -230;

};