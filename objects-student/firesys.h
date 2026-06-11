// =========================================================================================
// KXC354 - Computer Graphics & Animation - 2013
// Assignment 1 & 2
// 3D Engine Code
// =========================================================================================
//
// Author: Tony Gray
//
// firesys.h
//
// This file declares the class for a fire system (derived from the particle system)


#ifndef _firesys_H
#define _firesys_H



// -----------------------------------------------------------------------------------------
// application includes
// -----------------------------------------------------------------------------------------
#include "particlesys.h"
#include "utility.h"
#include "texture.h"




// -----------------------------------------------------------------------------------------
// class declaration
// -----------------------------------------------------------------------------------------
class firesys : public particlesys
{
	public:
							firesys(unsigned int particleCount);
				
			virtual void	initParticle(unsigned int i);

};


#endif // _firesys_H

