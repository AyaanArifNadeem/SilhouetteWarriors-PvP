#include "map1.hpp"
#include "player.hpp"
#include<raylib.h>

map1::map1(){
    c1 = LoadTexture("res/map1/clouds_1.png");
    c2 = LoadTexture("res/map1/clouds_2.png");
    g1 = LoadTexture("res/map1/ground_1.png");
    g2 = LoadTexture("res/map1/ground_2.png");
    g3 = LoadTexture("res/map1/ground_3.png");
    rocks = LoadTexture("res/map1/rocks.png");
    sky = LoadTexture("res/map1/sky.png");

    scrollingMid = 0.0f;
    scrollingMid2 = 0.0f;
    scrollingfront1 = 0.0f;
    scrollingfront2 = 0.0f;
    scrollingfront3 = 0.0f;
    flooroffset = 0.0f;

}

map1::~map1(){
    UnloadTexture(c1);
    UnloadTexture(c2);
    UnloadTexture(g1);
    UnloadTexture(g2);
    UnloadTexture(g3);
    UnloadTexture(rocks);
    UnloadTexture(sky);
}

void map1::update(player &p1, player &p2){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    scrollingMid -= 0.4f;
    scrollingMid2 -= 0.5f;
    if (scrollingMid <= -c1.width) scrollingMid = ScreenWidth;
    if (scrollingMid2 <= -c2.width*0.75) scrollingMid2 = ScreenWidth;

    if((p1.R_dash || p2.R_dash)){
        scrollingfront3 -= 2*18;
        scrollingfront2 -= 1*18;
        scrollingfront1 -= 0.5*18;
    }

    if((p1.L_dash || p2.L_dash)){
        scrollingfront3 += 2*18;
        scrollingfront2 += 1*18;
        scrollingfront1 += 0.5*18;
    }

    if ((IsKeyDown(p1.GetRight()) && !IsKeyDown(p1.GetLeft())) && p1.R_move_allowed){ 
            scrollingfront3 -= 2;
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if ((IsKeyDown(p1.GetLeft())  && !IsKeyDown(p1.GetRight())) && p1.L_move_allowed){ 
            scrollingfront3 += 2;
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

        if ((IsKeyDown(p2.GetRight()) && !IsKeyDown(p2.GetLeft())) && p2.R_move_allowed){ 
            scrollingfront3 -= 2;
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if ((IsKeyDown(p2.GetLeft())  && !IsKeyDown(p2.GetRight())) && p2.L_move_allowed){ 
            scrollingfront3 += 2;
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

    }

void map1::draw(){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    DrawTexturePro(sky,(Rectangle){0, 0, (float)sky.width, (float)sky.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);        
    DrawTextureEx(c1, (Vector2){ scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(c1, (Vector2){ c1.width*2 + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
    DrawTexturePro(rocks,(Rectangle){0, 0, (float)rocks.width, (float)rocks.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTexturePro(g1,(Rectangle){0, 0, (float)g1.width, (float)g1.height},(Rectangle){-70+scrollingfront1, -100, ScreenWidth+200, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTextureEx(c2, (Vector2){ scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
    DrawTextureEx(c2, (Vector2){ c2.width*2 + scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
    DrawTexturePro(g2,(Rectangle){0, 0, (float)g2.width, (float)g2.height},(Rectangle){-350+scrollingfront2, -100, ScreenWidth+500, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTexturePro(g3,(Rectangle){0, 0, (float)g3.width, (float)g3.height},(Rectangle){-350+scrollingfront3, -100, ScreenWidth+1300, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
}

