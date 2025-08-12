#pragma once
#include<raylib.h>

class player{
private:
    Texture2D image;
    Vector2 speed;
    float p_dmg, k_dmg, scale, groundY;
    bool facingRight, is_attacking, is_blocking, is_grounded;

    const float gravity= 600.0f;
    const float acceleration = 500.0f;
    const float deltaTime = 1.0f / 60.0f;
    const float jumpVelocity = -300.0f;
    float moveSpeed = 20.0f;       



public:
    Vector2 position;
    player();
    ~player();
    void draw();
    void gravity_on();
    void update();
    void punch();
    void kick();




};