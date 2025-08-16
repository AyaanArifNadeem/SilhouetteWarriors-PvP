#include "player.hpp"
#include<raylib.h>

player::player(){
    image = LoadTexture("res/bs.png");
    running_anim = LoadTexture("res/ra.png");
    frameRec = { 0.0f, 0.0f, (float)running_anim.width/8, (float)running_anim.height};
    position = {(float)GetScreenWidth()/4-200,400};
    speed = {900,0};
    p_dmg = 15,k_dmg = 30, scale = 0.13f, groundY =220, keyframe = 200;
    facingRight = true;
    is_attacking = 0, is_blocking = 0, is_grounded = 0, is_moving = 0;
    update_hitbox();
}


void player::setControls(KeyboardKey up, KeyboardKey down, KeyboardKey left, KeyboardKey right){
    Jump = up, crouch = down, Left = left, Right = right;
}


void player::update_hitbox(){
    hitbox = {position.x , position.y, (float)image.width*scale, (float)image.height*scale};
}


void player::draw(){
    Rectangle source;
    Rectangle destin = {position.x, position.y, (float)image.width*scale, (float)image.height*scale};

    if(!is_moving){
        source = {0.0f, 0.0f, (float)image.width, (float)image.height};
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(image,source,destin,{0.0f, 0.0f},0.0f,RAYWHITE);
    }else if(is_moving){
        source = {200.0f*currentFrame, 0.0f, (float)running_anim.width/8, (float)running_anim.height};
        if (!facingRight) {source.width *= -1;}
        DrawTexturePro(running_anim,source,destin,{0.0f, 0.0f}, 0.0f, RAYWHITE);
    }

    
    DrawRectangleLinesEx(hitbox,2.0f,RED);
}


void player::gravity_on(){
    if(!is_grounded){
        speed.y += gravity * deltaTime;
        position.y += speed.y * deltaTime;
    }

    if((position.y > groundY - (float)image.height*scale)){
        position.y = groundY - (float)image.height*scale;
        speed.y = 0;
    }
}


void player::update(){
    framesCounter++;
    is_moving = 0;
    is_grounded = 0;
    gravity_on();

    if (framesCounter >= (60/framesSpeed)){
        framesCounter = 0;
        currentFrame++;
        if (currentFrame > 7) currentFrame = 0;
        frameRec.x = (float)currentFrame*(float)running_anim.width/8;
    }

    if((IsKeyDown(Left)  && !IsKeyDown(Right)) && position.x > 0){position.x -= speed.x * deltaTime;is_moving=1;}
    else if((IsKeyDown(Right) && !IsKeyDown(Left)) && position.x < 2500){position.x += speed.x * deltaTime;is_moving=1;}

    if(position.y >= groundY - (image.height * scale)){is_grounded = true;}
    if(IsKeyPressed(Jump) && is_grounded){speed.y = jumpVelocity;}

    update_hitbox();
    
    position.y += speed.y * deltaTime;
    if(position.x > 2500) position.x = 2500;
    if(position.x < 0) position.x = 0;
}

KeyboardKey player::GetJump(){return Jump;}
KeyboardKey player::GetCrouch(){return crouch;}
KeyboardKey player::GetLeft(){return Left;}
KeyboardKey player::GetRight(){return Right;}

player::~player(){UnloadTexture(image);}