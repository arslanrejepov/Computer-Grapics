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

    gShapeVector.push_back(this);
}