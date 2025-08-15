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
    player p1; 
    player p2;
    p1.setControls(KEY_W, KEY_S, KEY_A, KEY_D);
    p2.setControls(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT);
    p2.position = {1800.0f, -300.0f};
    map1 m1;


//Camera Setup
    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((p1.position.x + p2.position.x+200)/2.0f), ((p1.position.y + p2.position.y)/2.0f) };
    camera.offset = (Vector2){ ScreenWidth/2.0f, ScreenHeight/2.0f-140 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    SetTargetFPS(60);


    while(!WindowShouldClose()){
//UPDATE
        m1.update(p1, p2); 
        p1.update();
        p2.update();

        if(p2.position.x>p1.position.x){p2.facingRight = 0; p1.facingRight =1;}
        if(p2.position.x<p1.position.x){p2.facingRight = 1; p1.facingRight =0;}

//Camera Work
        camera.target = (Vector2){ ((p1.position.x + p2.position.x+(200*1.3f))/2.0f), ((p1.position.y + p2.position.y)/2.0f) };
        if(fabs(p1.position.x-p2.position.x) > 1720){
            camera.zoom = 1.646 - 0.000375*(fabs(p1.position.x-p2.position.x));
            m1.flooroffset =  ((fabs(p1.position.x-p2.position.x))-1720)*0.211538461f;
        }else{camera.zoom = 1.0f; m1.flooroffset = 0.0f;}
        if (camera.zoom > 1.0f) camera.zoom = 1.0f;
        if (camera.zoom < 0.6f) camera.zoom = 0.6f;
       

//DRAW
        BeginDrawing();
            ClearBackground(RAYWHITE);

            m1.draw();
            // DrawText(TextFormat("Pos: %f", p1.position.x), 100, 100, 50, RED);
            // DrawText(TextFormat("Pos: %f", p2.y), 100, 200, 50, BLUE);
            DrawRectangle(-1000, 975.0f-(m1.flooroffset), 5000, 3000, BLACK);


            BeginMode2D(camera);   

                p2.draw();
                p1.draw();

            EndMode2D();


        EndDrawing();
    }


//Unload    
    CloseWindow();
    return 0;
}