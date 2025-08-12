#include<iostream>
#include<raylib.h>
#include<cmath>
#include "player.hpp"
using namespace std;

int main(){
    const int ScreenWidth = 1920, ScreenHeight = 1080;
    Rectangle enemy =  {(2500/2)-200, 450, 200, 450};

    InitWindow(ScreenWidth,ScreenHeight,"SilhouetteWarriors-PvP");

    player p1; 

    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((p1.position.x + enemy.x+200)/2.0f), ((p1.position.y + enemy.y)/2.0f) };
    camera.offset = (Vector2){ ScreenWidth/2.0f, ScreenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    SetTargetFPS(60);

    Texture2D Background = LoadTexture("res/bgfull.png");
    Texture2D c1 = LoadTexture("res/layers/clouds_1.png");
    Texture2D c2 = LoadTexture("res/layers/clouds_2.png");
    Texture2D g1 = LoadTexture("res/layers/ground_1.png");
    Texture2D g2 = LoadTexture("res/layers/ground_2.png");
    Texture2D g3 = LoadTexture("res/layers/ground_3.png");
    Texture2D rocks = LoadTexture("res/layers/rocks.png");
    Texture2D sky = LoadTexture("res/layers/sky.png");

    float scrollingMid = 0.0f;
    float scrollingMid2 = 0.0f;
    float scrollingfront1 = 0.0f;
    float scrollingfront2 = 0.0f;
    float scrollingfront3 = 0.0f;
    float flooroffset = 0.0f;

    while(!WindowShouldClose()){
        


        //Clouds Control
        scrollingMid -= 0.4f;
        scrollingMid2 -= 0.5f;
        if (scrollingMid <= -c1.width) scrollingMid = ScreenWidth;
        if (scrollingMid2 <= -c2.width*0.75) scrollingMid2 = ScreenWidth;



        //Camera Work
        camera.target = (Vector2){ ((p1.position.x + enemy.x+200)/2.0f), ((p1.position.y + enemy.y)/2.0f) };
        if(fabs(p1.position.x-enemy.x) > 1720){
            camera.zoom = 1.646 - 0.000375*(fabs(p1.position.x-enemy.x));
            flooroffset =  ((fabs(p1.position.x-enemy.x))-1720)*0.160256f;
        }
        else{camera.zoom = 1.0f; flooroffset = 0.0f;}

        if (camera.zoom > 1.0f) camera.zoom = 1.0f;
        else if (camera.zoom < 0.7f) camera.zoom = 0.7f;



        //Parallex Effect Code
        //Placeholder Characters Control
        if(enemy.x < 0) enemy.x=0;
        if(enemy.x > 2500) enemy.x=2500;

        if (IsKeyDown(KEY_D) && p1.position.x < 2500){ 
            scrollingfront3 -= 2;
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if (IsKeyDown(KEY_A) && p1.position.x > 0){ 
            scrollingfront3 += 2;
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

        if (IsKeyDown(KEY_RIGHT) && enemy.x < 2500){ 
            enemy.x += 15;
            scrollingfront3 -= 2;
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if (IsKeyDown(KEY_LEFT) && enemy.x > 0){ 
            enemy.x -= 15;
            scrollingfront3 += 2;
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

       
        p1.update();
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //Textures
        DrawTexturePro(sky,(Rectangle){0, 0, (float)sky.width, (float)sky.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);        
        DrawTextureEx(c1, (Vector2){ scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(c1, (Vector2){ c1.width*2 + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
        DrawTexturePro(rocks,(Rectangle){0, 0, (float)rocks.width, (float)rocks.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
        DrawTexturePro(g1,(Rectangle){0, 0, (float)g1.width, (float)g1.height},(Rectangle){-70+scrollingfront1, -100, ScreenWidth+200, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
        DrawTextureEx(c2, (Vector2){ scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
        DrawTextureEx(c2, (Vector2){ c2.width*2 + scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
        DrawTexturePro(g2,(Rectangle){0, 0, (float)g2.width, (float)g2.height},(Rectangle){-350+scrollingfront2, -100, ScreenWidth+500, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
        DrawTexturePro(g3,(Rectangle){0, 0, (float)g3.width, (float)g3.height},(Rectangle){-350+scrollingfront3, -100, ScreenWidth+1300, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);

        //Live Player Positon Information
        DrawText(TextFormat("Pos: %f", p1.position.x), 100, 100, 50, RED);
        DrawText(TextFormat("Pos: %f", enemy.x), 100, 200, 50, BLUE);
        DrawRectangle(-1000, 975.0f-(flooroffset), 5000, 3000, BLACK);



        BeginMode2D(camera);   

            DrawRectangleRec(enemy, BLUE);
            p1.draw();

        EndMode2D();


        EndDrawing();
    }


    //Unload Textures
    UnloadTexture(Background);
    UnloadTexture(c1);
    UnloadTexture(c2);
    UnloadTexture(g1);
    UnloadTexture(g2);
    UnloadTexture(g3);
    UnloadTexture(rocks);
    UnloadTexture(sky);
    CloseWindow();


    
    return 0;
}