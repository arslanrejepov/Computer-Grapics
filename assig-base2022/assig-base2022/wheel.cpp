// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// wheel.cpp
//
// A wheel object: flat disc shape with top face, bottom face, and side quads.
// Height = 2 units (-1 to +1 on Y axis), origin at centre.
// Constructor: wheel(double radius, int density)
// -----------------------------------------------------------------------------------------

#include "prefix.h"
#include "wheel.h"
#include "utility.h"        // provides cos_d() and sin_d()

extern vector<object3d*> gShapeVector;

// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
wheel::wheel(double radius, int density) : object3d()
{
    setName("wheel");
    builder(radius, density);
}

// -----------------------------------------------------------------------------------------
// builder - constructs the display list
// -----------------------------------------------------------------------------------------
void wheel::builder(double radius, int density)
{
    // create a display list and start recording
    listName = glGenLists(1);
    if (listName == 0) fatal("wheel constructor couldn't create an OpenGL list");
    glNewList(listName, GL_COMPILE);

    // ── TOP FACE (triangle fan, normal pointing up +Y) ───────────────────
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);          // centre top

    for (int i = 0; i <= density; i++)
    {
        float angle = i * (360.0f / density);
        float x = (float)(cos_d(angle) * radius);
        float z = (float)(sin_d(angle) * radius);
        glVertex3f(x, 1.0f, z);
    }
    glEnd();

    // ── BOTTOM FACE (triangle fan, normal pointing down -Y) ───────────────
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);         // centre bottom

    for (int i = 0; i <= density; i++)
    {
        // reversed winding so normal faces downward
        float angle = i * (360.0f / density);
        float x = (float)(cos_d(-angle) * radius);
        float z = (float)(sin_d(-angle) * radius);
        glVertex3f(x, -1.0f, z);
    }
    glEnd();

    // ── SIDE FACES (quad strip around the circumference) ──────────────────
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= density; i++)
    {
        float angle = i * (360.0f / density);
        float x = (float)(cos_d(angle) * radius);
        float z = (float)(sin_d(angle) * radius);

        // outward normal (no Y component - it's vertical)
        glNormal3f((float)cos_d(angle), 0.0f, (float)sin_d(angle));

        glVertex3f(x, 1.0f, z);    // top edge
        glVertex3f(x, -1.0f, z);    // bottom edge
    }
    glEnd();

    // stop recording
    glEndList();

    // register with the shape vector so it receives draw messages
    gShapeVector.push_back(this);
}