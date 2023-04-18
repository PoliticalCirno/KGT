#ifndef GENERICS_H
#define GENERICS_H

#define MAX_CONTACTS 8
//#define MAX_OBJ 200
#define MAX_ENTITY_DY 1024
#define MAX_ENTITY_PHYS 512
#define dSINGLE
#include <ode/ode.h>
#include "raylib.h"
#include "../headers_rl/rlgl.h"
#include "../headers_rl/raymath.h"
#include <math.h>

//--------------------Time Management-----------------//
extern float oldTime;
extern float newTime;
extern float deltatime;
//--------------------Menu / non-game Ui--------------//
void DrawMenuUiBackground(Texture2D texture); //[[May be deprecated]]


//--------------------Game Ui---------------------//
void SetGameUiBackground(char bgLocation);
void DrawGameUiElemants(void);

//---------[[MAIN FUNCTION/PURPOSE OF THIS]]----------//
void Update(void);

//=========[Physics / collisions]============//
//static void NearCallBack(void *data, dGeomID o1, dGeomID o2);

#endif // GENERICS_H
