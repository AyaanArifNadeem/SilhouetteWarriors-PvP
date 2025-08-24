#include<iostream>
#include<raylib.h>
#include<cmath>
#include "player.hpp"
#include "map1.hpp"
#include "map2.hpp"
#include "map3.hpp"
#include "map4.hpp"
#include "map5.hpp"
using namespace std;

int main(){
    bool exitgame = 0, next = 0;
    const int ScreenWidth = 1920, ScreenHeight = 1080;
    InitWindow(ScreenWidth,ScreenHeight,"SilhouetteWarriors-PvP");
    InitAudioDevice();

    Texture2D MainScreen = LoadTexture("res/mainmenu.png");

    Sound Buttonsfx = LoadSound("res/audio/buttonsfxwav.wav");
    Sound punchsfx = LoadSound("res/audio/punchsfxwav.wav");
    Sound punchsfx2 = LoadSound("res/audio/punchsfxwav.wav");
    Sound kicksfx = LoadSound("res/audio/kicksfxwav.wav");
    Sound kicksfx2 = LoadSound("res/audio/kicksfxwav.wav");
    Sound jumpsfx = LoadSound("res/audio/jumpsfxwav.wav");
    Sound jumpsfx2 = LoadSound("res/audio/jumpsfxwav.wav");
    Sound crouchsfx = LoadSound("res/audio/crouchsfxwav.wav");
    Sound crouchsfx2 = LoadSound("res/audio/crouchsfxwav.wav");


    Music Track1 = LoadMusicStream("res/audio/Music1wav.wav");
    Music Track2 = LoadMusicStream("res/audio/Music2wav.wav");
    Music Track3 = LoadMusicStream("res/audio/Music3wav.wav");
    Music Track4 = LoadMusicStream("res/audio/Music4wav.wav");

    PlayMusicStream(Track1);
    PlayMusicStream(Track2);
    PlayMusicStream(Track3);
    PlayMusicStream(Track4);

//Entity Decleration
    player p1; 
    player p2;
    p2.position = {1800.0f, -300.0f};
    p1.setControls(KEY_W, KEY_S, KEY_A, KEY_D, KEY_Q, KEY_E);
    p2.setControls(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_PAGE_UP, KEY_PAGE_DOWN);
    map1 m1;

//Settings
    char player1name[9];
    char player2name[9];
    int charCount1 = 0, charCount2 = 0;
    int rtime[5] = {30, 45, 60, 75, 90};
    int rounds[3] = {1,3,5};
    int Round_time = rtime[0], Total_Rounds = rounds[0];

//Camera Setup
    Camera2D camera = { 0 };
    camera.target = (Vector2){ ((p1.position.x + p2.position.x+200)/2.0f), ((p1.position.y + p2.position.y)/2.0f) };
    camera.offset = (Vector2){ ScreenWidth/2.0f, ScreenHeight/2.0f-140 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    SetTargetFPS(60);

//Main Menu
    Rectangle MouseCursor;
    Rectangle StartGame = {800.0f, 550.0f, 300.0f, 60.0f};
    Rectangle Settings =  {800.0f, 660.0f, 300.0f, 60.0f};
    Rectangle Credits =   {800.0f, 770.0f, 300.0f, 60.0f};
    Rectangle ExitGame =  {800.0f, 880.0f, 300.0f, 60.0f};
    Rectangle Back =      {100.0f, ScreenHeight - 100.0f, 300.0f, 60.0f};
    Rectangle P1name =  {100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
    Rectangle P2name =  {100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
    Rectangle rt1, rt2, rt3, rt4, rt5, nr1, nr2, nr3;


    float num = 0.0f;
    bool setting, creds; 
    while (!WindowShouldClose() || !next){
        MouseCursor = {(float)GetMouseX(), (float)GetMouseY(), 1.0f,1.0f};
        num += 20;if(num > 1500){num = 1550.0f;}

        UpdateMusicStream(Track2);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexturePro(MainScreen, (Rectangle){0.0f,0.0f,(float)MainScreen.width,(float)MainScreen.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);
            Back = {100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            P1name =  {100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            P2name =  {100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            rt1 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            rt2 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            rt3 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            rt4 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            rt5 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            nr1 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            nr2 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            nr3 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};



            if(!next && !setting && !creds){
                StartGame = {800.0f, 550.0f, 300.0f, 60.0f};Settings =  {800.0f, 660.0f, 300.0f, 60.0f};Credits =   {800.0f, 770.0f, 300.0f, 60.0f};ExitGame =  {800.0f, 880.0f, 300.0f, 60.0f};
                DrawRectangle(180.0f,215.0f,num,190.0f,BLACK);
                DrawText("Silhouette Warriors", 200.0f, (ScreenHeight/2.0f)- 300.0f, 150.0f, WHITE);

                if(!CheckCollisionRecs(MouseCursor,StartGame)){DrawRectangleRec(StartGame,WHITE);DrawText("Start Game", 805.0f, 560.0f, 50.0f, BLACK);}
                else{DrawRectangleRec(StartGame,BLACK);DrawText("Start Game", 805.0f, 560.0f, 50.0f, WHITE);}
                
                if(!CheckCollisionRecs(MouseCursor,Settings)){DrawRectangleRec(Settings,WHITE);DrawText("Settings", 840.0f, 665.0f, 50.0f, BLACK);}
                else{DrawRectangleRec(Settings,BLACK);DrawText("Settings", 840.0f, 665.0f, 50.0f, WHITE);}
                
                if(!CheckCollisionRecs(MouseCursor,Credits)){DrawRectangleRec(Credits,WHITE);DrawText("Credits", 850.0f, 780.0f, 50.0f, BLACK);}
                else{DrawRectangleRec(Credits,BLACK);DrawText("Credits", 850.0f, 780.0f, 50.0f, WHITE);}


                if(!CheckCollisionRecs(MouseCursor,ExitGame)){DrawRectangleRec(ExitGame,WHITE);DrawText("Exit", 900.0f, 890.0f, 50.0f, BLACK);}
                else{DrawRectangleRec(ExitGame,BLACK);DrawText("Exit", 900.0f, 890.0f, 50.0f, WHITE);}
            
            }else if(setting){
                StartGame = {800.0f, 5500.0f, 300.0f, 60.0f};Settings =  {800.0f, 6600.0f, 300.0f, 60.0f};Credits =   {800.0f, 7700.0f, 300.0f, 60.0f};ExitGame =  {800.0f, 8800.0f, 300.0f, 60.0f};Back =      {100.0f, ScreenHeight - 100.0f, 300.0f, 60.0f};
                P1name =  {700.0f, 300.0f, 300.0f, 60.0f}; P2name = {700.0f, 400.0f, 300.0f, 60.0f};
                rt1 ={725.0f, 500.0f, 50.0f, 60.0f};
                rt2 ={775.0f, 500.0f, 50.0f, 60.0f};
                rt3 ={825.0f, 500.0f, 50.0f, 60.0f};
                rt4 ={875.0f, 500.0f, 50.0f, 60.0f};
                rt5 ={925.0f, 500.0f, 50.0f, 60.0f};
                nr1 ={775.0f, 600.0f, 50.0f, 60.0f};
                nr2 ={825.0f, 600.0f, 50.0f, 60.0f};
                nr3 ={875.0f, 600.0f, 50.0f, 60.0f};


                DrawRectangle(90.0f,50.0f,670.0f,190.0f,BLACK);
                DrawText("Settings", 110.0f, (ScreenHeight/2.0f)- 470.0f, 150.0f, WHITE);

                DrawRectangle(200.0f, 300.0f, 440.0f, 60.0f, WHITE);
                DrawText("Player 1 Name",220.0f, 300.0f,55.0f, BLACK);
                DrawRectangle(200.0f, 400.0f, 440.0f, 60.0f, WHITE);
                DrawText("Player 2 Name",220.0f, 400.0f,55.0f, BLACK);
                DrawRectangle(200.0f, 500.0f, 440.0f, 60.0f, WHITE);
                DrawText("Round Time",220.0f, 500.0f,55.0f, BLACK);
                DrawRectangle(200.0f, 600.0f, 440.0f, 60.0f, WHITE);
                DrawText("Rounds Number",220.0f, 600.0f,55.0f, BLACK);
                DrawRectangle(200.0f, 700.0f, 440.0f, 60.0f, WHITE);
                DrawText("Track No.",220.0f, 700.0f,55.0f, BLACK);
                DrawRectangle(200.0f, 800.0f, 440.0f, 60.0f, WHITE);
                DrawText("Map",220.0f, 800.0f,55.0f, BLACK);

                DrawRectangleRec(P1name, BLACK);
                DrawRectangleRec(P2name, BLACK);
                DrawRectangle(700.0f, 500.0f, 300.0f, 60.0f, BLACK);
                DrawRectangle(700.0f, 600.0f, 300.0f, 60.0f, BLACK);
                DrawRectangle(700.0f, 700.0f, 300.0f, 60.0f, BLACK);

                DrawText(player1name,P1name.x, P1name.y, 55.0f, WHITE);
                DrawText(player2name,P2name.x, P2name.y, 55.0f, WHITE);
                
                DrawRectangleRec(rt1,BLACK);
                DrawRectangleRec(rt2,BLACK);
                DrawRectangleRec(rt3,BLACK);
                DrawRectangleRec(rt4,BLACK);
                DrawRectangleRec(rt5,BLACK);
                for(int i =0; i < 5; i++){DrawText(TextFormat("%d",rtime[i]), (725.0f+(i*50))+10.0f, rt1.y + 20.0f, 30.0f, WHITE);}


                DrawRectangleRec(nr1,BLACK);
                DrawRectangleRec(nr2,BLACK);
                DrawRectangleRec(nr3,BLACK);
                for(int i = 0; i < 3; i++){DrawText(TextFormat("%d",rounds[i]), (775.0f+(i*50))+10.0f, nr1.y + 20.0f, 30.0f, WHITE);}


                if(CheckCollisionRecs(MouseCursor,P1name)){
                int key = GetCharPressed();
                while (key > 0) {
                    if (key >= 32 && key <= 126 && charCount1 < 10) {
                        player1name[charCount1] = (char)key;
                        charCount1++;
                    }
                    key = GetCharPressed();  
                }
            
                if (IsKeyPressed(KEY_BACKSPACE) && charCount1 > 0) {
                    charCount1--;
                    player1name[charCount1] = '\0';
                }}

                if(CheckCollisionRecs(MouseCursor,P2name)){
                int key2 = GetCharPressed();
                while (key2 > 0) {
                    if (key2 >= 32 && key2 <= 126 && charCount2 < 10) {
                        player2name[charCount2] = (char)key2;
                        charCount2++;
                    }
                    key2 = GetCharPressed();  
                }
            
                if (IsKeyPressed(KEY_BACKSPACE) && charCount2 > 0) {
                    charCount2--;
                    player2name[charCount2] = '\0';
                }}

                if(CheckCollisionRecs(MouseCursor,rt1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Round_time = rtime[0];}
                else if(CheckCollisionRecs(MouseCursor,rt2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Round_time = rtime[1];}
                else if(CheckCollisionRecs(MouseCursor,rt3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Round_time = rtime[2];}
                else if(CheckCollisionRecs(MouseCursor,rt4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Round_time = rtime[3];}
                else if(CheckCollisionRecs(MouseCursor,rt5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Round_time = rtime[4];}

                if(CheckCollisionRecs(MouseCursor,nr1)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Total_Rounds = rounds[0];}
                else if(CheckCollisionRecs(MouseCursor,nr2)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Total_Rounds = rounds[1];}
                else if(CheckCollisionRecs(MouseCursor,nr3)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){Total_Rounds = rounds[2];}
                
                if(Round_time == rtime[0]){DrawRectangleLines(725.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[1]){DrawRectangleLines(775.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[2]){DrawRectangleLines(825.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[3]){DrawRectangleLines(875.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[4]){DrawRectangleLines(925.0f, 500.0f, 50.0f, 60.0f,WHITE);}

                if(Total_Rounds == rounds[0]){DrawRectangleLines(775.0f, 600.0f, 50.0f, 60.0f,WHITE);}
                else if(Total_Rounds == rounds[1]){DrawRectangleLines(825.0f, 600.0f, 50.0f, 60.0f,WHITE);}
                else if(Total_Rounds == rounds[2]){DrawRectangleLines(875.0f, 600.0f, 50.0f, 60.0f,WHITE);}
                
                if(!CheckCollisionRecs(MouseCursor, Back)){DrawRectangleRec(Back,WHITE);DrawText("BACK", 170.0f, 990.0f, 50.0f, BLACK);}
                else{DrawRectangleRec(Back,BLACK);DrawText("BACK", 170.0f, 990.0f, 50.0f, WHITE);}


            }

            if(CheckCollisionRecs(MouseCursor,StartGame) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){next = 1;PlaySound(Buttonsfx);}
            else if(CheckCollisionRecs(MouseCursor,Settings) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){setting = 1;PlaySound(Buttonsfx);}
            else if(CheckCollisionRecs(MouseCursor,Credits) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){creds = 1;PlaySound(Buttonsfx);}
            else if(CheckCollisionRecs(MouseCursor,ExitGame) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){exitgame = 1;PlaySound(Buttonsfx);}
            else if(CheckCollisionRecs(MouseCursor, Back) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){setting = 0; creds = 0; PlaySound(Buttonsfx);}
        
        EndDrawing();
        for(int i = 0; i < 9; i++){
            p1.username[i] = player1name[i];
            p2.username[i] = player2name[i];
        }
        if (exitgame || next) break;
    }
    
    next = 0;



    while(!WindowShouldClose() && !exitgame){
//UPDATE
        UpdateMusicStream(Track2);
        m1.update(p1, p2); 
        p1.update(p2);
        p2.update(p1);
        if(p1.playpunchsfx){PlaySound(punchsfx);}
        if(p1.playkicksfx){PlaySound(kicksfx);}
        if(p1.playjumpsfx){PlaySound(jumpsfx);}
        if(p1.playcrouchsfx){PlaySound(crouchsfx);}
        if(p2.playpunchsfx){PlaySound(punchsfx2);}
        if(p2.playkicksfx){PlaySound(kicksfx2);}
        if(p2.playjumpsfx){PlaySound(jumpsfx2);}
        if(p2.playcrouchsfx){PlaySound(crouchsfx2);}

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
            DrawRectangle(-1000, 975.0f-(m1.flooroffset), 5000, 3000, BLACK);

            BeginMode2D(camera);   

                p2.draw();
                p1.draw();

            EndMode2D();


        EndDrawing();
    }


//Unload  
    UnloadTexture(MainScreen);
    UnloadSound(Buttonsfx);
    UnloadSound(punchsfx); 
    UnloadSound(punchsfx2); 
    UnloadSound(kicksfx);
    UnloadSound(kicksfx2);
    UnloadSound(jumpsfx);
    UnloadSound(jumpsfx2);
    UnloadSound(crouchsfx);
    UnloadSound(crouchsfx2);
    UnloadMusicStream(Track1);
    UnloadMusicStream(Track2);
    UnloadMusicStream(Track3);
    UnloadMusicStream(Track4);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}