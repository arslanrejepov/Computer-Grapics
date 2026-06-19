#ifndef _COMPOSITE2_H
#define _COMPOSITE2_H

#include "object3d.h"
#include "tcube.h"
#include "sweep.h"
#include "extrusion.h"
#include "torus.h"
#include "cube.h"

class composite2 : public object3d
{
private:
    tcube* hull;
    tcube* turret;
    sweep* cannon;
    torus* wheelL[3];
    torus* wheelR[3];
    extrusion* trackL;
    extrusion* trackR;
    tcube* turretHead;
    cube* discL[3];
    cube* discR[3];

public:
    composite2();
    virtual ~composite2() {}
    virtual void hide();
    virtual void show();

    void setBodyTexture(texture* t);
    void setWheelAngle(float angle);
    void setTurretTexture(texture* t) { turret->setTexture(t); }
};

#endif