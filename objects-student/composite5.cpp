// composite5.cpp — Minecraft Person (Steve)
#include "prefix.h"
#include "composite5.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

composite5::composite5()
{
    setName("steve");

    // --- Head ---
    head = new cube();
    head->setColour(0.87f, 0.70f, 0.55f, 1.0f);    // skin colour
    head->setDeformation(0.55f, 0.55f, 0.55f);
    head->setPosition(0.0f, 3.55f, 0.0f);
    head->setParent(this);

    // --- Body ---
    body = new cube();
    body->setColour(0.25f, 0.35f, 0.70f, 1.0f);    // blue shirt
    body->setDeformation(0.55f, 0.75f, 0.30f);
    body->setPosition(0.0f, 2.25f, 0.0f);
    body->setParent(this);

    // --- Left arm ---
    armL = new cube();
    armL->setColour(0.25f, 0.35f, 0.70f, 1.0f);
    armL->setDeformation(0.25f, 0.70f, 0.25f);
    armL->setPosition(-0.85f, 2.25f, 0.0f);
    armL->setParent(this);

    // --- Right arm ---
    armR = new cube();
    armR->setColour(0.25f, 0.35f, 0.70f, 1.0f);
    armR->setDeformation(0.25f, 0.70f, 0.25f);
    armR->setPosition(0.85f, 2.25f, 0.0f);
    armR->setParent(this);

    // --- Left leg ---
    legL = new cube();
    legL->setColour(0.20f, 0.15f, 0.10f, 1.0f);    // dark trousers
    legL->setDeformation(0.25f, 0.75f, 0.25f);
    legL->setPosition(-0.30f, 0.75f, 0.0f);
    legL->setParent(this);

    // --- Right leg ---
    legR = new cube();
    legR->setColour(0.20f, 0.15f, 0.10f, 1.0f);
    legR->setDeformation(0.25f, 0.75f, 0.25f);
    legR->setPosition(0.30f, 0.75f, 0.0f);
    legR->setParent(this);

    gShapeVector.push_back(this);
}