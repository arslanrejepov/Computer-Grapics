#include "composite2.h"

#include <cmath>

static const float OLIVE[3] = { 0.40f, 0.42f, 0.18f };
static const float DARK_GREEN[3] = { 0.22f, 0.30f, 0.10f };
static const float DARK_GREY[3] = { 0.25f, 0.25f, 0.25f };
static const float BLACK[3] = { 0.10f, 0.10f, 0.10f };

composite2::composite2()
{
    _body = new sweep("resources/tankBody.txt", 24);
    _body->setColour(OLIVE[0], OLIVE[1], OLIVE[2]);
    _body->setParent(this);

    _turret = new sweep("resources/tankTurret.txt", 24);
    _turret->setColour(DARK_GREEN[0], DARK_GREEN[1], DARK_GREEN[2]);
    _turret->setOffset(0.0f, 3.0f, 0.0f);
    _turret->setParent(this);

    _barrel = new cylinder(12);
    _barrel->setColour(DARK_GREY[0], DARK_GREY[1], DARK_GREY[2]);
    _barrel->setRotation('x', 90.0f);
    _barrel->setOffset(0.0f, 4.5f, 2.5f);
    _barrel->setParent(this);

    _hatch = new disc(16, 0.8f);
    _hatch->setColour(DARK_GREY[0], DARK_GREY[1], DARK_GREY[2]);
    _hatch->setOffset(0.0f, 5.9f, 0.0f);
    _hatch->setParent(this);

    _trackLeft = new extrusion("resources/tankTrackProfile.txt",
        "resources/tankTrackPath.txt");
    _trackLeft->setColour(BLACK[0], BLACK[1], BLACK[2]);
    _trackLeft->makeInsideFaces();
    _trackLeft->setOffset(-5.2f, -3.4f, -4.5f);
    _trackLeft->setParent(this);

    _trackRight = new extrusion("resources/tankTrackProfile.txt",
        "resources/tankTrackPath.txt");
    _trackRight->setColour(BLACK[0], BLACK[1], BLACK[2]);
    _trackRight->makeInsideFaces();
    _trackRight->setOffset(5.2f, -3.4f, -4.5f);
    _trackRight->setParent(this);

    float wheelZ[4] = { -3.0f, -1.0f, 1.0f, 3.0f };
    float wheelX[2] = { -5.2f,  5.2f };

    for (int side = 0; side < 2; ++side)
    {
        for (int w = 0; w < 4; ++w)
        {
            int i = side * 4 + w;
            _wheel[i] = new disc(16, 1.0f);
            _wheel[i]->setColour(DARK_GREY[0], DARK_GREY[1], DARK_GREY[2]);
            _wheel[i]->setRotation('z', 90.0f);
            _wheel[i]->setOffset(wheelX[side], -2.8f, wheelZ[w]);
            _wheel[i]->setParent(this);
        }
    }
}

void composite2::update(double t)
{
    float angle = 30.0f * (float)sin(t * 0.5);
    _turret->setRotation('y', angle);
    _hatch->setRotation('y', angle);
}