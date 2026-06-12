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
#include "composite3.h"
#include "composite5.h"
#include "firesys.h"
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

#define ROCKET_START_X   -130.0f
#define ROCKET_START_Y    4.2f
#define ROCKET_START_Z    50.0f
#define ROCKET_PEAK_Y    25.0f

#define TANK_X            100.0f
#define TANK_Y            2.5f
#define TANK_Z           50.0f

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
composite3* launcher;
firesys* fire;
snd* bgMusic;

light* ambient, * light0, * light1, * light2;

// -----------------------------------------------------------------------------------------
// constructScene
// -----------------------------------------------------------------------------------------
void constructScene()
{
    ambient = new light(GL_LIGHT_MODEL_AMBIENT);
    light0 = new light(GL_LIGHT0);
    light1 = new light(GL_LIGHT1);
    gSky = new skybox("sky14-");
    groundTex = new texture("battlefield.png");
    ground = new plane();
    ground->setScale(500);
    ground->setRotation('x', -90);
    ground->setPosition(0, 0, 0);
    ground->setTexture(groundTex, 4, 4);


    rocket = new composite1();
	rocket->setBodyTexture(new texture("rocket.png"));
    tank = new composite2();
	tank->setBodyTexture(new texture("tankhull.png"));
	tank->setTurretTexture(new texture("tanktorret.png"));
    launcher = new composite3();

    launcher->setPosition(ROCKET_START_X, 0, ROCKET_START_Z);

    fire = new firesys(100);
    fire->setPosition(0, 3, 0);  // tank-yň üstünde
    bgMusic = new snd("sound1.wav");
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
    bgMusic->stopSound();
    bgMusic->setPlayPoint(0.0);
    rocket->setPosition(ROCKET_START_X, ROCKET_START_Y, ROCKET_START_Z);
    rocket->setRotation('y', 90);
    rocket->show();

    tank->setPosition(TANK_X, TANK_Y, TANK_Z);
    tank->setRotation('y', 180);
    tank->show();
    fire->setPosition(TANK_X, TANK_Y + 3.0f, TANK_Z + 40.0f);
    launcher->setPosition(ROCKET_START_X, 0, ROCKET_START_Z);


    gCamera.setPosition(7, TANK_Y + 17, TANK_Z + 3);
    gCamera.setTarget(TANK_X, TANK_Y, TANK_Z);
}

void animateForNextFrame(float time, long frame)
{
    // SAZ
    if (time > 0.0f && time < 0.1f)
        bgMusic->startSound();
    if (time >= 38.0f)
        bgMusic->stopSound();

    // -------------------------------------------------------
    // PHASE 1: 0-10s — Tank öňe ýöreýär, kamera garşy tarapda
    // -------------------------------------------------------
    if (time <= 10.0f)
    {
        float tankZ = interpolate(0.0f, 10.0f, TANK_Z, TANK_Z + 40.0f);
        tank->setPosition(TANK_X, TANK_Y, tankZ);

        // Kamera tankyn öň tarapynda (garşylykly)
        gCamera.setPosition(TANK_X - 25.0f, TANK_Y + 8.0f, tankZ + 50.0f);
        gCamera.setTarget(TANK_X, TANK_Y, tankZ);
    }
    // -------------------------------------------------------
    // PHASE 2: 10-16s — Kamera launcher görkezýär
    // -------------------------------------------------------
    else if (time <= 16.0f)
    {
        tank->setPosition(TANK_X, TANK_Y, TANK_Z + 40.0f);

        gCamera.setPosition(ROCKET_START_X - 15.0f, ROCKET_START_Y + 8.0f, ROCKET_START_Z + 5.0f);
        gCamera.setTarget(ROCKET_START_X + 5.0f, ROCKET_START_Y + 3.0f, ROCKET_START_Z);
    }
    // -------------------------------------------------------
    // PHASE 3: 16-32s — Raketa uçýar
    // -------------------------------------------------------
    else if (time <= 32.0f)
    {
        rocket->show();

        float t = time - 16.0f;

        float progress;
        if (t <= 12.0f)
            progress = (t / 16.0f) * 0.7f;
        else
            progress = 0.7f + ((t - 12.0f) / 4.0f) * 0.3f;

        float newX = ROCKET_START_X + progress * (TANK_X - ROCKET_START_X);
        float newZ = ROCKET_START_Z + progress * (TANK_Z + 40.0f - ROCKET_START_Z);
        float arcAngle = progress * 180.0f;
        float newY = ROCKET_START_Y + ROCKET_PEAK_Y * sin_d(arcAngle);

        rocket->setPosition(newX, newY, newZ);

        float tilt = interpolate(16.0f, 32.0f, -45.0f, -120.0f);
        rocket->setRotation('y', -90, 'z', tilt);

        float rx, ry, rz;
        rocket->getPosition(rx, ry, rz);
        gCamera.setPosition(rx - 15.0f, ry + 6.0f, rz + 5.0f);
        gCamera.setTarget(rx + 8.0f, ry - 2.0f, rz);

        if (time >= 31.8f)
            rocket->hide();
    }
    // -------------------------------------------------------
    // PHASE 4: 32-38s — Raketa degdi, tank + raketa yitya, ot galya
    // -------------------------------------------------------
    else if (time <= 38.0f)
    {
        rocket->hide();
        tank->hide();
        fire->show();
        fire->animate();

        gCamera.setPosition(TANK_X - 20.0f, TANK_Y + 8.0f, TANK_Z + 40.0f);
        gCamera.setTarget(TANK_X, TANK_Y + 3.0f, TANK_Z + 40.0f);
    }
    // -------------------------------------------------------
    // PHASE 5: 38s+ — Gutarýar
    // -------------------------------------------------------
    else
    {
        fire->animate();
        gCamera.setPosition(TANK_X - 20.0f, TANK_Y + 8.0f, TANK_Z + 40.0f);
        gCamera.setTarget(TANK_X, TANK_Y + 3.0f, TANK_Z + 40.0f);
    }

    if (time >= 38.0f)
        gProgramMode = kpmFinished;
}