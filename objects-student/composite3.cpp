// composite3.cpp — Rocket Launcher
#include "prefix.h"
#include "composite3.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

composite3::composite3()
{
    setName("launcher");

    // --- Base platform ---
    base = new cube();
    base->setColour(0.30f, 0.30f, 0.30f, 1.0f);
    base->setDeformation(2.5f, 0.3f, 2.5f);
    base->setPosition(0.0f, 0.3f, 0.0f);
    base->setParent(this);

    // --- Vertical barrel ---
    barrel = new cylinder(12);
    barrel->setColour(0.20f, 0.20f, 0.22f, 1.0f);
    barrel->setDeformation(0.2f, 3.0f, 0.2f);
    barrel->setPosition(0.0f, 3.3f, 0.0f);
    barrel->setParent(this);

    // --- Support leg 1 ---
    legA = new cylinder(8);
    legA->setColour(0.35f, 0.32f, 0.28f, 1.0f);
    legA->setDeformation(0.1f, 1.5f, 0.1f);
    legA->setRotation('z', 30.0f);
    legA->setPosition(-1.0f, 1.0f, 0.0f);
    legA->setParent(this);

    // --- Support leg 2 ---
    legB = new cylinder(8);
    legB->setColour(0.35f, 0.32f, 0.28f, 1.0f);
    legB->setDeformation(0.1f, 1.5f, 0.1f);
    legB->setRotation('z', -30.0f);
    legB->setPosition(1.0f, 1.0f, 0.0f);
    legB->setParent(this);

    // --- Support leg 3 ---
    legC = new cylinder(8);
    legC->setColour(0.35f, 0.32f, 0.28f, 1.0f);
    legC->setDeformation(0.1f, 1.5f, 0.1f);
    legC->setRotation('x', 30.0f);
    legC->setPosition(0.0f, 1.0f, -1.0f);
    legC->setParent(this);

    gShapeVector.push_back(this);
}