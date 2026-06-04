// composite4.cpp — House
#include "prefix.h"
#include "composite4.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

composite4::composite4()
{
    setName("house");

    // --- Main walls ---
    walls = new cube();
    walls->setColour(0.85f, 0.78f, 0.60f, 1.0f);
    walls->setDeformation(3.0f, 2.0f, 2.5f);
    walls->setPosition(0.0f, 2.0f, 0.0f);
    walls->setParent(this);

    // --- Roof (cube egilip) ---
    roof = new cube();
    roof->setColour(0.55f, 0.20f, 0.10f, 1.0f);
    roof->setDeformation(3.2f, 0.8f, 2.7f);
    roof->setPosition(0.0f, 4.8f, 0.0f);
    roof->setParent(this);

    // --- Door ---
    door = new cube();
    door->setColour(0.40f, 0.25f, 0.10f, 1.0f);
    door->setDeformation(0.5f, 0.9f, 0.05f);
    door->setPosition(0.0f, 0.9f, 2.55f);
    door->setParent(this);

    // --- Left window ---
    windowL = new cube();
    windowL->setColour(0.55f, 0.80f, 0.95f, 1.0f);
    windowL->setDeformation(0.5f, 0.45f, 0.05f);
    windowL->setPosition(-1.5f, 2.3f, 2.55f);
    windowL->setParent(this);

    // --- Right window ---
    windowR = new cube();
    windowR->setColour(0.55f, 0.80f, 0.95f, 1.0f);
    windowR->setDeformation(0.5f, 0.45f, 0.05f);
    windowR->setPosition(1.5f, 2.3f, 2.55f);
    windowR->setParent(this);

    gShapeVector.push_back(this);
}