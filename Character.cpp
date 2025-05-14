#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int windowWidth, int windowHeight){
    scarfy = LoadTexture("textures/scarfy.png");
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;
}

Character::~Character(){
    UnloadTexture(scarfy);
}

void Character:: Update(float deltaTime, bool isInAir){
 if (!isInAir)
    {
        scarfyData.runningTime += deltaTime;
        if (scarfyData.runningTime >= scarfyData.updateTime)
        {
            scarfyData.runningTime = 0.0f;
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame = (scarfyData.frame + 1) % 6;
        }
    }
    
    scarfyData.pos.y += velocity * deltaTime;
}

void Character::Jump(int JumpVal){
    velocity += JumpVal;
}

void Character :: Reset(int windowWidth, int windowHeight){
        //reset player pos
        scarfyData.pos.x = windowWidth / 2 - scarfyData.rec.width / 2;
        scarfyData.pos.y = windowHeight - scarfyData.rec.height;
        velocity = 0;
}

Rectangle Character:: getCollisionRec() const{
    return {scarfyData.pos.x, scarfyData.pos.y, scarfyData.rec.width, scarfyData.rec.height};
}

bool Character:: IsOnGround(int windowHeight)const
{
    return scarfyData.pos.y >= windowHeight - scarfyData.rec.height;
}

