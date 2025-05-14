#include "raylib.h"
#include "raymath.h"
#include "Character.h"

Character::Character(int windowWidth, int windowHeight){
    scarfy = LoadTexture("textures/scarfy.png");
    scarfyData.rec.width = scarfy.width / 6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimension[0] / 2 - scarfyData.rec.width / 2;
    scarfyData.pos.y = windowDimension[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;
}

Character::~Character(){
    UnloadTexture(scarfy);
}

void Character:: Update(float )

void Character::Jump(int JumVal){
    velocity += JumVal;
}

void Character :: Reset(int windowWidth, int windowHeight)

