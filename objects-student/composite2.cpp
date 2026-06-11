#include "prefix.h"
#include "composite2.h"
#include "utility.h"

extern vector<object3d*> gShapeVector;

composite2::composite2()
{
    setName("tank");

    // HULL — tcube, 3 wide x 5 long x 2 tall
    hull = new tcube();
    hull->setColour(0.33f, 0.40f, 0.14f, 1.0f);
    hull->setDeformation(3.0f, 1.0f, 4.0f);
    hull->setParent(this);

    // TRACKS
    trackL = new extrusion("tankTrackProfile.txt", "tankTrackPath.txt");
    trackL->setColour(0.10f, 0.10f, 0.10f, 1.0f);
    trackL->setDeformation(0.30f, 0.45f, 1.0f);
    trackL->setPosition(-3.3f, -1.1f, -3.25f);
    trackL->setParent(hull);

    trackR = new extrusion("tankTrackProfile.txt", "tankTrackPath.txt");
    trackR->setColour(0.10f, 0.10f, 0.10f, 1.0f);
    trackR->setDeformation(0.30f, 0.45f, 1.0f);
    trackR->setPosition(3.3f, -1.1f, -3.25f);
    trackR->setParent(hull);

    // WHEELS — 3 left, 3 right
    float wheelZ[3] = { -2.2f, 0.0f, 2.2f };
    float wheelY = -1.65f;

    for (int i = 0; i < 3; i++)
    {
        wheelL[i] = new torus(16, 16, 0.7f, 0.35f);
        wheelL[i]->setColour(0.14f, 0.13f, 0.11f, 1.0f);
        wheelL[i]->setRotation('z', 90.0f);
        wheelL[i]->setPosition(-4.05f, wheelY, wheelZ[i]);
        wheelL[i]->setParent(this);

        wheelR[i] = new torus(16, 16, 0.7f, 0.35f);
        wheelR[i]->setColour(0.14f, 0.13f, 0.11f, 1.0f);
        wheelR[i]->setRotation('z', 90.0f);
        wheelR[i]->setPosition(4.05f, wheelY, wheelZ[i]);
        wheelR[i]->setParent(this);
    }


    // TURRET
    turret = new tcube();
    turret->setColour(0.25f, 0.31f, 0.10f, 1.0f);
    turret->setDeformation(1.4f, 0.6f, 1.4f);
    turret->setPosition(0.0f, 1.6f, 0.0f);
    turret->setParent(this);

    // TURRET HEAD
    turretHead = new tcube();
    turretHead->setColour(0.22f, 0.22f, 0.20f, 1.0f);
    turretHead->setDeformation(0.7f, 0.3f, 0.7f);
    turretHead->setParent(turret);  // this -> turret
    turretHead->setPosition(0.0f, 0.9f, 0.0f);  // turretiň merkezinde

    // CANNON
    cannon = new sweep("tankCannon.txt", 16);
    cannon->setColour(0.25f, 0.25f, 0.24f, 1.0f);
    cannon->setRotation('x', -90.0f);
    cannon->setPosition(0.0f, 2.5f, 0.0f);
    cannon->setParent(this);

    gShapeVector.push_back(this);
}

void composite2::hide()
{
    invisible = true;
    hull->hide();
    turret->hide();
    cannon->hide();
    turretHead->hide();
    trackL->hide();
    trackR->hide();
    for (int i = 0; i < 3; i++)
    {
        wheelL[i]->hide();
        wheelR[i]->hide();
    }
}

void composite2::show()
{
    invisible = false;
    hull->show();
    turret->show();
    cannon->show();
    turretHead->show();
    trackL->show();
    trackR->show();
    for (int i = 0; i < 3; i++)
    {
        wheelL[i]->show();
        wheelR[i]->show();
    }
}

void composite2::setBodyTexture(texture* t)
{
    hull->setTexture(t);
}
void composite2::setTurretRotation(float x, float z) {
    turret->setRotation('x', x, 'z', z);
}
