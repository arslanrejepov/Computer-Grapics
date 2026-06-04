// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// scene.cpp
// *****************************************************************************************

#include "prefix.h"
#include "constants.h"
#include "utility.h"
#include "light.h"
#include "camera.h"
#include "texture.h"
#include "scene.h"
#include "snd.h"
#include "skybox.h"
#include "fog.h"
#include "viewfrustum.h"

#include "sweep.h"
#include "extrusion.h"
#include "cube.h"
#include "sphere.h"
#include "torus.h"
#include "terrain.h"
#include "billboard.h"
#include "plane.h"
#include "tsphere.h"
#include "cylinder.h"
#include "disc.h"

#include "composite1.h"
#include "composite2.h"

// -----------------------------------------------------------------------------------------
// global variables
// -----------------------------------------------------------------------------------------
extern ProgramMode      gProgramMode;
extern cameraClass      gCamera;
extern object3d* gSky;
extern fog* gFog;
extern viewfrustum* gViewFrustum;
extern float            gCurrentFrameTime;
extern vector<object3d*> gShapeVector;
typedef vector<object3d*>::iterator shapeVectorIterator;

// -----------------------------------------------------------------------------------------
// Animation timings
// -----------------------------------------------------------------------------------------
// Phase 1: 0 -> 5 sec   rocket rises straight up
// Phase 2: 5 -> 15 sec  rocket flies toward tank
// Phase 3: 15 sec       impact — both hidden

#define ROCKET_START_X   -20.0f
#define ROCKET_START_Y    4.2f
#define ROCKET_START_Z    0.0f
#define ROCKET_PEAK_Y    25.0f

#define TANK_X            20.0f
#define TANK_Y            2.0f
#define TANK_Z            0.0f

#define T_LAUNCH_END      5.0f
#define T_IMPACT         15.0f
#define T_END            20.0f

// -----------------------------------------------------------------------------------------
// Object pointers
// -----------------------------------------------------------------------------------------
plane* ground;
texture* groundTex;
composite1* rocket;
composite2* tank;

light* ambient, * light0, * light1, * light2;

// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
void constructScene()
{
    ambient = new light(GL_LIGHT_MODEL_AMBIENT);
    light0 = new light(GL_LIGHT0);
    light1 = new light(GL_LIGHT1);

    groundTex = new texture("battlefield.png");
    ground = new plane();
    ground->setScale(80);
    ground->setRotation('x', -90);
    ground->setPosition(0, 0, 0);
    ground->setTexture(groundTex, 1, 1);  

    rocket = new composite1();
    tank = new composite2();
}

// -----------------------------------------------------------------------------------------
// resetScene
// -----------------------------------------------------------------------------------------
void resetScene()
{
    ambient->setColour(0.4f, 0.4f, 0.4f, 1.0f);

    light0->turnOn();
    light0->setPosition(-10, 20, 10);
    light0->setColour(0.8f, 0.8f, 0.8f, 1.0f);
    light0->setSpecularColour(0.8f, 0.8f, 0.8f, 1.0f);
    light0->makePositional();
    light0->setLinearAttenuation(0.01f);

    light1->turnOn();
    light1->setPosition(10, 15, -10);
    light1->setColour(0.6f, 0.6f, 0.6f, 1.0f);
    light1->setSpecularColour(0.6f, 0.6f, 0.6f, 1.0f);
    light1->makePositional();
    light1->setLinearAttenuation(0.01f);

    // Rocket launch pad position
    rocket->setPosition(ROCKET_START_X, ROCKET_START_Y, ROCKET_START_Z);
    rocket->setRotation('y', 90);
    rocket->show();

    // Tank position — faces rocket
    tank->setPosition(TANK_X, TANK_Y, TANK_Z);
    tank->setRotation('y', 180);
    tank->show();

    // Camera starts behind rocket
    gCamera.setPosition(ROCKET_START_X - 10, ROCKET_START_Y + 5, ROCKET_START_Z + 15);
    gCamera.setTarget(ROCKET_START_X, ROCKET_START_Y, ROCKET_START_Z);
}

// -----------------------------------------------------------------------------------------
// animateForNextFrame
// -----------------------------------------------------------------------------------------
void animateForNextFrame(float time, long frame)
{
    if (time <= T_IMPACT)
    {
        float newX = speedUp(0.0f, T_IMPACT, ROCKET_START_X, TANK_X);
        float arcT = interpolate(0.0f, T_IMPACT, 0.0f, 180.0f);
        float newY = ROCKET_START_Y + ROCKET_PEAK_Y * sin_d(arcT);

        rocket->setPosition(newX, newY, ROCKET_START_Z);

        float tilt = interpolate(0.0f, T_IMPACT, 0.0, -135.0);
        rocket->setRotation('y', -90, 'z', tilt);
    }
    else
    {
        rocket->hide();
        tank->hide();
    }

    float rx, ry, rz;
    rocket->getPosition(rx, ry, rz);
    gCamera.setPosition(rx - 12, ry + 6, rz + 16);
    gCamera.setTarget(rx, ry, rz);

    if (time >= T_END)
        gProgramMode = kpmFinished;
}