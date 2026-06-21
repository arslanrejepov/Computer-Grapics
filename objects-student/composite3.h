#pragma once
#include "object3d.h"
#include "cube.h"

class composite3 : public object3d
{
private:
    cube* base;

public:
    composite3();
};