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

    // --- Bottom cap - closes the bottom ---
    disc* bottomCap = new disc(24, 1);
    bottomCap->setColour(0.25, 0.25, 0.28, 1.0);
    bottomCap->setPosition(0, -4.2, 0);
    bottomCap->setRotation('x', -90);
    bottomCap->setScale(0.6);
    bottomCap->makeInsideFaces();
    bottomCap->setParent(this);

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

    // --- Round window (torus - blue) ---
    torus* window = new torus(16, 16, 0.35, 0.08);
    window->setColour(0.1, 0.2, 0.8, 1.0);
    window->setPosition(0.5, 1.0, 0.0);
    window->setRotation('z', 90);
    window->setParent(this);
}