#include "player.hpp"
#include<raylib.h>

player::player(){
    image = LoadTexture("res/Base Sprite.png");
    position = {(float)GetScreenWidth()/4-200,400};
    speed = {900,0};
    p_dmg = 15,k_dmg = 30, scale = 0.1f, groundY = 900;
    facingRight = true;
    is_attacking = 0, is_blocking = 0, is_grounded = 0;
}

void player::draw(){
    Rectangle source = {0.0f, 0.0f, (float)image.width, (float)image.height};
    if (!facingRight) {source.width *= -1;}
    Rectangle destin = {position.x, position.y, (float)image.width*scale, (float)image.height*scale};
    
    DrawTexturePro(image,source,destin,{0.0f, 0.0f},0.0f,RAYWHITE);
}

void player::gravity_on(){
    if(!is_grounded){
        speed.y += gravity * deltaTime;
        position.y += speed.y * deltaTime;
    }

    if((position.y + (float)image.height*scale) > groundY){
        speed.y = 0;
        position.y = groundY - (float)image.height*scale;
    }
}

void player::update(){
    
    gravity_on();

    if (IsKeyDown(KEY_A) && position.x > 0){position.x -= speed.x * deltaTime;}
    else if(IsKeyDown(KEY_D) && position.x < 2500){position.x += speed.x * deltaTime;}

    if(IsKeyDown(KEY_W) && is_grounded){
        speed.y = jumpVelocity;
    }


    if(position.y >= GetScreenHeight() - (image.height * scale)) {is_grounded = true;}
    else {is_grounded = 0;}

    if(position.x > 2500) position.x = 2500;
    if(position.x < 0) position.x = 0;

}