#include<iostream>
#include<raylib.h>
#include<cmath>
using namespace std;

int main(){
    const int ScreenWidth = 1920, ScreenHeight = 1080;
    Rectangle player = {(2500/2)-200, 450, 200,450};
    Rectangle enemy =  {(2500/2)-200, 450, 200,450};

    InitWindow(ScreenWidth,ScreenHeight,"SilhouetteWarriors-PvP");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((player.x + enemy.x+200)/2.0f), ((player.y + enemy.y)/2.0f) };
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

    while(!WindowShouldClose()){
        


        //Clouds Control
        scrollingMid -= 0.4f;
        scrollingMid2 -= 0.5f;
        if (scrollingMid <= -c1.width) scrollingMid = ScreenWidth;
        if (scrollingMid2 <= -c2.width*0.75) scrollingMid2 = ScreenWidth;



        //Camera Work
        camera.target = (Vector2){ ((player.x + enemy.x+200)/2.0f), ((player.y + enemy.y)/2.0f) };
        if(fabs(player.x-enemy.x) > 1720){camera.zoom = 1.646 - 0.000375*(fabs(player.x-enemy.x));}
        else{camera.zoom = 1;}
        if (camera.zoom > 1.0f) camera.zoom = 1.0f;
        else if (camera.zoom < 0.7f) camera.zoom = 0.7f;



        //Parallex Effect Code
        //Placeholder Characters Control
        if(enemy.x < 0) enemy.x=0;
        if(player.x < 0) player.x=0;
        if(enemy.x > 2500) enemy.x=2500;
        if(player.x > 2500) player.x=2500;

        if (IsKeyDown(KEY_RIGHT) && player.x < 2500){ 
            player.x += 15;
            scrollingfront3 -= 2;
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if (IsKeyDown(KEY_LEFT) && player.x > 0){ 
            player.x -= 15;
            scrollingfront3 += 2;
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

        if (IsKeyDown(KEY_D) && enemy.x < 2500){ 
            enemy.x += 15;
            scrollingfront3 -= 2;
            scrollingfront2 -= 1;
            scrollingfront1 -= 0.5;
        }
        else if (IsKeyDown(KEY_A) && enemy.x > 0){ 
            enemy.x -= 15;
            scrollingfront3 += 2;
            scrollingfront2 += 1;
            scrollingfront1 += 0.5;
        }

       

        
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
        DrawText(TextFormat("Pos: %f", player.x), 100, 100, 50, RED);
        DrawText(TextFormat("Pos: %f", enemy.x), 100, 200, 50, BLUE);


        BeginMode2D(camera);   

            DrawRectangleRec(player, RED);
            DrawRectangleRec(enemy, BLUE);
            DrawRectangle(-1000, (player.y+player.height-20), 5000, 3000, BLACK);

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