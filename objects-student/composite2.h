#pragma once
#include "prefix.h"
#include "object3d.h"
#include "sweep.h"
#include "extrusion.h"
#include "disc.h"
#include "cylinder.h"

class composite2 : public object3d
{
public:
    composite2();
    void update(double t);

private:
    // Hull
    sweep* _body;

    // Turret
    sweep* _turret;
    cylinder* _barrel;
    disc* _hatch;

    // Tracks
    extrusion* _trackLeft;
    extrusion* _trackRight;

    // Wheels (4 per side)
    disc* _wheel[8];
};