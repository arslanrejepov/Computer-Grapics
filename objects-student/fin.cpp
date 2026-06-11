// *****************************************************************************************
// KXC354 - Computer Graphics & Animation - 2014
// Assignment 1 & 2
// 3D Engine Code
// *****************************************************************************************
//
// Author: Tony Gray
//
// cube.cpp
//
// This file defines the class for cube objects



// -----------------------------------------------------------------------------------------
// includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "fin.h"
#include "utility.h"



// -----------------------------------------------------------------------------------------
// globals
// -----------------------------------------------------------------------------------------
extern vector<object3d*> gShapeVector;



// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------

fin::fin()
{
    setName("fin");
    setColour(0.15, 0.85, 0.35, 1.0);

    // 4 vertices for a triangular prism
    vertexCount = 6;
    faceCount = 5;
    polygonCount = 5;

    vertices.resize(vertexCount);
    faces.resize(faceCount);

    // Front triangle
    vertices[0].set(-1.0f, 1.0f, 1.0f);
    vertices[1].set(-1.0f, -1.0f, 1.0f);
    vertices[2].set(1.0f, -1.0f, 1.0f);

    // Back triangle (same shape, pushed back)
    vertices[3].set(-1.0f, 1.0f, -0.5f);
    vertices[4].set(-1.0f, -1.0f, -0.5f);
    vertices[5].set(1.0f, -1.0f, -0.5f);

    // Front face (triangle)
    faces[0].init(0, 1, 2);
    // Back face (triangle)
    faces[1].init(3, 5, 4);
    // Bottom face (quad)
    faces[2].init(1, 4, 5, 2);
    // Left face (quad)
    faces[3].init(0, 3, 4, 1);
    // Right/top face (two triangles would be better, but keeping simple)
    faces[4].init(0, 2, 5, 3);

    calculateNormals();

    gShapeVector.push_back(this);
}


