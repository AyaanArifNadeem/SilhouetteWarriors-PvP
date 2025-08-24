#pragma once
#include<raylib.h>

class player{
private:
    Rectangle hitbox, c_hitbox, l_hitbox, p_hitbox, k_hitbox, frameRec;

    KeyboardKey Jump, Left, Right, crouch, Punch, Kick;

    Texture2D image, idle_block, running_anim,dash_anim, jump_anim, crouch_anim, punch_anim, kick_anim;
    Vector2 speed;
    float p_dmg, k_dmg, scale, groundY, keyframe, L_input_times, R_input_times, Jumpheight, crouchdepth, crouch_y;
    bool facingRight, is_punching, is_kicking, is_blocking, is_grounded, is_upright, is_moving, just_dashed, R_dash_allowed, L_dash_allowed, p_dmg_once, can_punch, k_dmg_once, can_kick;

    const float gravity= 1200.0f;
    const float upwardsAcceleration = -1200.0f;
    const float deltaTime = 1.0f / 60.0f;
    const float jumpVelocity = -500.0f;
    const float crouchVelocity = 500.0f;
    float moveSpeed = 10.0f;       

    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 12; 

    int currentFrameDash = 0;
    int framesCounterDash = 0;
    int framesSpeedDash = 10; 

    int currentFrameJump = 0;
    int framesCounterJump = 0;
    int framesSpeedJump = 8; 

    int currentFrameAtk = 0;
    int framesCounterAtk = 0;
    int framesSpeedAtk = 8; 

    int CFpun = 0, FCpun =0; 
    int CFkick = 0, FCkick = 0;

public:

    float health;
    bool R_move_allowed, L_move_allowed, R_dash, L_dash, can_block, is_alive, playpunchsfx, playkicksfx, playjumpsfx, playcrouchsfx, pausemove, blockbroken;
    char username[9] = {'P','l','a','y','e','r'};
    Vector2 position;
    
    player();
    
    void update_hitbox();
    void draw();
    void gravity_on();
    void update(player &p2);
    void setControls(KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right, KeyboardKey punch, KeyboardKey kick);    
    
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