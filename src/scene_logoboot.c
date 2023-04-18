#include "raylib.h"
#include "engine/headers/generics.h"
#include "assets/asset_texture_manager.h"
#include "assets/asset_texture_rectangles.h"
#include "engine/scene_headers/scene_logoboot.h"
#include <stdlib.h>
#include <stdio.h>
/*************************************************
//Developer: PoliticalCirno || Tapc             //
//Purpose: Logo display, runs at execution.     //
//Date made: 22/10/18                           //
//Date completed: [[TBD]]                       //
//                                              //
//License : (9) Open license                    //
*************************************************/

//Texture datas

Texture2D logoTexture = {0};
Texture2D logoNitori = {0};

//Local Bools (only for this script)

bool isSequenceFinished = false;

Vector2 mainLogo = {64, 64};
Vector2 nitoriLogo = {128.0f/2, 128.0f/2};


void PrepBoot() //[Will be deprecated]
{
        //logoTexture = LoadTexture("src/logo.png");
        //logoNitori = LoadTexture("logo_nitori.png");
        //LoadMap(1, "");
}

void UpdateBootGraphics(void)
{
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("KAPPA GAME TOOL v0.1", 20, 50, 100, WHITE);
            //DrawText("EPIK?!v", 20, 70, 100, WHITE);
            //DrawTexturePro(logoNitori,rect_ui2_base,rect_ui2_dest,nitoriLogo,0,WHITE); //tag nitori
            //DrawTexturePro(logoTexture,rect_ui1_base,rect_ui1_dest,mainLogo,0,WHITE); // tag cucumber

           // DrawTexture(logoTexture, 100, 500, WHITE);
        EndDrawing();
}

void UpdateBootLogics(void)
{
    if (rect_ui1_dest.x < 670)
    {
        rect_ui1_dest.x += 100 * deltatime;
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

                //Sound wonderHoy = LoadSound("src/musica.wav");
                SwitchSceneGame(1);
                //PlaySound(wonderHoy);
                isSequenceFinished = true;
            }
        }
    }

}
