#include "scene manager/scenestate.h"
#include "engine/scene_headers/scene_logoboot.h"
#include "engine/scene_headers/scene_gametest.h"
#include "engine/headers/generics.h"
#include "engine/headers/player_camera.h"

SceneManager ScreenState = LOADING_MAIN;
float oldTime;
int loadTime;
float newTime;
float deltatime;

sceneNumber = 0;
//Render scene
Update(void)
{
    //oldTime = newTime;
    //newTime = GetTime();
    deltatime = GetFrameTime();

    UpdateSceneGraphics();
}

//Self explanitory
void LoadSceneData(void)
{
    switch(ScreenState)
    {
        case LOADING_MAIN:
        printf("debug");
        PrepBoot();
        break;

        case LOADING_GAME:
        break;

        case GAME_TEST:
        //SetupCamera();
        //LoadTestPhysReq();
        LoadTestAssetsReq();
        TestAnimSys();
        printf("loaded");
        break;

        case GAME_IHATE:

        break;

        default :
        printf("no scenes of that name");
        break;

    }

    return 0;
}

//Self explanitory
UpdateSceneGraphics(void)
{
    if (ScreenState == LOADING_MAIN)
    {
        UpdateBootGraphics();
        UpdateBootLogics();
    }
    if(ScreenState == GAME_TEST)
    {
        printf("this is working");
        TestRunLogics();
    }

}

//Changes the scene with or without delay

SwitchSceneGame(sceneNumber)
{
    if (sceneNumber == 1)
    {
        ScreenState = GAME_TEST;
    }
    if(sceneNumber == 2)
    {
        ScreenState = GAME_IHATE;
    }
    isLoading = true;
}

