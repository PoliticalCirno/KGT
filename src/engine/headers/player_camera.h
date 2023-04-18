/*************************************************
//Credit for this code: Jeffery Myers           //
//See below.                                    //
//                                              //
//Purpose: Player Camera, Runs At gamestate.    //
//Date made: 22/10/18                           //
//Date completed: [[TBD]]                       //
//                                              //
//License : MIT                                 //
*************************************************/

/**********************************************************************************************
*
*   raylibExtras * Utilities and Shared Components for Raylib
*
*   FPCamera * Simple First person camera (C version)
*
*   LICENSE: MIT
*
*   Copyright (c) 2020 Jeffery Myers
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*
**********************************************************************************************/

#include "raylib.h"
#include "generics.h"
#ifndef PLAYER_CAMERA_H
#define PLAYER_CAMERA_H

// updated to better camera
typedef enum
{
    MOVE_FORWARD = 0,
    MOVE_BACKWARD = 1,
    MOVE_RIGHT = 2,
    MOVE_LEFT = 3,
    MOVE_DOWN,
    MOVE_UP,
    TURN_RIGHT,
    TURN_LEFT,
    TURN_UP,
    TURN_DOWN,
    SPRINT,
    LAST_CONTROL
}FpCameraControls;

typedef struct
{
    int controlsKey[LAST_CONTROL];

    Vector3 moveSpeed; // x = strafe /y jump /z forward
    Vector2 rotationSpeed; //self-explanitory
    bool useMouse;

    bool invertY;

    // how many pixels equate out to an angle move, larger numbers mean slower, more accurate mouse
    float mouseSensitivity;

    // how far down can the camera look
    float minimumViewY;

    // how far up can the camera look
    float maximumViewY;

    // how fast the view should bobble as you move
    // defaults to 0 for no bobble
    float viewBobbleFreq;

    // how high up/down will the bobble be
    float viewBobbleMagnatude;

    // how far left and right should the view bobble
    float viewBobbleWaverMagnitude;

    // the position of the base of the camera (on the floor)
    // note that this will not be the view position because it is offset by the eye height.
    // this value is also not changed by the view bobble
    Vector3 cameraPosition;

    // how far from the base of the camera is the player's view
    float playerEyesPosition;

    // the field of view in X and Y
    Vector2 FOV;

    // state for view movement
    float targetDistance;

    // state for view angles
    Vector2 viewAngles;

    // state for bobble
    float currentBobble;

    // state for window focus
    bool focused;

    bool allowFlight;
    bool carMod;
    // raylib camera for use with raylib modes.
    Camera3D ViewCamera;

    Vector3 Forward;
    Vector3 Right;

    //clipping planes
    // note must use BeginModeFP3D and EndModeFP3D instead of BeginMode3D/EndMode3D for clipping planes to work
    double NearPlane;
    double FarPlane;
}FpCamera;

RLAPI void FpCameraInit(FpCamera* camera, float fovY, Vector3 position);

RLAPI void FpCameraMouse(FpCamera* camera, bool mouseUse);

RLAPI void FpCameraResizeVeiw(FpCamera* camera);

RLAPI Vector3 FpCameraGetPosition(FpCamera* camera);

RLAPI void FpCameraSetPosition(FpCamera* camera, Vector3 pos);

RLAPI Ray FpCameraGetViewRay(FpCamera* camera);

RLAPI void FpCameraUpdate(FpCamera* camera);

RLAPI void FpCameraBeginMode3D(FpCamera* camera);

RLAPI void FpCameraEndMode3D();


//////////////DEPRECATED CODES///////////////////////////////////////////////////////////

//Main playercamera [Note]: btw this seems like a bad way. what if i had to add multiple camera?

extern Camera playerCamera; //[[POSSIBLE DEPRECATION]]
void SetupCamera(void);
void CameraLogic(void);
#endif // PLAYER_CAMERA_H
