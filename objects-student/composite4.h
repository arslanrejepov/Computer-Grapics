#pragma once
#include "object3d.h"
#include "cube.h"

class composite4 : public object3d
{
private:
    cube* walls;
    cube* roof;
    cube* door;
    cube* windowL;
    cube* windowR;

public:
    composite4();
};