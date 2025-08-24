#include "map3.hpp"
#include "player.hpp"
#include<raylib.h>

map3::map3(){
    g1 = LoadTexture("res/map3/background3.png");
    g2 = LoadTexture("res/map3/background4a.png");
    rocks = LoadTexture("res/map3/background2.png");
    sky = LoadTexture("res/map3/background1.png");

    scrollingfront1 = 0.0f;
    scrollingfront2 = 0.0f;
    flooroffset = 0.0f;

}

map3::~map3(){
    UnloadTexture(g1);
    UnloadTexture(g2);
    UnloadTexture(rocks);
    UnloadTexture(sky);
}

void map3::update(player &p1, player &p2){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();

    if((p1.R_dash || p2.R_dash)){
        scrollingfront2 -= 1*18;
        scrollingfront1 -= 0.5*18;
    }

    if((p1.L_dash || p2.L_dash)){
        scrollingfront2 += 1*18;
        scrollingfront1 += 0.5*18;
    }

    if ((IsKeyDown(p1.GetRight()) && !IsKeyDown(p1.GetLeft())) && p1.R_move_allowed){ 
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if ((IsKeyDown(p1.GetLeft())  && !IsKeyDown(p1.GetRight())) && p1.L_move_allowed){ 
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

        if ((IsKeyDown(p2.GetRight()) && !IsKeyDown(p2.GetLeft())) && p2.R_move_allowed){ 
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if ((IsKeyDown(p2.GetLeft())  && !IsKeyDown(p2.GetRight())) && p2.L_move_allowed){ 
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

    }

void map3::draw(){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    DrawTexturePro(sky,(Rectangle){0, 0, (float)sky.width, (float)sky.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);        
    DrawTexturePro(rocks,(Rectangle){0, 0, (float)rocks.width, (float)rocks.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTexturePro(g1,(Rectangle){0, 0, (float)g1.width, (float)g1.height},(Rectangle){-70+scrollingfront1, -100, ScreenWidth+200, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTexturePro(g2,(Rectangle){0, 0, (float)g2.width, (float)g2.height},(Rectangle){-350+scrollingfront2, -100, ScreenWidth+500, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
}

