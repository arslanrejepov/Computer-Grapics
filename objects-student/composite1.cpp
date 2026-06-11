#include "prefix.h"
#include "composite1.h"


composite1::composite1()
{
    setName("rocket");

    s_body = new tcube();
    s_body->setColour(0.75, 0.75, 0.80, 1.0);
    s_body->setDeformation(0.55, 3.5, 0.55);
    s_body->setParent(this);

    s_nose = new pyramid();
    s_nose->setParent(s_body);
    s_nose->setColour(0.1, 0.3, 0.1, 1.0);
    s_nose->setDeformation(0.55, 1.0, 0.55);
    s_nose->setPosition(0.0, 4.5, 0.0);

    s_nozzle = new sweep("rocketNozzle.txt", 24);
    s_nozzle->setParent(s_body);
    s_nozzle->setColour(0.25, 0.25, 0.28, 1.0);
    s_nozzle->setPosition(0.0, -0.5, 0.0);



    for (int i = 0; i < 4; i++)
    {
        fins[i] = new fin;
        fins[i]->setParent(s_body);
        fins[i]->setColour(0.9, 0.1, 0.1, 1.0);
        fins[i]->setDeformation(0.4, 0.5, 0.1);
    }
    fins[0]->setRotation('y', -90);
    fins[0]->setPosition(0.0, -3.0, 0.95);

    fins[1]->setPosition(0.0, -3.0, -0.95);
    fins[1]->setRotation('y', 90);

    fins[2]->setPosition(0.95, -3.0, 0.0);
    fins[2]->setRotation('y', 360);

    fins[3]->setRotation('y', 180);
    fins[3]->setPosition(-0.95, -3.0, 0.0);

    antennaTipL = new sphere(8);
    antennaTipL->setParent(s_body);
    antennaTipL->setColour(0.9, 0.1, 0.1, 1.0);
    antennaTipL->setScale(0.15);
    antennaTipL->setPosition(0.15, 2.0, 0.65);

    antennaTipR = new sphere(8);
    antennaTipR->setParent(s_body);
    antennaTipR->setColour(0.1, 0.1, 0.9, 1.0);
    antennaTipR->setScale(0.15);
    antennaTipR->setPosition(-0.15, 2.0, 0.65);

}

void composite1::hide()
{
    invisible = true;
    s_body->hide();
    s_nose->hide();
    s_nozzle->hide();
    fins[0]->hide();
    fins[1]->hide();
    fins[2]->hide();
    fins[3]->hide();
	antennaTipL->hide();
	antennaTipR->hide();    
}

void composite1::show()
{
    invisible = false;
    s_body->show();
    s_nose->show();
    s_nozzle->show();
    fins[0]->show();
    fins[1]->show();
    fins[2]->show();
    fins[3]->show();
}


void composite1::setBodyTexture(texture* t)
{
    s_body->setTexture(t);
}

void composite1::setLightAngle(float angle)
{
    antennaTipL->setRotation('x', angle);
    antennaTipR->setRotation('x', angle);
}