#pragma once
#include "pSysModule.h"
class ModuleInitialRotationRate :
	public pSysModule
{
public:
	ModuleInitialRotationRate();
	~ModuleInitialRotationRate();

	virtual void update(std::vector<Particle>* particles);
};

