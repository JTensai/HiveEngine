#pragma once

#include <vector>

#include "Particle.h"
class pSysModule
{
public:
	pSysModule();
	~pSysModule();
	virtual void update(std::vector<Particle>* particles)=0;
};

