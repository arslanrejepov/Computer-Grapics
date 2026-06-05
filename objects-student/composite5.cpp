// composite5.cpp — Soldier (Minecraft style, military uniform)
#include "prefix.h"
#include "composite5.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

composite5::composite5()
{
    setName("soldier");

    // --- Head (skin) ---
    head = new cube();
    head->setColour(0.87f, 0.70f, 0.55f, 1.0f);    // skin
    head->setDeformation(0.55f, 0.55f, 0.55f);
    head->setPosition(0.0f, 3.55f, 0.0f);
    head->setParent(this);

    // --- Military cap (dark green, flat cube on top of head) ---
    cap = new cube();
    cap->setColour(0.18f, 0.25f, 0.10f, 1.0f);     // dark military green
    cap->setDeformation(0.60f, 0.15f, 0.60f);
    cap->setPosition(0.0f, 4.25f, 0.0f);
    cap->setParent(this);

    // --- Cap brim (slightly wider, thinner, forward) ---
    capBrim = new cube();
    capBrim->setColour(0.18f, 0.25f, 0.10f, 1.0f);
    capBrim->setDeformation(0.65f, 0.07f, 0.25f);
    capBrim->setPosition(0.0f, 4.12f, 0.65f);
    capBrim->setParent(this);

    // --- Body (military green jacket) ---
    body = new cube();
    body->setColour(0.25f, 0.33f, 0.15f, 1.0f);    // olive military green
    body->setDeformation(0.55f, 0.75f, 0.30f);
    body->setPosition(0.0f, 2.25f, 0.0f);
    body->setParent(this);

    // --- Left arm (green sleeve) ---
    armL = new cube();
    armL->setColour(0.25f, 0.33f, 0.15f, 1.0f);
    armL->setDeformation(0.25f, 0.70f, 0.25f);
    armL->setPosition(-0.85f, 2.25f, 0.0f);
    armL->setParent(this);

    // --- Right arm (green sleeve) ---
    armR = new cube();
    armR->setColour(0.25f, 0.33f, 0.15f, 1.0f);
    armR->setDeformation(0.25f, 0.70f, 0.25f);
    armR->setPosition(0.85f, 2.25f, 0.0f);
    armR->setParent(this);

    // --- Left leg (dark green trousers) ---
    legL = new cube();
    legL->setColour(0.18f, 0.22f, 0.10f, 1.0f);    // darker green trousers
    legL->setDeformation(0.25f, 0.75f, 0.25f);
    legL->setPosition(-0.30f, 0.75f, 0.0f);
    legL->setParent(this);

    // --- Right leg ---
    legR = new cube();
    legR->setColour(0.18f, 0.22f, 0.10f, 1.0f);
    legR->setDeformation(0.25f, 0.75f, 0.25f);
    legR->setPosition(0.30f, 0.75f, 0.0f);
    legR->setParent(this);

    // --- Boots left (dark brown) ---
    bootL = new cube();
    bootL->setColour(0.20f, 0.13f, 0.07f, 1.0f);   // dark brown boots
    bootL->setDeformation(0.28f, 0.20f, 0.35f);
    bootL->setPosition(-0.30f, 0.05f, 0.05f);
    bootL->setParent(this);

    // --- Boots right ---
    bootR = new cube();
    bootR->setColour(0.20f, 0.13f, 0.07f, 1.0f);
    bootR->setDeformation(0.28f, 0.20f, 0.35f);
    bootR->setPosition(0.30f, 0.05f, 0.05f);
    bootR->setParent(this);

    gShapeVector.push_back(this);
}