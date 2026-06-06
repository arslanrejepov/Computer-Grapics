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
#define ROCKET_START_Z    -35.0f
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
composite5* person;

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
    ground->setScale(200);
    ground->setRotation('x', -90);
    ground->setPosition(0, 0, 0);
    ground->setTexture(groundTex, 4, 4);  

 
    rocket = new composite1();
    tank = new composite2();
    launcher = new composite3();
    person = new composite5();

    launcher->setPosition(ROCKET_START_X, 0, ROCKET_START_Z);
    person->setPosition(-130.0f, 0.5f, -40.0f);
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

    rocket->setPosition(ROCKET_START_X, ROCKET_START_Y, ROCKET_START_Z);
    rocket->setRotation('y', 90);
    rocket->show();

    tank->setPosition(TANK_X, TANK_Y, TANK_Z);
    tank->setRotation('y', 180);
    tank->show();

    launcher->setPosition(ROCKET_START_X, 0, ROCKET_START_Z);
    person->setPosition(-130.0f, 0.5f, -40.0f);
    person->setRotation('y', 0);

    gCamera.setPosition(TANK_X + 20, TANK_Y + 8, TANK_Z - 20);
    gCamera.setTarget(TANK_X, TANK_Y, TANK_Z);
}

void animateForNextFrame(float time, long frame)
{
    // -------------------------------------------------------
    // PHASE 1: 0-8 sek — Kamera tankyň daşynda aýlanýar
    // -------------------------------------------------------
    if (time <= 8.0f)
    {
        float angle = interpolate(0.0f, 8.0f, 0.0f, 90.0f);
        float camX = TANK_X + 25.0f * cos_d(angle);
        float camZ = TANK_Z - 25.0f * sin_d(angle);
        gCamera.setPosition(camX, TANK_Y + 10, camZ);
        gCamera.setTarget(TANK_X, TANK_Y, TANK_Z);
    }

    // -------------------------------------------------------
    // PHASE 2: 8-15 sek — Kamera esgere geçýär, esger ýöreýär
    // -------------------------------------------------------
    else if (time <= 15.0f)
    {
        // Kamera esgere geçýär (smooth)
        float camX = interpolate(8.0f, 15.0f, TANK_X + 25.0f * cos_d(90.0f), -28.0f);
        float camZ = interpolate(8.0f, 15.0f, TANK_Z - 25.0f * sin_d(90.0f), -10.0f);
        float camY = interpolate(8.0f, 15.0f, TANK_Y + 10, TANK_Y + 6);
        gCamera.setPosition(camX, camY, camZ);
        gCamera.setTarget(-35.0f, 2.0f, -15.0f);

        // Esger öňe ýöreýär: 8-12 sek aralygynda
        if (time <= 12.0f)
        {
            float personZ = interpolate(8.0f, 12.0f, -15.0f, -5.0f);
            person->setPosition(-130.0f, 0.5f, personZ);
        }
    }

    // -------------------------------------------------------
    // PHASE 3: 15-20 sek — Esger el galdyrýar (signal)
    // -------------------------------------------------------
    else if (time <= 20.0f)
    {
        gCamera.setPosition(-20.0f, 6.0f, -5.0f);
        gCamera.setTarget(-35.0f, 2.0f, -5.0f);

        // El ýokardan aşak — composite5-de armAngle bar bolsa
        float armAngle = interpolate(15.0f, 20.0f, -80.0f, 0.0f);
        person->setArmAngle(armAngle);
    }

    // -------------------------------------------------------
    // PHASE 4: 20-45 sek — Raketa uçýar, kamera yzarlaýar
    // -------------------------------------------------------
    else if (time <= 45.0f)
    {
        float t = time - 20.0f;          // 0..25
        float dur = 25.0f;

        float newX = interpolate(20.0f, 45.0f, ROCKET_START_X, TANK_X);
        float arcAngle = interpolate(20.0f, 45.0f, 0.0f, 180.0f);
        float newY = ROCKET_START_Y + ROCKET_PEAK_Y * sin_d(arcAngle);
        float newZ = interpolate(20.0f, 45.0f, ROCKET_START_Z, TANK_Z);
        rocket->setPosition(newX, newY, newZ);

        float tilt = interpolate(0.0f, 45.0f, 90.0f, -135.0f);
        rocket->setRotation('y', -90, 'z', tilt);

        // Kamera raketany yzarlaýar
        float rx, ry, rz;
        rocket->getPosition(rx, ry, rz);
        gCamera.setPosition(rx - 12, ry + 6, rz + 16);
        gCamera.setTarget(rx, ry, rz);
    }

    // -------------------------------------------------------
    // PHASE 5: 45+ sek — Partlama, ikisi gizlenýär
    // -------------------------------------------------------
    else
    {
        rocket->hide();
        tank->hide();

        // Kamera partlama ýerini görkezýär
        gCamera.setPosition(TANK_X - 15, TANK_Y + 10, TANK_Z - 20);
        gCamera.setTarget(TANK_X, TANK_Y, TANK_Z);
    }

    if (time >= 50.0f)
        gProgramMode = kpmFinished;
}