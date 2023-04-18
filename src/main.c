
/*************************************************
//Developer: PoliticalCirno || Tapc             //
//Purpose: Main funtion, everything starts here //
//Date made: 22/10/18                           //
//Date completed: [[TBD]]                       //
//                                              //
//License : (9) Open license                    //
*************************************************/

///REMINDER: the game's world is called : multa terrarum
#include "raylib.h"
#include "assets/asset_texture_manager.h"
#include "engine/scene_headers/scene_logoboot.h"
#include "assets/asset_texture_rectangles.h"
#include "scene manager/scenestate.h"
#include "engine/headers/generics.h"

//Self explanitory
const int windowHeight = 900;
const int windowWidth = 1600;
int gameTime = 0;
bool isLoading = true;
//bool isSequenceFinished = false;

int main()//main
{

    //isLoading = true;
    InitWindow(windowWidth, windowHeight, "Project Cucumbers");
    //SetWindowState(FLAG_WINDOW_HIDDEN);
    InitAudioDevice();

    SetTargetFPS(60);
    //Code runs in loop
    while(!WindowShouldClose())
    {
        Update();
        if (isLoading == true)
        {
            printf("I be loading");
            LoadSceneData();
            isLoading = false;

        }
    }

    CloseWindow();
    return 0;
}

/*SetLoader(void)
{
    isLoading = true;
}*/
/*void UpdateBootGraphics() [[[[[[BELOW CODE IS MOVED]]]]]]
{
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Cucumber Engine v0.0.1", 70, 100, 100, WHITE);
            DrawTexturePro(logoNitori,rect_ui2_base,rect_ui2_dest,nitoriLogo,0,WHITE);
            DrawTexturePro(logoTexture,rect_ui1_base,rect_ui1_dest,mainLogo,0,WHITE);

           // DrawTexture(logoTexture, 100, 500, WHITE);
        EndDrawing();
}

void UpdateBootLogics()
{
    if (rect_ui1_dest.x < 500)
    {
        rect_ui1_dest.x += 5;
    }

    if (rect_ui1_dest.x >= 500)
    {
        if(rect_ui2_dest.y > 670.0f)
        {
            rect_ui2_dest.y -= 20.0f;

        }

        if (rect_ui2_dest.y < 670.0f)
        {
            if(isSequenceFinished == false)
            {
                Sound wonderHoy = LoadSound("src/wonderhoy.mp3");
                PlaySound(wonderHoy);
                isSequenceFinished = true;
            }
        }
    }
}*/
