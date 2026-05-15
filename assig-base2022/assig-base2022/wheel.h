#pragma once
#include "object3d.h"

class wheel : public object3d
{
public:
    wheel(double radius, int density);

private:
    void builder(double radius, int density);
};