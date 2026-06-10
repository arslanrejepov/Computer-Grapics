#include "prefix.h"
#include "soldier.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

soldier::soldier()
{
    setName("soldier");

    head = new cube();
    head->setColour(0.87f, 0.70f, 0.55f, 1.0f);
    head->setDeformation(0.55f, 0.55f, 0.55f);
    head->setPosition(0.0f, 3.55f, 0.0f);
    head->setParent(this);

    cap = new cube();
    cap->setColour(0.18f, 0.25f, 0.10f, 1.0f);
    cap->setDeformation(0.60f, 0.15f, 0.60f);
    cap->setPosition(0.0f, 4.25f, 0.0f);
    cap->setParent(this);

    capBrim = new cube();
    capBrim->setColour(0.18f, 0.25f, 0.10f, 1.0f);
    capBrim->setDeformation(0.65f, 0.07f, 0.25f);
    capBrim->setPosition(0.0f, 4.12f, 0.65f);
    capBrim->setParent(this);

    body = new cube();
    body->setColour(0.25f, 0.33f, 0.15f, 1.0f);
    body->setDeformation(0.55f, 0.75f, 0.30f);
    body->setPosition(0.0f, 2.25f, 0.0f);
    body->setParent(this);

    armL = new cube();
    armL->setColour(0.25f, 0.33f, 0.15f, 1.0f);
    armL->setDeformation(0.25f, 0.70f, 0.25f);
    armL->setPosition(-0.85f, 2.25f, 0.0f);
    armL->setParent(this);

    // Right arm pivot at shoulder
    armRPivot = new object3d();
    armRPivot->setPosition(0.85f, 3.0f, 0.0f);
    armRPivot->setParent(this);

    armR = new cube();
    armR->setColour(0.25f, 0.33f, 0.15f, 1.0f);
    armR->setDeformation(0.25f, 0.70f, 0.25f);
    armR->setOffset(0.0f, -0.75f, 0.0f);
    armR->setParent(armRPivot);

    legL = new cube();
    legL->setColour(0.18f, 0.22f, 0.10f, 1.0f);
    legL->setDeformation(0.25f, 0.75f, 0.25f);
    legL->setPosition(-0.30f, 0.75f, 0.0f);
    legL->setParent(this);

    legR = new cube();
    legR->setColour(0.18f, 0.22f, 0.10f, 1.0f);
    legR->setDeformation(0.25f, 0.75f, 0.25f);
    legR->setPosition(0.30f, 0.75f, 0.0f);
    legR->setParent(this);

    bootL = new cube();
    bootL->setColour(0.20f, 0.13f, 0.07f, 1.0f);
    bootL->setDeformation(0.28f, 0.20f, 0.35f);
    bootL->setPosition(-0.30f, 0.05f, 0.05f);
    bootL->setParent(this);

    bootR = new cube();
    bootR->setColour(0.20f, 0.13f, 0.07f, 1.0f);
    bootR->setDeformation(0.28f, 0.20f, 0.35f);
    bootR->setPosition(0.30f, 0.05f, 0.05f);
    bootR->setParent(this);

    gShapeVector.push_back(this);
}

void soldier::setArmAngle(float angle)
{
    armRPivot->setRotation('x', -angle);
}

void soldier::setLegAngle(float angle)
{
    legL->setRotation('x', angle);
    legR->setRotation('x', -angle);
}

void soldier::hide()
{
    head->hide();
    cap->hide();
    capBrim->hide();
    body->hide();
    armL->hide();
    armR->hide();
    legL->hide();
    legR->hide();
    bootL->hide();
    bootR->hide();
}

void soldier::show()
{
    head->show();
    cap->show();
    capBrim->show();
    body->show();
    armL->show();
    armR->show();
    legL->show();
    legR->show();
    bootL->show();
    bootR->show();
}