#include "map4.hpp"
#include "player.hpp"
#include<raylib.h>

map4::map4(){
    c1 = LoadTexture("res/map4/clouds_1.png");
    c2 = LoadTexture("res/map4/clouds_2.png");
    c3 = LoadTexture("res/map4/clouds_3.png");
    g1 = LoadTexture("res/map4/rocks_3.png");
    g2 = LoadTexture("res/map4/rocks_2.png");
    g3 = LoadTexture("res/map4/rocks_1.png");
    sky = LoadTexture("res/map4/sky.png");

    scrollingMid = 0.0f;
    scrollingMid2 = 0.0f;
    scrollingMid3 = 0.0f;
    scrollingfront1 = 0.0f;
    scrollingfront2 = 0.0f;
    scrollingfront3 = 0.0f;
    flooroffset = 0.0f;

}

map4::~map4(){
    UnloadTexture(c1);
    UnloadTexture(c2);
    UnloadTexture(c3);
    UnloadTexture(g1);
    UnloadTexture(g2);
    UnloadTexture(g3);
    UnloadTexture(sky);
}

void map4::update(player &p1, player &p2){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    scrollingMid -= 0.4f;
    scrollingMid2 -= 0.5f;
    scrollingMid3 -= 0.6f;
    if (scrollingMid <= -c1.width) scrollingMid = ScreenWidth;
    if (scrollingMid2 <= -c2.width*0.75) scrollingMid2 = ScreenWidth;
    if (scrollingMid3 <= -c3.width*0.75) scrollingMid3 = ScreenWidth;

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

void map4::draw(){
    float ScreenWidth = GetScreenWidth(), ScreenHeight = GetScreenHeight();
    DrawTexturePro(sky,(Rectangle){0, 0, (float)sky.width, (float)sky.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);        
    DrawTextureEx(c1, (Vector2){ scrollingMid, 100 }, 0.0f, 1.0f, WHITE);
    DrawTextureEx(c1, (Vector2){ c1.width*2 + scrollingMid, 100 }, 0.0f, 1.0f, WHITE);
    DrawTexturePro(g1,(Rectangle){0, 0, (float)g1.width, (float)g1.height},(Rectangle){-70+scrollingfront1, -100, ScreenWidth+200, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTextureEx(c2, (Vector2){ scrollingMid2, -150 }, 0.0f, 0.8f, WHITE);
    DrawTextureEx(c2, (Vector2){ c2.width*2 + scrollingMid2, -150 }, 0.0f, 0.8f, WHITE);   
    DrawTextureEx(c3, (Vector2){ scrollingMid3, -150 }, 0.0f, 0.8f, WHITE);
    DrawTextureEx(c3, (Vector2){ c3.width*2 + scrollingMid3, -150 }, 0.0f, 0.8f, WHITE);
    DrawTexturePro(g2,(Rectangle){0, 0, (float)g2.width, (float)g2.height},(Rectangle){-350+scrollingfront2, -100, ScreenWidth+500, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
    DrawTexturePro(g3,(Rectangle){0, 0, (float)g3.width, (float)g3.height},(Rectangle){-350+scrollingfront3, -100, ScreenWidth+1300, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
}

