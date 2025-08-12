#include "map2.hpp"
#include "player.hpp"
#include<raylib.h>

map2::map2(){
    c1 = LoadTexture("res/map2/clouds_1.png");
    c2 = LoadTexture("res/map2/clouds_2.png");
    g1 = LoadTexture("res/map2/ground.png");
    rocks = LoadTexture("res/map2/rocks.png");
    sky = LoadTexture("res/map2/sky.png");

    scrollingMid = 0.0f;
    scrollingMid2 = 0.0f;
    scrollingfront1 = 0.0f;
    flooroffset = 0.0f;

}

map2::~map2(){
    UnloadTexture(c1);
    UnloadTexture(c2);
    UnloadTexture(g1);
    UnloadTexture(rocks);
    UnloadTexture(sky);
}

void map2::update(player &p1, Rectangle &enemy){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    scrollingMid -= 0.4f;
    scrollingMid2 -= 0.5f;
    if (scrollingMid <= -c1.width) scrollingMid = ScreenWidth;
    if (scrollingMid2 <= -c2.width*0.75) scrollingMid2 = ScreenWidth;

    if (IsKeyDown(KEY_D) && p1.position.x < 2500){ 
            scrollingfront1 -= 0.5;
        }
        else if (IsKeyDown(KEY_A) && p1.position.x > 0){ 
            scrollingfront1 += 0.5;
        }

        if (IsKeyDown(KEY_RIGHT) && enemy.x < 2500){ 
            enemy.x += 15;
            scrollingfront1 -= 0.5;
        }
        else if (IsKeyDown(KEY_LEFT) && enemy.x > 0){ 
            enemy.x -= 15;
            scrollingfront1 += 0.5;
        }

        
        if(enemy.x < 0) enemy.x=0;
        if(enemy.x > 2500) enemy.x=2500;
}

void map2::draw(){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    DrawTexturePro(sky,(Rectangle){0, 0, (float)sky.width, (float)sky.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);        
    DrawTextureEx(c1, (Vector2){ scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(c1, (Vector2){ c1.width*2 + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
    DrawTexturePro(rocks,(Rectangle){0, 0, (float)rocks.width, (float)rocks.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTexturePro(g1,(Rectangle){0, 0, (float)g1.width, (float)g1.height},(Rectangle){-70+scrollingfront1, -100, ScreenWidth+200, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTextureEx(c2, (Vector2){ scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
    DrawTextureEx(c2, (Vector2){ c2.width*2 + scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
}