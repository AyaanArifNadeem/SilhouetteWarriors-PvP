#include "player.hpp"
#include<raylib.h>

player::player(){
    image = LoadTexture("res/bs.png");
    running_anim = LoadTexture("res/ra.png");
    dash_anim = LoadTexture("res/da.png");
    jump_anim = LoadTexture("res/ja.png");
    crouch_anim = LoadTexture("res/caa.png");
    idle_block = LoadTexture("res/b.png");
    punch_anim = LoadTexture("res/pa.png");
    frameRec = { 0.0f, 0.0f, (float)running_anim.width/8, (float)running_anim.height};
    position = {(float)GetScreenWidth()/4-200,400};
    speed = {900,0};
    health = 200, p_dmg = 10,k_dmg = 20, scale = 0.13f, groundY =220, keyframe = 200, Jumpheight = 0, crouchdepth = 0, crouch_y = 0;
    facingRight = true;
    is_punching = 0, is_blocking = 0, is_grounded = 0, is_upright = 0, is_moving = 0, just_dashed = 0, R_dash_allowed = 1, L_dash_allowed = 1, can_punch = 1;
}


void player::setControls(KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right, KeyboardKey punch){
    Jump = up, crouch = down, Left = left, Right = right, Punch = punch;
}


void player::update_hitbox(){
    hitbox = {position.x , position.y, (float)image.width*scale, (float)image.height*scale};
    if(facingRight){
        c_hitbox = {position.x + 50.0f, position.y + 80.0f + crouchdepth, (float)image.width*scale- 130.0f, ((float)image.height*scale/2.0f)-80.0f - crouchdepth};
        l_hitbox = {position.x + 40.0f , position.y + ((float)image.height*scale)/2.0f, (float)image.width*scale - 100.0f, (float)image.height*scale/2.0f + Jumpheight};
        p_hitbox = {c_hitbox.x + c_hitbox.width, c_hitbox.y, ((hitbox.x + hitbox.width)-(c_hitbox.x + c_hitbox.width)), c_hitbox.height};
    }else if(!facingRight){
        c_hitbox = {position.x + 80.0f, position.y + 80.0f + crouchdepth, (float)image.width*scale- 130.0f, ((float)image.height*scale/2.0f)-80.0f - crouchdepth};
        l_hitbox = {position.x + 60.0f , position.y + ((float)image.height*scale)/2.0f, (float)image.width*scale - 100.0f, (float)image.height*scale/2.0f + Jumpheight};
        p_hitbox = {hitbox.x, c_hitbox.y, c_hitbox.x - hitbox.x, c_hitbox.height};
    }
}


void player::draw(){
    Rectangle source;
    Rectangle destin = {position.x, position.y, (float)image.width*scale, (float)image.height*scale};

    if(!is_upright){
        source = {200.0f*currentFrameJump, 0.0f, (float)crouch_anim.width/8, (float)crouch_anim.height};;
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(crouch_anim,source,destin,{0.0f, 0.0f},0.0f,RAYWHITE);
    }else if(!is_grounded){
        source = {200.0f*currentFrameJump, 0.0f, (float)jump_anim.width/8, (float)jump_anim.height};
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(jump_anim,source,destin,{0.0f, 0.0f}, 0.0f, RAYWHITE);
    }else if(is_punching){
        source = {200.0f*currentFrameJump, 0.0f, (float)punch_anim.width/8, (float)punch_anim.height};
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(punch_anim,source,destin,{0.0f, 0.0f}, 0.0f, RAYWHITE);
    }else if(just_dashed){
        source = {200.0f*currentFrameDash, 0.0f, (float)dash_anim.width/8, (float)dash_anim.height};
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(dash_anim,source,destin,{0.0f, 0.0f}, 0.0f, RAYWHITE);
    }else if(!is_moving){
        if(is_blocking){
            source = {0.0f, 0.0f, (float)idle_block.width, (float)idle_block.height};
            if (!facingRight) {source.width *= -1;}
            DrawTexturePro(idle_block,source,destin,{0.0f, 0.0f},0.0f,RAYWHITE);
        }else if(!is_blocking){
            source = {0.0f, 0.0f, (float)image.width, (float)image.height};
            if (!facingRight) {source.width *= -1;}
            DrawTexturePro(image,source,destin,{0.0f, 0.0f},0.0f,RAYWHITE);
        }
    }else if(is_moving){
        source = {200.0f*currentFrame, 0.0f, (float)running_anim.width/8, (float)running_anim.height};
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(running_anim,source,destin,{0.0f, 0.0f}, 0.0f, RAYWHITE);
    }    

    DrawText(TextFormat("%d", (int)health), hitbox.x, hitbox.y - 50, 50, RED);
    
    if(IsKeyDown(KEY_LEFT_CONTROL)){ 
    DrawRectangleLinesEx(hitbox,2.0f,RED);
    DrawRectangleLinesEx(c_hitbox,2.0f,BLUE);
    DrawRectangleLinesEx(l_hitbox,2.0f,PURPLE);
    DrawRectangleLinesEx(p_hitbox, 2.0f, GREEN);
    }
}


void player::gravity_on(){
    if(!is_grounded){
        speed.y += gravity * deltaTime;
        Jumpheight += speed.y * deltaTime;
    }

    if(!is_upright){
        crouch_y += upwardsAcceleration * deltaTime;
        crouchdepth += crouch_y * deltaTime;
    }

    if((Jumpheight > 0)){
        Jumpheight = 0;
        speed.y = 0;
    }

    if(crouchdepth < 0){
        crouchdepth = 0;
        crouch_y = 0;
    }
    
    if((position.y > groundY - (float)image.height*scale)){
        position.y = groundY - (float)image.height*scale;
    }
}


void player::update(player &p2){

//General Updates
    is_blocking = (facingRight && IsKeyDown(Left)) || (!facingRight && IsKeyDown(Right)) ?  1 : 0;
    if(is_punching || !is_grounded || !is_upright){is_blocking = 0;}
    R_dash = 0, L_dash = 0, is_moving = 0;
    framesCounter++;framesCounterDash++;framesCounterJump++; FCpun++;
    gravity_on();

    if(!can_punch && FCpun >= 60/8){
        FCpun = 0;
        CFpun++;
        if(CFpun > 13){CFpun = 0; can_punch = 1;}
    }

//Movement Frames
    //Movement
    if (framesCounter >= (60/framesSpeed)){
        framesCounter = 0;
        currentFrame++;
        if (currentFrame > 7) currentFrame = 0;
        frameRec.x = (float)currentFrame*(float)running_anim.width/8;
    }

    //Dash
    if(just_dashed && (framesCounterDash >= (60/framesSpeedDash))){
        framesCounterDash = 0;
        currentFrameDash++;
        if (currentFrameDash > 7) {just_dashed = 0;currentFrameDash = 0;}
        frameRec.x = (float)currentFrameDash*(float)dash_anim.width/8;
    }

    //Jump and Crouch
    if(is_grounded && is_upright && !is_punching){currentFrameJump = 0;}
    if((!is_grounded || !is_upright || is_punching) && (framesCounterJump >= (60/framesSpeedJump))){
        framesCounterJump = 0;
        currentFrameJump++;
        if (currentFrameJump > 7) {is_punching =0, p_dmg_once=0, currentFrameJump = 0;}
        frameRec.x = (float)currentFrameJump*(float)jump_anim.width/8;
    }

//Direction
    if(position.x < p2.position.x){facingRight = 1;}
    else{facingRight = 0;}


//Collision
    if((position.x < p2.position.x) && ((CheckCollisionRecs(hitbox,p2.hitbox)) && ((position.x+hitbox.width)-p2.position.x) >= 170.0f)){position.x = p2.position.x-170.0f;}
    if(position.x < 2500.0f && position.x != p2.position.x-170.0f){ R_move_allowed = 1;}else{R_move_allowed = 0;}
    if(position.x > 0.0f && position.x != p2.position.x+170.0f){ L_move_allowed = 1;}else{L_move_allowed = 0;}


//Movement
    //Movement allowed Check
    if(!is_grounded || !is_upright || is_punching){L_move_allowed = 0; R_move_allowed = 0, R_dash_allowed = 0, L_dash_allowed = 0;}
    //Dash
    if(!CheckCollisionRecs(hitbox, p2.hitbox)){L_input_times = 0; R_input_times = 0;}
    else{
        if((position.x < p2.position.x && p2.position.x < 2240.0f) && R_dash_allowed){
            if(IsKeyPressed(Right)){R_input_times++;}
            if(R_input_times == 3.0){position.x = p2.position.x + p2.hitbox.width; R_input_times = 0; R_dash = 1;just_dashed = 1;}
        }
        if((position.x > p2.position.x && position.x > 260.0f) && L_dash_allowed){
            if(IsKeyPressed(Left)){L_input_times++;}
            if(L_input_times == 3.0){position.x = p2.position.x - hitbox.width; L_input_times = 0; L_dash = 1;just_dashed = 1;}
        }
    }
    //Regular
    if((IsKeyDown(Left)  && !IsKeyDown(Right)) && L_move_allowed){position.x -= speed.x * deltaTime;is_moving=1;}
    if((IsKeyDown(Right) && !IsKeyDown(Left)) && R_move_allowed){position.x += speed.x * deltaTime;is_moving=1;}
    

    if(((l_hitbox.y + l_hitbox.height) >= groundY) && (c_hitbox.y <= -285.0f) && !is_punching){R_dash_allowed = 1, L_dash_allowed = 1;}
//Jump
    if((l_hitbox.y + l_hitbox.height) >= groundY){is_grounded = 1;}else{is_grounded = 0;}
    if(IsKeyPressed(Jump) && is_grounded && is_upright && !IsKeyDown(crouch) && !is_punching){speed.y = jumpVelocity;}
    Jumpheight += speed.y * deltaTime;

//Crouch
    if(c_hitbox.y <= -285.0f){is_upright = 1;}else{is_upright  = 0;}
    if(IsKeyPressed(crouch) && is_upright && is_grounded && !IsKeyDown(Jump) && !is_punching){crouch_y = crouchVelocity;}
    crouchdepth += crouch_y * deltaTime;


//Punch
    if(IsKeyPressed(Punch) && is_grounded && is_upright && can_punch){is_punching = true; can_punch = 0;}
    if(is_punching){
        R_dash_allowed = 0, L_dash_allowed = 0;
        if(CheckCollisionRecs(p_hitbox,p2.c_hitbox) && !p_dmg_once && !p2.is_blocking && p2.is_upright){p2.health -= p_dmg; p_dmg_once = 1;}
    }

    update_hitbox();


//Clamping
    if(p2.position.x == 2500.0f && position.x > 2330.0f) position.x = 2330.0f;
    if(p2.position.x == 0.0f && position.x < 170.0f) position.x = 170.0f;
    if(position.x > 2500) position.x = 2500;
    if(position.x < 0) position.x = 0;
}


//Getters
Rectangle player::GetHitbox(){return hitbox;}
Rectangle player::GetCHitbox(){return c_hitbox;}
Rectangle player::GetLHitbox(){return l_hitbox;}
KeyboardKey player::GetJump(){ return Jump;}
KeyboardKey player::GetCrouch(){return crouch;}
KeyboardKey player::GetLeft(){return Left;}
KeyboardKey player::GetRight(){return Right;}


player::~player(){
    UnloadTexture(image);
    UnloadTexture(running_anim);
    UnloadTexture(dash_anim);
    UnloadTexture(jump_anim);
    UnloadTexture(crouch_anim);
    UnloadTexture(idle_block);
    UnloadTexture(punch_anim);
}