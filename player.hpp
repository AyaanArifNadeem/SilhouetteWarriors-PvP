#pragma once
#include<raylib.h>

class player{
private:
    Rectangle hitbox, c_hitbox, l_hitbox, frameRec;

    KeyboardKey Jump, Left, Right, crouch;

    Texture2D image,running_anim,dash_anim;
    Vector2 speed;
    float health, p_dmg, k_dmg, scale, groundY, keyframe, L_input_times, R_input_times, Jumpheight, crouchdepth, crouch_y;
    bool facingRight, is_attacking, is_blocking, is_grounded, is_upright, is_moving, just_dashed, R_dash_allowed, L_dash_allowed;

    const float gravity= 900.0f;
    const float upwardsAcceleration = -900.0f;
    const float deltaTime = 1.0f / 60.0f;
    const float jumpVelocity = -500.0f;
    const float crouchVelocity = 600.0f;
    float moveSpeed = 10.0f;       

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 12; 

    int currentFrameDash = 0;
    int framesCounterDash = 0;
    int framesSpeedDash = 10; 

public:

    bool R_move_allowed, L_move_allowed, R_dash, L_dash;
    Vector2 position;
    
    player();
    
    void update_hitbox();
    void draw();
    void gravity_on();
    void update(player &p2);
    void setControls(KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right);    
    
    KeyboardKey GetJump();
    KeyboardKey GetCrouch();
    KeyboardKey GetLeft();
    KeyboardKey GetRight();
    KeyboardKey GetPunch();
    KeyboardKey GetKick();
    Rectangle GetHitbox();
    Rectangle GetCHitbox();
    Rectangle GetLHitbox();


    ~player();

};