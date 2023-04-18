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
#include "headers/player_camera.h"
#include <stdlib.h>
Camera playerCamera = {0};
Vector2 playerMouse = {0.0f, 0.0f};

void FpCameraInit(FpCamera* camera, float fovY, Vector3 position)
{
	if (camera == NULL)
        return;

	camera->controlsKey[0] = 'W';//self explanitory
	camera->controlsKey[1] = 'S';
	camera->controlsKey[2] = 'A';
	camera->controlsKey[3] = 'D';
	camera->controlsKey[4] = 'E';//for elevation and inverse
	camera->controlsKey[5] = 'Q';
	camera->controlsKey[6] = KEY_LEFT;
	camera->controlsKey[7] = KEY_RIGHT;
	camera->controlsKey[8] = KEY_UP;
	camera->controlsKey[9] = KEY_DOWN;
	camera->controlsKey[10] = KEY_LEFT_SHIFT;

	// Speed (?)
	camera->moveSpeed = (Vector3) {1, 1, 1};
	camera->rotationSpeed = (Vector2) {90, 90};

	camera->useMouse = true;
	camera->mouseSensitivity = 600.0f;
	camera->invertY = false;

	// some clamps
	camera->minimumViewY = -89.0f;
	camera->maximumViewY = 89.0f;

	camera->viewBobbleFreq = 0.0f;
	camera->viewBobbleMagnatude = 0.02f;
	camera->viewBobbleWaverMagnitude = 0.005f;
	camera->currentBobble = 0;

	camera->focused = IsWindowFocused();

	camera->targetDistance = 1;
	camera->playerEyesPosition = 0.5f;
	camera->viewAngles = (Vector2){0,0};

	camera->cameraPosition = position;
	camera->FOV.y = fovY;

    camera->ViewCamera.position = position;
    camera->ViewCamera.position.y += camera->playerEyesPosition;
    camera->ViewCamera.target = Vector3Add(camera->ViewCamera.position, (Vector3) {0, 0, camera->targetDistance});
    camera->ViewCamera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera->ViewCamera.fovy = fovY;
    camera->ViewCamera.projection = CAMERA_PERSPECTIVE;

    camera->allowFlight = false;

    camera->NearPlane = 0.01f;
    camera->FarPlane = 1000.0;

    FpCameraResizeVeiw(camera);
    FpCameraMouse(camera, camera->useMouse);
}

void FpCameraMouse(FpCamera* camera, bool UseMouse)
{
    if (!camera)
        return;

    camera->useMouse = UseMouse;

    if (UseMouse && IsWindowFocused())
        DisableCursor();
    else if (!UseMouse && IsWindowFocused())
        EnableCursor();
}

void FpCameraResizeVeiw(FpCamera* camera)
{
    if (camera == NULL)
        return;

    float width = (float)GetScreenWidth();
    float height = (float)GetScreenHeight();

    camera->FOV.y = camera->ViewCamera.fovy;

    if(height != 0)
        camera->FOV.x = camera->FOV.y * (width / height);
}

Vector3 FpCameraGetPosition(FpCamera* camera)
{
    return camera->cameraPosition;
}

void FpCameraSetPosition(FpCamera* camera, Vector3 pos)
{
    camera->cameraPosition = pos;
    Vector3 forward = Vector3Subtract(camera->ViewCamera.target, camera->ViewCamera.position);
    camera->ViewCamera.position = camera->cameraPosition;
    camera->ViewCamera.target = Vector3Add(camera->cameraPosition, forward);
}

RLAPI Ray FpCameraGetViewRay(FpCamera* camera)
{
    return (Ray) {camera->cameraPosition, camera->Forward};
}

static float GetSpeedForAxis(FpCamera* camera, FpCameraControls axis, float speed)
{
    if (camera == NULL)
        return 0;

    int key = camera->controlsKey[axis];
    if (key == -1)
        return 0;

    float factor = 1.0f;
    if (IsKeyDown(camera->controlsKey[SPRINT]))
        factor = 2;

    if (IsKeyDown(camera->controlsKey[axis]))
        return speed * GetFrameTime() * factor;

    return 0.0f;
}

void FpCameraUpdate(FpCamera* camera)
{
    if (camera == NULL)
        return;

    if (IsWindowFocused() != camera->focused && camera->useMouse)
    {
        camera->focused = IsWindowFocused();
        if(camera->focused)
        {
            DisableCursor();
        }
        else
        {
            EnableCursor();
        }
    }

    Vector2 mousePositionDelta = GetMouseDelta();

    float direction[MOVE_DOWN + 1] = {GetSpeedForAxis(camera,MOVE_FORWARD, camera->moveSpeed.z),
                                      GetSpeedForAxis(camera,MOVE_BACKWARD, camera->moveSpeed.z),
                                    GetSpeedForAxis(camera,MOVE_RIGHT, camera->moveSpeed.x),
                                    GetSpeedForAxis(camera,MOVE_LEFT, camera->moveSpeed.x),
                                    GetSpeedForAxis(camera,MOVE_UP, camera->moveSpeed.y),
                                    GetSpeedForAxis(camera,MOVE_DOWN, camera->moveSpeed.y)};

    float turnRotation = GetSpeedForAxis(camera, TURN_RIGHT, camera->rotationSpeed.x) - GetSpeedForAxis(camera, TURN_LEFT, camera->rotationSpeed.x);
    float tiltRotation = GetSpeedForAxis(camera, TURN_UP, camera->rotationSpeed.y) - GetSpeedForAxis(camera, TURN_DOWN, camera->rotationSpeed.y);

    if(turnRotation != 0)
        camera->viewAngles.x -= turnRotation * DEG2RAD;
    else if(camera->useMouse && camera->focused)
        camera->viewAngles.x += (mousePositionDelta.x / camera->mouseSensitivity);

        float yFactor = camera->invertY ? -1.0f : 1.0f;

    if (tiltRotation)
        camera->viewAngles.y += yFactor * tiltRotation * DEG2RAD;
    else if (camera->useMouse && camera->focused)
        camera->viewAngles.y += (yFactor * mousePositionDelta.y / camera->mouseSensitivity);

    // Angle clamp
    if (camera->viewAngles.y < camera->minimumViewY * DEG2RAD)
        camera->viewAngles.y = camera->minimumViewY * DEG2RAD;
    else if (camera->viewAngles.y > camera->maximumViewY * DEG2RAD)
        camera->viewAngles.y = camera->maximumViewY * DEG2RAD;

    // Recalculate camera target considering translation and rotation
    Vector3 target = Vector3Transform((Vector3) { 0, 0, 1 }, MatrixRotateZYX((Vector3) { camera->viewAngles.y, -camera->viewAngles.x, 0 }));

    if (camera->allowFlight)
        camera->Forward = target;
    else
        camera->Forward = Vector3Transform((Vector3) { 0, 0, 1 }, MatrixRotateZYX((Vector3) { 0, -camera->viewAngles.x, 0 }));

    camera->Right = (Vector3){ camera->Forward.z * -1.0f, 0, camera->Forward.x };

    camera->cameraPosition = Vector3Add(camera->cameraPosition, Vector3Scale(camera->Forward, direction[MOVE_FORWARD] - direction[MOVE_BACKWARD]));
    camera->cameraPosition = Vector3Add(camera->cameraPosition, Vector3Scale(camera->Right, direction[MOVE_LEFT] - direction[MOVE_RIGHT ]));

    //camera->cameraPosition.y += direction[MOVE_UP] - direction[MOVE_DOWN];

    camera->ViewCamera.position = camera->cameraPosition;

    float eyeOffset = camera->playerEyesPosition;

    if (camera->viewBobbleFreq > 0)
    {
        float swingDelta = (float)(fmax(fabs(direction[MOVE_FORWARD] - direction[MOVE_BACKWARD]), fabs(direction[MOVE_RIGHT] - direction[MOVE_LEFT])));

        camera->currentBobble += swingDelta * camera->viewBobbleFreq;

        static float viewBobbleDampen = 8.0f;

        eyeOffset -= sinf(camera->currentBobble / viewBobbleDampen) * camera->viewBobbleMagnatude;

        camera->ViewCamera.up.x = sinf(camera->currentBobble / (viewBobbleDampen * 2)) * camera->viewBobbleWaverMagnitude;
        camera->ViewCamera.up.z = -sinf(camera->currentBobble / (viewBobbleDampen * 2)) * camera->viewBobbleWaverMagnitude;
    }
    else
    {
        camera->currentBobble = 0;
        camera->ViewCamera.up.x = 0;
        camera->ViewCamera.up.z = 0;
    }

    camera->ViewCamera.position.y += eyeOffset;

    camera->ViewCamera.target.x = camera->ViewCamera.position.x + target.x;
    camera->ViewCamera.target.y = camera->ViewCamera.position.y + target.y;
    camera->ViewCamera.target.z = camera->ViewCamera.position.z + target.z;
}
void FpCameraSetup(FpCamera* camera, float aspect)
{
    rlDrawRenderBatchActive();
    rlMatrixMode(RL_PROJECTION);
    rlPushMatrix();
    rlLoadIdentity();

    if (camera->ViewCamera.projection == CAMERA_PERSPECTIVE)
    {
        double top = RL_CULL_DISTANCE_NEAR * tan(camera->ViewCamera.fovy * 0.5 * DEG2RAD);
        double right = top * aspect;

        rlFrustum(-right, right, -top, top, camera->NearPlane, camera->FarPlane);
    }

    else if(camera->ViewCamera.projection == CAMERA_ORTHOGRAPHIC)
    {
        double top = camera->ViewCamera.fovy / 2.0f;
        double right = top * aspect;

        rlOrtho(-right, right, -top, top, camera->NearPlane, camera->FarPlane);
    }

    rlMatrixMode(RL_MODELVIEW);
    rlLoadIdentity();

    Matrix matView = MatrixLookAt(camera->ViewCamera.position, camera->ViewCamera.target, camera->ViewCamera.up);

    rlMultMatrixf(MatrixToFloatV(matView).v);

    rlEnableDepthTest();
}

void FpCameraBeginMode3D(FpCamera* camera)
{
    if(camera == NULL)
        return;

    float aspect = (float)GetScreenWidth() / (float)GetScreenHeight();
    FpCameraSetup(camera, aspect);
}

void FpCameraEndMode3D()
{
    EndMode3D();
}

/*void SetupCamera()
{
    SetCameraMoveControls(KEY_W, KEY_S, KEY_D, KEY_A, 0, 0);

    DisableCursor();
    playerCamera.position = (Vector3) {5.0f, 3.0f, 0.0f};
    playerCamera.target = (Vector3){ 0.0f, 0.85f, 0.0f};
    playerCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    playerCamera.fovy = 60.0f;
    playerCamera.projection = CAMERA_PERSPECTIVE;

   SetCameraMode(playerCamera, CAMERA_FIRST_PERSON);
} // will be deleted but as a failsave

void CameraLogic()
{
    UpdateCamera(&playerCamera);
}*/
