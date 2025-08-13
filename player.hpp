#pragma once
#include<raylib.h>

class player{
private:
    Rectangle hitbox;
    Rectangle frameRec;

    Texture2D image,running_anim;
    Vector2 speed;
    float p_dmg, k_dmg, scale, groundY, keyframe;
    bool facingRight, is_attacking, is_blocking, is_grounded, is_moving;

    const float gravity= 600.0f;
    const float acceleration = 500.0f;
    const float deltaTime = 1.0f / 60.0f;
    const float jumpVelocity = -300.0f;
    float moveSpeed = 10.0f;       

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 12; 


public:
    Vector2 position;
    player();
    ~player();
    void update_hitbox();
    void draw();
    void gravity_on();
    void update();
    void punch();
    void kick();




};