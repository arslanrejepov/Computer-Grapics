// *****************************************************************************************
// KXC354 - Computer Graphics & Animation
// Assignment 1 & 2
// *****************************************************************************************
//
// composite2.h
// Tank composite object
//

#ifndef _COMPOSITE2_H
#define _COMPOSITE2_H

#include "object3d.h"
#include "sweep.h"
#include "extrusion.h"
#include "disc.h"
#include "torus.h"

class composite2 : public object3d
{
private:
    // Hull and turret
    sweep* hull;
    sweep* turret;
    sweep* cannon;

    // 6 wheels: 3 left, 3 right
    sweep* wheelL[3];
    sweep* wheelR[3];

    // Tracks (left and right)
    extrusion* trackL;
    extrusion* trackR;

    // Turret ring / base detail
    torus* turretRing;

public:
    composite2();
    virtual     ~composite2() {}
};

#endif // _COMPOSITE2_H