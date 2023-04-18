#include "../scene manager/scenestate.h"
#include "../engine/headers/player_camera.h"
#include "scene_headers/scene_gametest.h"
#include "../engine/headers/generics.h"
#include "../engine/headers/physics.h"
#include <ode/ode.h>
//dSpaceID space;
//dWorldID world;
//dGeomID plane;
//dJointGroupID contactGroup;
//dBodyID obj[MAX_OBJ];

FpCamera cam;
FpCamera stackCam;

int waitForSecond = 0;

float yaw = 0.0f;
float pitch = 0.0f;

bool drawInModel = true;
bool devMode = false;

Vector2 viewmodelRotation = {0};

Vector3 playerPosition = {0.0f, 0.0f, -4.0f};
Vector3 cubePosition = { 0.0f, -2.0f, 0.0f };
Vector3 testModPos = {0.0f, 10.7f, 4.0f};
Vector3 testMapPos = {0.0f, 10.7f, 0.0f};

Model playerCollider = {0};
Model playerVM = {0};
Model roadBlock = {0};
Model weirdCube = {0};
Model weirdShpere = {0};


Texture testTexture = {0};

LoadTestAssetsReq()
{
    FpCameraInit(&cam, 45, (Vector3) { 10, 15, -20.0 });
    FpCameraInit(&stackCam, 45, (Vector3) { 0, 0, 0 });
    cam.moveSpeed.z = 10.0f;
    cam.moveSpeed.x = 5.0f;
    cam.viewBobbleMagnatude = 0.05f;
    cam.viewBobbleFreq = 14.0f;
    cam.allowFlight = false;

    stackCam.moveSpeed.z = 0;
    stackCam.moveSpeed.x = 0;

    playerCollider = LoadModel("src/assets/models/physproperty/player/player_collider.glb");
    roadBlock = LoadModel ("src/assets/models/prop/d_map_npc_behavior-propinfo.glb");
    weirdCube = LoadModel("src/assets/models/props/base/weirdcube.glb");
    weirdShpere = LoadModel("src/assets/models/props/base/weirdcube.glb");
    playerVM = LoadModel("src/assets/models/viewmodel/weapon/hands_vm.glb");

    SetFilterModel(roadBlock, TEXTURE_FILTER_TRILINEAR);

    printf("\nSuccessfully loaded game data and scene.");
}



TestAnimSys(void)
{
    unsigned int animCount = 0;
    unsigned int animIndex = 0;
    unsigned int animCurrentFrame = 0;

    //ModelAnimation *diyuAnimSrc = LoadModelAnimations("src/assets/models/attempt/plswork.glb", &animCount);

    while(drawInModel == true)
    {
        playerPosition = (Vector3){cam.cameraPosition.x, 10.7f, cam.cameraPosition.z};
        cam.cameraPosition.y = playerPosition.y + 2;

        TestRun();
        TestRunLogics();
    }
        UnloadModel(roadBlock);
        SwitchSceneGame(2);
}

TestRun(void)
{
    FpCameraUpdate(&cam);

    //check collision
   // dSpaceCollide(space, 0, &NearCallBack);
    //step
    //dWorldQuickStep(world, 1./60);
    //dJointGroupEmpty(contactGroup);

    BeginDrawing();

            ClearBackground(WHITE);

            FpCameraBeginMode3D(&stackCam);

                DrawModel(playerVM, stackCam.cameraPosition, 1.0f, WHITE);

            FpCameraEndMode3D(&stackCam);

            FpCameraBeginMode3D(&cam);
            //BeginMode3D(playerCamera);

            /*for (int i = 0; i < MAX_OBJ; i++)
            {
                float* pos = (float *) dBodyGetPosition(obj[i]);
                float* rot = (float *) dBodyGetRotation(obj[i]);

                if(i<MAX_OBJ/2)
                {
                    SetTransform(pos, rot, &weirdCube.transform);
                    DrawModel(weirdCube, (Vector3){0, 10, 0}, 1.0f, BLACK);
                }
            }*/
                //DrawCube(cubePosition, 10,5,10, BLACK);
                DrawModel(roadBlock, testMapPos, 1.0f, WHITE);
                DrawModel(playerCollider, playerPosition, 1.0f, BLACK);

                DrawGrid(20, 5.0f);

            FpCameraEndMode3D(&cam);

            DrawText("This is a developer build.", 20, 10, 40, BLACK);
            DrawText("This branch of KAPPA GAME TOOLS will be classified as \"Densei demo\" Branch", 25, 50, 20, BLACK);


    EndDrawing();

}

/*LoadTestPhysReq(void)
{
    dInitODE2(0);//init
    world = dWorldCreate();
    space = dHashSpaceCreate(NULL);
    contactGroup = dJointGroupCreate(0);
    dWorldSetGravity(world, 0, -9.8, 0);
    //plane = dCreatePlane(space, 0, 1, 0, 0);
    plane = dCreateBox(space, 0, 0, 0);
    dGeomBoxSetLengths(plane, 100, 1, 100);

    for(int i = 0; i < MAX_OBJ; i++)
    {
        obj[i] = dBodyCreate(world);
        dGeomID geom;
        dMatrix3 R;
        dMass m;

        if (i<MAX_OBJ/2)
        {
            geom = dCreateBox(space, 1, 1, 1);
            dMassSetBoxTotal(&m, 1, 0.5, 0.5, 0.5);
        }
        else
        {
            geom = dCreateSphere(space,0.5);
            dMassSetSphereTotal(&m, 1, 0.5);
        }

        dBodySetPosition(obj[i],
                         dRandReal() * 10 - 5, 4+(i/10), dRandReal() * 10-5 );

        dRFromAxisAndAngle(R, dRandReal() * 2.0 - 1.0,
                            dRandReal() * 2.0 - 1.0,
                            dRandReal() * 2.0 - 1.0,
                            dRandReal() * 10.0 - 5.0);
        dBodySetRotation(obj[i], R);
        //body mass
        dBodySetMass(obj[i], &m);
        dGeomSetBody(geom, obj[i]);

    }
}*/

TestRunLogics(void)
{
    stackCam.useMouse = false;

}


/*void NearCallBack(void *data, dGeomID o1, dGeomID o2)
{
    (void)data;
    int i;

    dBodyID b1 = dGeomGetBody(o1);
    dBodyID b2 = dGeomGetBody(o2);
    if(b1 && b2 && dAreConnectedExcluding(b1, b2, dJointTypeContact))
        return;

    dContact contact[MAX_CONTACTS];
    for(i = 0; i < MAX_CONTACTS; i++)
    {
        contact[i].surface.mode = dContactBounce;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.mu2 = 0;
        contact[i].surface.bounce = 0.5;
        contact[i].surface.bounce_vel = 0.5;
    }
    int numc = dCollide(o1, o2, MAX_CONTACTS, &contact[0].geom,
                        sizeof(dContact));
    if (numc){
        dMatrix3 RI;
        dRSetIdentity(RI);
        for(i = 0; i < numc; i++){
            dJointID c =
                dJointCreateContact(world, contactGroup, contact + i);
            dJointAttach(c, b1, b2);
        }
    }
}*/
