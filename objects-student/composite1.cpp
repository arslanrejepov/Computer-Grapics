#include "prefix.h"
#include "composite1.h"
#include "sweep.h"
#include "extrusion.h"
#include "torus.h"
#include "disc.h"

composite1::composite1()
{
    setName("rocket");
    setPosition(0, 0, 0);

    // --- Rocket body (silver) ---
    sweep* body = new sweep("rocketBody.txt", 24);
    body->setColour(0.75, 0.75, 0.80, 1.0);
    body->makeInsideFaces();
    body->setParent(this);

    // --- Nose cone (red) ---
    sweep* nose = new sweep("rocketNose.txt", 24);
    nose->setColour(0.9, 0.1, 0.1, 1.0);
    nose->makeInsideFaces();
    nose->setParent(this);

    // --- Exhaust nozzle (dark grey) ---
    sweep* nozzle = new sweep("rocketNozzle.txt", 24);
    nozzle->setColour(0.25, 0.25, 0.28, 1.0);
    nozzle->makeInsideFaces();
    nozzle->setParent(this);

 

    // --- Fin 1 - touching body, rotated 0 deg ---
    extrusion* fin1 = new extrusion("rocketFinProfile.txt", "rocketFinPath.txt");
    fin1->setColour(0.9, 0.1, 0.1, 1.0);
    fin1->makeInsideFaces();
    fin1->setRotation('y', 0);
    fin1->setParent(this);

    // --- Fin 2 - 120 deg ---
    extrusion* fin2 = new extrusion("rocketFinProfile.txt", "rocketFinPath.txt");
    fin2->setColour(0.9, 0.1, 0.1, 1.0);
    fin2->makeInsideFaces();
    fin2->setRotation('y', 120);
    fin2->setParent(this);

    // --- Fin 3 - 240 deg ---
    extrusion* fin3 = new extrusion("rocketFinProfile.txt", "rocketFinPath.txt");
    fin3->setColour(0.9, 0.1, 0.1, 1.0);
    fin3->makeInsideFaces();
    fin3->setRotation('y', 240);
    fin3->setParent(this);

}