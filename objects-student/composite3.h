#pragma once
#include "object3d.h"
#include "cube.h"
#include "cylinder.h"

class composite3 : public object3d
{
private:
    cube* base;
    cylinder* barrel;
    cylinder* legA;
    cylinder* legB;
    cylinder* legC;

public:
    composite3();
};