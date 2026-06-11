// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================
//
// Author: Tony Gray
//
// firesys.cpp
//
// This file defines the class for a fire system (derived from the particle system)



// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "prefix.h"
#include "firesys.h"




// -----------------------------------------------------------------------------------------
// constructor
// -----------------------------------------------------------------------------------------
firesys::firesys(unsigned int n) : particlesys(n)
{
	// the particle system constructor has done the basic initialisation,
	// so all we need to do here is the custom stuff for the fire system
	minLifeSpan = 2.0;	
	maxLifeSpan = 3.0;	
		
	minBirthSize = 0.05;
	maxBirthSize = 0.2;
	maxSize = 1.5;
	
	minBirthSpeed = 0.1;
	maxBirthSpeed = 0.4;
	minMaxSpeed = 0.4;
	maxMaxSpeed = 1.3;
	
	birthRate = 50;
	
	acceleration = true;
	accelerationVectr.set(0.0, 0.9, 0.0);

	useAlpha = true;

	texture *tex = new texture("flames.png", kContinuousTone, kMipmaps);
	setTexture(tex);
	framesWide = 2;

}




// -----------------------------------------------------------------------------------------
// (re)initialise a single fire particle
// -----------------------------------------------------------------------------------------
void firesys::initParticle(unsigned int i)
{
	// to the basic initialisation from the base class
	particlesys::initParticle(i);
	
	// increase the spread of the base of the flames
	particles[i].position.add(randomFloat(-0.3, 0.3), 0, 0);
	
	// make the flames have a greater chance of left-right movement to give
	// the base of the flames some spread
	vectr direction;
	direction.set(randomFloat(-8, 8), randomFloat(.1, .1), 0.0);
	direction.reduceToUnit();

	// set velocity from speed and direction
	float speed = randomFloat(minBirthSpeed, maxBirthSpeed);
	particles[i].velocity = direction * speed;
	
	// set the rate that flame particles can grow
	particles[i].growthRate = 0.5;
}






