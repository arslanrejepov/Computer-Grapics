#pragma once
#include "object3d.h"
#include "sweep.h"
#include "extrusion.h"
#include "cylinder.h"
#include "sphere.h"
#include "tcube.h"
#include "fin.h"
#include "pyramid.h"
#include "utility.h"

class composite1 : public object3d
{
public:
    composite1();
    void setSensorAngle(float angle);
    virtual void hide();
    virtual void show();
    void setBodyTexture(texture* t);
    void setLightAngle(float angle);
private:
    fin* fins[4];
    pyramid* s_nose;
    tcube* s_body;
    sweep* s_nozzle;
    extrusion* antenna;
    sphere* antennaTipL, * antennaTipR;
};

