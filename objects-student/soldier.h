#pragma once
#include "prefix.h"
#include "object3d.h"
#include "cube.h"

class soldier : public object3d
{
private:
    cube* head;
    cube* cap;
    cube* capBrim;
    cube* body;
    cube* armL;
    cube* armR;
    cube* legL;
    cube* legR;
    cube* bootL;
    cube* bootR;
    object3d* armRPivot;

public:
    soldier();

    void setArmAngle(float angle);
    void setLegAngle(float angle);

    virtual void hide();
    virtual void show();
};