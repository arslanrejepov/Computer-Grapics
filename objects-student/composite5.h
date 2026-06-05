#pragma once
#include "object3d.h"
#include "cube.h"

class composite5 : public object3d
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

public:
    composite5();
};