#include<iostream>
#include<raylib.h>
#include<cmath>
using namespace std;

int main(){
    const int ScreenWidth = 1920, ScreenHeight = 980;
    Rectangle player = {200,50,(ScreenWidth/2) -50,(ScreenHeight)-300};

    InitWindow(ScreenWidth,ScreenHeight,"SilhouetteWarriors-PvP");
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
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


    while(!WindowShouldClose()){
        scrollingMid -= 0.4f;
        scrollingMid2 -= 0.5f;

        if (scrollingMid <= -c1.width) scrollingMid = ScreenWidth;
        if (scrollingMid2 <= -c2.width*0.75) scrollingMid2 = ScreenWidth;

        if (IsKeyDown(KEY_RIGHT)) player.x += 2;
        else if (IsKeyDown(KEY_LEFT)) player.x -= 2;

        // Camera target follows player
        camera.target = (Vector2){ player.x + 20, player.y + 20 };

        // Camera rotation controls
        if (IsKeyDown(KEY_A)) camera.rotation--;
        else if (IsKeyDown(KEY_S)) camera.rotation++;

        // Limit camera rotation to 80 degrees (-40 to 40)
        if (camera.rotation > 40) camera.rotation = 40;
        else if (camera.rotation < -40) camera.rotation = -40;

        // Camera zoom controls
        // Uses log scaling to provide consistent zoom speed
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()*0.1f));

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexturePro(sky,(Rectangle){0, 0, (float)sky.width, (float)sky.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);        
        
        DrawTextureEx(c1, (Vector2){ scrollingMid, 0 }, 0.0f, 1.0f, WHITE);
        DrawTextureEx(c1, (Vector2){ c1.width*2 + scrollingMid, 0 }, 0.0f, 1.0f, WHITE);

        DrawTexturePro(rocks,(Rectangle){0, 0, (float)rocks.width, (float)rocks.height},(Rectangle){0, -100, ScreenWidth, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);

        

        DrawTexturePro(g1,(Rectangle){0, 0, (float)g1.width, (float)g1.height},(Rectangle){-50, -100, ScreenWidth+100, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);


        DrawTextureEx(c2, (Vector2){ scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);
        DrawTextureEx(c2, (Vector2){ c2.width*2 + scrollingMid2, -250 }, 0.0f, 0.8f, WHITE);

        DrawTexturePro(g2,(Rectangle){0, 0, (float)g2.width, (float)g2.height},(Rectangle){-50, -100, ScreenWidth+100, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
        DrawTexturePro(g3,(Rectangle){0, 0, (float)g3.width, (float)g3.height},(Rectangle){-50, -100, ScreenWidth+100, ScreenHeight},(Vector2){0, 0},0.0f,WHITE);
        DrawRectangle(-500, ScreenHeight-100, ScreenWidth+1000, 100, BLACK);


            BeginMode2D(camera);

                DrawRectangle((ScreenWidth/2) -50,(ScreenHeight)-300,200,50,BLUE);

                

                DrawRectangleRec(player, RED);


            EndMode2D();





        EndDrawing();
    }

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