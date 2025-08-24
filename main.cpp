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
    Texture2D maptwo =   LoadTexture("res/m2.png");
    Texture2D mapthree = LoadTexture("res/m3.png");
    Texture2D mapfour =  LoadTexture("res/m4.png");
    Texture2D mapfive =  LoadTexture("res/m5.png");
    Texture2D noblock =  LoadTexture("res/skull.png");

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

//Map Decleration
map1 m1;
map2 m2;
map3 m3;
map4 m4;
map5 m5;

//Entity Decleration
    player p1; 
    player p2;
    p2.position = {1800.0f, -300.0f};
    p1.setControls(KEY_W, KEY_S, KEY_A, KEY_D, KEY_Q, KEY_E);
    p2.setControls(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_PAGE_UP, KEY_PAGE_DOWN);

//Settings
    char player1name[9] = {'\0'};
    char player2name[9] = {'\0'};
    int charCount1 = 0, charCount2 = 0;
    int rtime[5] = {30, 45, 60, 75, 90};
    int rounds[3] = {1,3,5};
    int Playlist[4] = {1,2,3,4};
    int maps[5] = {1,2,3,4,5};
    int Round_time = rtime[0], Total_Rounds = rounds[0], current_track = Playlist[1], current_map = maps[0];

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
    Rectangle rt1, rt2, rt3, rt4, rt5, nr1, nr2, nr3, t1, t2, t3 ,t4, ma1, ma2, ma3, ma4, ma5;


    float num = 0.0f;
    bool setting, creds; 
    while (!WindowShouldClose() || !next){
        MouseCursor = {(float)GetMouseX(), (float)GetMouseY(), 1.0f,1.0f};
        num += 20;if(num > 1500){num = 1550.0f;}

        if(current_track == Playlist[0]){UpdateMusicStream(Track1);}
        else if(current_track == Playlist[1]){UpdateMusicStream(Track2);}
        else if(current_track == Playlist[2]){UpdateMusicStream(Track3);}
        else if(current_track == Playlist[3]){UpdateMusicStream(Track4);}

        
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if(current_map == maps[0]){DrawTexturePro(MainScreen, (Rectangle){0.0f,0.0f,(float)MainScreen.width,(float)MainScreen.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[1]){DrawTexturePro(maptwo, (Rectangle){0.0f,0.0f,(float)maptwo.width,(float)maptwo.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[2]){DrawTexturePro(mapthree, (Rectangle){0.0f,0.0f,(float)mapthree.width,(float)mapthree.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[3]){DrawTexturePro(mapfour, (Rectangle){0.0f,0.0f,(float)mapfour.width,(float)mapfour.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[4]){DrawTexturePro(mapfive, (Rectangle){0.0f,0.0f,(float)mapfive.width,(float)mapfive.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            
            
            
            
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
            t1 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            t2 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            t3 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            t4 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            ma1 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            ma2 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            ma3 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            ma4 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};
            ma5 ={100.0f, ScreenHeight + 100.0f, 300.0f, 60.0f};



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
                t1 ={750.0f, 700.0f, 50.0f, 60.0f};
                t2 ={800.0f, 700.0f, 50.0f, 60.0f};
                t3 ={850.0f, 700.0f, 50.0f, 60.0f};
                t4 ={900.0f, 700.0f, 50.0f, 60.0f};
                ma1 ={725.0f, 800.0f, 50.0f, 60.0f};
                ma2 ={775.0f, 800.0f, 50.0f, 60.0f};
                ma3 ={825.0f, 800.0f, 50.0f, 60.0f};
                ma4 ={875.0f, 800.0f, 50.0f, 60.0f};
                ma5 ={925.0f, 800.0f, 50.0f, 60.0f};




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
                DrawRectangle(700.0f, 800.0f, 300.0f, 60.0f, BLACK);

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
                for(int i = 0; i < 3; i++){DrawText(TextFormat("%d",rounds[i]), (775.0f+(i*50))+20.0f, nr1.y + 20.0f, 30.0f, WHITE);}


                DrawRectangleRec(t1,BLACK);
                DrawRectangleRec(t2,BLACK);
                DrawRectangleRec(t3,BLACK);
                DrawRectangleRec(t4,BLACK);
                for(int i = 0; i < 4; i++){DrawText(TextFormat("%d",Playlist[i]), (750.0f+(i*50))+15.0f, t1.y + 20.0f, 30.0f, WHITE);}


                DrawRectangleRec(ma1,BLACK);
                DrawRectangleRec(ma2,BLACK);
                DrawRectangleRec(ma3,BLACK);
                DrawRectangleRec(ma4,BLACK);
                DrawRectangleRec(ma5,BLACK);
                for(int i =0; i < 5; i++){DrawText(TextFormat("%d",maps[i]), (725.0f+(i*50))+10.0f, ma1.y + 20.0f, 30.0f, WHITE);}



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

                if(CheckCollisionRecs(MouseCursor,t1)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))     {current_track = Playlist[0];StopMusicStream(Track1); PlayMusicStream(Track1);}
                else if(CheckCollisionRecs(MouseCursor,t2)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_track = Playlist[1];StopMusicStream(Track2); PlayMusicStream(Track2);}
                else if(CheckCollisionRecs(MouseCursor,t3)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_track = Playlist[2];StopMusicStream(Track3); PlayMusicStream(Track3);}
                else if(CheckCollisionRecs(MouseCursor,t4)  && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_track = Playlist[3];StopMusicStream(Track4); PlayMusicStream(Track4);}

                if(CheckCollisionRecs(MouseCursor,ma1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_map = maps[0];}
                else if(CheckCollisionRecs(MouseCursor,ma2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_map = maps[1];}
                else if(CheckCollisionRecs(MouseCursor,ma3) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_map = maps[2];}
                else if(CheckCollisionRecs(MouseCursor,ma4) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_map = maps[3];}
                else if(CheckCollisionRecs(MouseCursor,ma5) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){current_map = maps[4];}
                
                if(Round_time == rtime[0]){DrawRectangleLines(725.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[1]){DrawRectangleLines(775.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[2]){DrawRectangleLines(825.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[3]){DrawRectangleLines(875.0f, 500.0f, 50.0f, 60.0f,WHITE);}
                else if(Round_time == rtime[4]){DrawRectangleLines(925.0f, 500.0f, 50.0f, 60.0f,WHITE);}

                if(Total_Rounds == rounds[0]){DrawRectangleLines(775.0f, 600.0f, 50.0f, 60.0f,WHITE);}
                else if(Total_Rounds == rounds[1]){DrawRectangleLines(825.0f, 600.0f, 50.0f, 60.0f,WHITE);}
                else if(Total_Rounds == rounds[2]){DrawRectangleLines(875.0f, 600.0f, 50.0f, 60.0f,WHITE);}

                if(current_track == Playlist[0]){DrawRectangleLinesEx(t1,2.0f, WHITE);}
                else if(current_track == Playlist[1]){DrawRectangleLinesEx(t2,2.0f, WHITE);}
                else if(current_track == Playlist[2]){DrawRectangleLinesEx(t3,2.0f, WHITE);}
                else if(current_track == Playlist[3]){DrawRectangleLinesEx(t4,2.0f, WHITE);}

                if(current_map == maps[0]){DrawRectangleLines(715.0f, 800.0f, 50.0f, 60.0f,WHITE);}
                else if(current_map == maps[1]){DrawRectangleLines(765.0f, 800.0f, 50.0f, 60.0f,WHITE);}
                else if(current_map == maps[2]){DrawRectangleLines(815.0f, 800.0f, 50.0f, 60.0f,WHITE);}
                else if(current_map == maps[3]){DrawRectangleLines(865.0f, 800.0f, 50.0f, 60.0f,WHITE);}
                else if(current_map == maps[4]){DrawRectangleLines(915.0f, 800.0f, 50.0f, 60.0f,WHITE);}


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

    SetMusicVolume(Track1,0.4f);
    SetMusicVolume(Track2,0.4f);
    SetMusicVolume(Track3,0.4f);
    SetMusicVolume(Track4,0.4f);
    int p1wins = 0, p2wins = 0;

    if(p1.username[0] == '\0'){ p1.username[0] = 'P';
                                p1.username[1] = 'l';
                                p1.username[2] = 'a';
                                p1.username[3] = 'y';
                                p1.username[4] = 'e';
                                p1.username[6] = 'r';
                                p1.username[7] = '1';
                                p1.username[8] = '\0';
    }
    if(p2.username[0] == '\0'){ p2.username[0] = 'P';
                                p2.username[1] = 'l';
                                p2.username[2] = 'a';
                                p2.username[3] = 'y';
                                p2.username[4] = 'e';
                                p2.username[6] = 'r';
                                p2.username[7] = '2';
                                p2.username[8] = '\0';
    }

//GAME LOOP
    while(!WindowShouldClose() && p1wins !=  (Total_Rounds/2)+1 && p2wins !=  (Total_Rounds/2)+1 && (!exitgame)){

    int roundstarttime = GetTime();
    int roundtimeleft = Round_time;
    p1.health = 200; p2.health = 200;
    bool p1win = 0, p2win = 0;
    int roundfinishtime = INT_MAX;
    p1.position.x = 500.0f;
    p2.position.x = 2000.0f;

    while(!WindowShouldClose() && !exitgame){
//UPDATE
        if(!p1win && !p2win && roundtimeleft > 0)roundtimeleft = Round_time - (GetTime() - roundstarttime) +1;

        if(GetTime() - roundfinishtime > 4){break;}
        if(!p1win && !p2win && (roundtimeleft < 0 || p1.health <1 || p2.health< 1)){roundfinishtime = GetTime();}

        if(roundtimeleft < 0 || p1.health <1 || p2.health< 1){p1.pausemove = 1; p2.pausemove = 1;
            if(p1.health > p2.health)p1win = 1;
            else if(p1.health < p2.health)p2win = 1;
        } else {p1.pausemove = 0; p2.pausemove = 0;}

        if(current_track == Playlist[0]){UpdateMusicStream(Track1);}
        else if(current_track == Playlist[1]){UpdateMusicStream(Track2);}
        else if(current_track == Playlist[2]){UpdateMusicStream(Track3);}
        else if(current_track == Playlist[3]){UpdateMusicStream(Track4);}



        if(current_map == maps[0])     {m1.update(p1, p2);}
        else if(current_map == maps[1]){m2.update(p1, p2);}
        else if(current_map == maps[2]){m3.update(p1, p2);}
        else if(current_map == maps[3]){m4.update(p1, p2);}
        else if(current_map == maps[4]){m5.update(p1, p2);}


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

            if(current_map == maps[0])     {m1.flooroffset =  ((fabs(p1.position.x-p2.position.x))-1720)*0.211538461f;}
            else if(current_map == maps[1]){m2.flooroffset =  ((fabs(p1.position.x-p2.position.x))-1720)*0.211538461f;}
            else if(current_map == maps[2]){m3.flooroffset =  ((fabs(p1.position.x-p2.position.x))-1720)*0.211538461f;}
            else if(current_map == maps[3]){m4.flooroffset =  ((fabs(p1.position.x-p2.position.x))-1720)*0.211538461f;}
            else if(current_map == maps[4]){m5.flooroffset =  ((fabs(p1.position.x-p2.position.x))-1720)*0.211538461f;}
        }else{
            camera.zoom = 1.0f;
            
            if(current_map == maps[0])     {m1.flooroffset = 0.0f;}
            else if(current_map == maps[1]){m2.flooroffset = 0.0f;}
            else if(current_map == maps[2]){m3.flooroffset = 0.0f;}
            else if(current_map == maps[3]){m4.flooroffset = 0.0f;}
            else if(current_map == maps[4]){m5.flooroffset = 0.0f;}
            }
        
        if (camera.zoom > 1.0f) camera.zoom = 1.0f;
        if (camera.zoom < 0.6f) camera.zoom = 0.6f;
       

//DRAW
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if(current_map == maps[0])     {m1.draw();DrawRectangle(-1000, 975.0f-(m1.flooroffset), 5000, 3000, BLACK);}
            else if(current_map == maps[1]){m2.draw();DrawRectangle(-1000, 975.0f-(m2.flooroffset), 5000, 3000, BLACK);}
            else if(current_map == maps[2]){m3.draw();DrawRectangle(-1000, 975.0f-(m3.flooroffset), 5000, 3000, BLACK);}
            else if(current_map == maps[3]){m4.draw();DrawRectangle(-1000, 975.0f-(m4.flooroffset), 5000, 3000, BLACK);}
            else if(current_map == maps[4]){m5.draw();DrawRectangle(-1000, 975.0f-(m5.flooroffset), 5000, 3000, BLACK);}

            float Guioffset = (((fabs(p1.position.x-p2.position.x))-1720)*0.081f);
            if(Guioffset < -50.0f){ Guioffset = -50.0f;}
            if(Guioffset > 110.0f){ Guioffset = 110.0f;}

            BeginMode2D(camera);   

                p2.draw();
                p1.draw();
                DrawText(TextFormat("%d",roundtimeleft), ((p1.position.x+p2.position.x)/2.0f + 70.0f), -760-Guioffset , 100, RED);
                DrawText(p1.username,((p1.position.x+p2.position.x)/2.0f + 70.0f)- 900.0f, -760-Guioffset ,100,PURPLE);
                DrawText(p2.username,((p1.position.x+p2.position.x)/2.0f + 70.0f)+ 140.0f, -760-Guioffset ,100,PURPLE);
                DrawRectangle(((p1.position.x+p2.position.x)/2.0f + 70.0f)- 450.0f,-760-Guioffset,p1.health*2.0f,80,RED);
                DrawRectangle(((p1.position.x+p2.position.x)/2.0f + 70.0f)+ 590.0f,-760-Guioffset,p2.health*2.0f,80,RED);

                if(p1.blockbroken){DrawTexture(noblock,((p1.position.x+p2.position.x)/2.0f + 90.0f)- 900.0f,-660-Guioffset,RAYWHITE);}
                if(p2.blockbroken){DrawTexture(noblock,((p1.position.x+p2.position.x)/2.0f + 90.0f)+ 140.0f,-660-Guioffset,RAYWHITE);}

                if(p1win){DrawText(TextFormat("%s wins",p1.username),((p1.position.x+p2.position.x)/2.0f + 370.0f)- 900.0f, p1.position.y , 200, RED);}
                else if(p2win){DrawText(TextFormat("%s wins",p2.username),((p1.position.x+p2.position.x)/2.0f + 370.0f)- 900.0f, p2.position.y , 200, RED);}

            EndMode2D();


        EndDrawing();
    }

    if(p1win)p1wins++;
    else if(p2win)p2wins++;
    }

    while(!WindowShouldClose() && !exitgame){

        if(current_track == Playlist[0]){UpdateMusicStream(Track1);}
        else if(current_track == Playlist[1]){UpdateMusicStream(Track2);}
        else if(current_track == Playlist[2]){UpdateMusicStream(Track3);}
        else if(current_track == Playlist[3]){UpdateMusicStream(Track4);}

        ExitGame =  {800.0f, 880.0f, 300.0f, 60.0f};
        MouseCursor = {(float)GetMouseX(), (float)GetMouseY(), 1.0f,1.0f};

        BeginDrawing();
            ClearBackground(RAYWHITE);


            if(current_map == maps[0]){DrawTexturePro(MainScreen, (Rectangle){0.0f,0.0f,(float)MainScreen.width,(float)MainScreen.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[1]){DrawTexturePro(maptwo, (Rectangle){0.0f,0.0f,(float)maptwo.width,(float)maptwo.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[2]){DrawTexturePro(mapthree, (Rectangle){0.0f,0.0f,(float)mapthree.width,(float)mapthree.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[3]){DrawTexturePro(mapfour, (Rectangle){0.0f,0.0f,(float)mapfour.width,(float)mapfour.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            else if(current_map == maps[4]){DrawTexturePro(mapfive, (Rectangle){0.0f,0.0f,(float)mapfive.width,(float)mapfive.height},(Rectangle){0.0f,0.0f,ScreenWidth,ScreenHeight},{0.0f,0.0f},0.0f,RAYWHITE);}
            

            if(p1wins> p2wins){{DrawText(TextFormat("%s has won",p1.username),100.0f, ScreenHeight/2.0f - 200.0f , 200, RED);}}
            else if(p1wins< p2wins){{DrawText(TextFormat("%s has won",p2.username),100.0f, ScreenHeight/2.0f - 200.0f , 200, RED);}}
    
            if(!CheckCollisionRecs(MouseCursor,ExitGame)){DrawRectangleRec(ExitGame,WHITE);DrawText("Exit", 900.0f, 890.0f, 50.0f, BLACK);}
            else{DrawRectangleRec(ExitGame,BLACK);DrawText("Exit", 900.0f, 890.0f, 50.0f, WHITE);}

            if(CheckCollisionRecs(MouseCursor,ExitGame) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){exitgame = 1;PlaySound(Buttonsfx);}

        EndDrawing();
    }


//Unload  
    UnloadTexture(MainScreen);
    UnloadTexture(maptwo);
    UnloadTexture(mapthree);
    UnloadTexture(mapfour);
    UnloadTexture(mapfive);
    UnloadTexture(noblock);
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