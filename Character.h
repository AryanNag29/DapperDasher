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



class Character{
    public:
    Character(int windowWidth, int WindowHeight);

    ~Character();
    void Update(float deltaTime,bool isInAir);
    void Jump(int jumpVal);
    void Reset(int windowWidth, int windowHeight);

    AnimData getAnimData() const {return scarfyData};
    Vector2 getPos() const {return scarfyData.pos};
    Rectangle getCollisionRec() const;
    bool IsinGround(int windowHeight) const;

    private:
    Texture2D scarfy;
    // Initialize Scarfy
    AnimData scarfyData;
    int velocity{0};


};