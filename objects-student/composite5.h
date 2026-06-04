#pragma once
#include "object3d.h"
#include "cube.h"
#include "sphere.h"

// composite5 — Minecraft Person
class composite5 : public object3d
{
private:
    cube* head;
    cube* body;
    cube* armL;
    cube* armR;
    cube* legL;
    cube* legR;

public:
    composite5();
};