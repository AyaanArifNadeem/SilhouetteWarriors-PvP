#include<iostream>
#include<raylib.h>
#include<cmath>
#include "player.hpp"
#include "map1.hpp"
#include "map2.hpp"
using namespace std;

int main(){
    const int ScreenWidth = 1920, ScreenHeight = 1080;
    InitWindow(ScreenWidth,ScreenHeight,"SilhouetteWarriors-PvP");


//Entity Decleration
    Rectangle enemy =  {(2500/2)-200, 450, 200, 450};
    player p1; 
    map1 m1;


//Camera Setup
    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((p1.position.x + enemy.x+200)/2.0f), ((p1.position.y + enemy.y)/2.0f) };
    camera.offset = (Vector2){ ScreenWidth/2.0f, ScreenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    SetTargetFPS(60);


    while(!WindowShouldClose()){
//UPDATE
        m1.update(p1, enemy); 
        p1.update();


//Camera Work
        camera.target = (Vector2){ ((p1.position.x + enemy.x+200)/2.0f), ((p1.position.y + enemy.y)/2.0f) };
        if(fabs(p1.position.x-enemy.x) > 1720){
            camera.zoom = 1.646 - 0.000375*(fabs(p1.position.x-enemy.x));
            m1.flooroffset =  ((fabs(p1.position.x-enemy.x))-1720)*0.160256f;
        }else{camera.zoom = 1.0f; m1.flooroffset = 0.0f;}
        if (camera.zoom > 1.0f) camera.zoom = 1.0f;
        if (camera.zoom < 0.7f) camera.zoom = 0.7f;
       

//DRAW
        BeginDrawing();
            ClearBackground(RAYWHITE);

            m1.draw();
            DrawText(TextFormat("Pos: %f", p1.position.x), 100, 100, 50, RED);
            DrawText(TextFormat("Pos: %f", enemy.x), 100, 200, 50, BLUE);
            DrawRectangle(-1000, 975.0f-(m1.flooroffset), 5000, 3000, BLACK);


            BeginMode2D(camera);   

                DrawRectangleRec(enemy, BLUE);
                p1.draw();

            EndMode2D();


        EndDrawing();
    }


//Unload    
    CloseWindow();
    return 0;
}