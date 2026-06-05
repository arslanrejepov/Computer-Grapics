    // *****************************************************************************************
    // KXC354 - Computer Graphics & Animation
    // Assignment 1 & 2
    // *****************************************************************************************
    //
    // composite2.cpp  —  Tank
    //
    // COORDINATE SYSTEM:
    //   Tank sits with its bottom at y = -2.0 (hull bottom)
    //   Ground should be placed at y = -2.0 so tank rests on it
    //
    // PARTS:
    //   Hull          — wide swept body,    army green
    //   Turret        — dome on top,        darker olive
    //   TurretRing    — torus detail ring,  dark metal
    //   Cannon        — long barrel,        steel grey
    //   Wheels x6     — 3L + 3R,            black rubber
    //   Tracks x2     — left + right,       dark charcoal with tread detail colour

    #include "prefix.h"
    #include "composite2.h"
    #include "utility.h"

    extern vector<object3d*> gShapeVector;

    composite2::composite2()
    {
        setName("tank");

        // -----------------------------------------------------------------------
        // HULL  — the main tank body
        //   Sweep builds around Y axis. Hull profile goes from y=-2 to y=+2.
        //   Colour: classic army olive green
        // -----------------------------------------------------------------------
        hull = new sweep("tankHull.txt", 28);
        hull->setColour(0.33f, 0.40f, 0.14f, 1.0f);
        hull->makeInsideFaces();        // olive army green
        hull->setParent(this);

        // -----------------------------------------------------------------------
        // TRACKS  — dark rubber belt on each side, sitting flush with hull bottom
        //   Extrusion profile is XY rectangle, path extrudes along Z.
        //   setDeformation squashes it into a flat belt shape.
        //   Positioned to hug each side of the hull at wheel level.
        //   Colour: very dark charcoal (rubber)
        // -----------------------------------------------------------------------
        trackL = new extrusion("tankTrackProfile.txt", "tankTrackPath.txt");
        trackL->setColour(0.10f, 0.10f, 0.10f, 1.0f);      // near-black rubber
        trackL->setDeformation(0.30f, 0.45f, 1.0f);
        trackL->setPosition(-3.25f, -1.65f, -3.25f);
        trackL->setParent(this);

        trackR = new extrusion("tankTrackProfile.txt", "tankTrackPath.txt");
        trackR->setColour(0.10f, 0.10f, 0.10f, 1.0f);
        trackR->setDeformation(0.30f, 0.45f, 1.0f);
        trackR->setPosition(3.25f, -1.65f, -3.25f);
        trackR->setParent(this);

        // -----------------------------------------------------------------------
        // WHEELS  — 3 left, 3 right  (road wheels)
        //   Sweep makes a disc-shaped wheel around Y.
        //   Rotate 90° on Z so the axle runs left-right (X axis).
        //   Left side:  x = -3.5
        //   Right side: x = +3.5
        //   Height:     y = -1.65  (bottom of hull)
        //   Spread:     z = -2.2, 0.0, +2.2
        //   Colour: dark rubber black with slight warm tint
        // -----------------------------------------------------------------------
        float wheelZ[3] = { -2.2f, 0.0f, 2.2f };
        float wheelY = -1.65f;

        for (int i = 0; i < 3; i++)
        {
            wheelL[i] = new sweep("tankWheel.txt", 20);
            wheelL[i]->setColour(0.14f, 0.13f, 0.11f, 1.0f);   // dark rubber
            wheelL[i]->setRotation('z', 90.0f);
            wheelL[i]->setPosition(-3.5f, wheelY, wheelZ[i]);
            wheelL[i]->makeInsideFaces();
            wheelL[i]->setParent(this);

             wheelR[i] = new sweep("tankWheel.txt", 20);
            wheelR[i]->setColour(0.14f, 0.13f, 0.11f, 1.0f);
            wheelR[i]->setRotation('z', 90.0f);
            wheelR[i]->setPosition(3.5f, wheelY, wheelZ[i]);
            wheelR[i]->makeInsideFaces();
            wheelR[i]->setParent(this);
        }

        // -----------------------------------------------------------------------
        // TURRET  — dome sitting on top of the hull
        //   Profile goes y=-0.5 (base) to y=+1.3 (top).
        //   Positioned at y=+2.0 so its base aligns with hull top.
        //   Colour: slightly darker / more saturated olive than hull
        // -----------------------------------------------------------------------
        turret = new sweep("tankTurret.txt", 24);
        turret->setColour(0.25f, 0.31f, 0.10f, 1.0f);      // darker olive
        turret->setPosition(0.0f, 2.0f, 0.0f);
        turret->makeInsideFaces();
        turret->setParent(this);

        // -----------------------------------------------------------------------
        // TURRET RING  — torus at the hull/turret junction, gives detail line
        //   Colour: dark steel grey (metal ring)
        // -----------------------------------------------------------------------
        turretRing = new torus(20, 20, 1.55f, 0.10f);
        turretRing->setColour(0.22f, 0.22f, 0.20f, 1.0f);  // dark steel
        turretRing->setPosition(0.0f, 2.05f, 0.0f);
        turretRing->setParent(this);

        // -----------------------------------------------------------------------
        // CANNON  — steel barrel pointing forward (+Z)
        //   Sweep profile is along Y; rotate -90 on X to point along +Z.
        //   Positioned at front of turret, mid height of dome.
        //   Colour: steel grey (slightly lighter than wheels)
        // -----------------------------------------------------------------------
        cannon = new sweep("tankCannon.txt", 16);
        cannon->setColour(0.25f, 0.25f, 0.24f, 1.0f);      // steel grey
        cannon->setRotation('x', -90.0f);
        cannon->setPosition(0.0f, 3.1f, 0.8f);
        cannon->makeInsideFaces();
        cannon->setParent(this);

        // -----------------------------------------------------------------------
        // Register composite on the shape vector
        // -----------------------------------------------------------------------
        gShapeVector.push_back(this);
    }