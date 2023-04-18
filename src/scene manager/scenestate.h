/*************************************************
//Developer: PoliticalCirno || Tapc             //
//Purpose: Scene Management, during transition  //
//Date made: 22/10/18                           //
//Date completed: [[TBD]]                       //
//                                              //
//License : (9) Open license                    //
*************************************************/
#include "raylib.h"
#ifndef SCENESTATE_H
#define SCENESTATE_H
//int delayTime;
//int sceneID;

typedef enum States
{
    LOADING_MAIN,
    LOADING_GAME,
    MENU_MAIN,
    MENU_SUB,
    GAME_TEST,
    GAME_IHATE,
    GAME_PLAY
} SceneManager;

//ints
extern int sceneNumber;

//bools
extern bool isLoading;
extern bool isRuntime;

//Returns nothing // points to void
//void SetLoader(void);
void RenderLogo(void);
void LoadSceneData(void);
void UpdateSceneGraphics(void);
void UpdateSceneLogics(void);
void PrepBoot(void);
//Still a void, but requires an argument
//int SwitchScene();
void SwitchSceneGame(int a);

#endif // SCENESTATE_H
