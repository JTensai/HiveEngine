#pragma once

#include "Data.h"

class IDataManager {
public:
	virtual int loadCoreData() { return 1; }
	virtual int loadXMLData(char* filename) { return 1; }

	virtual DAbility* getAbilityData(int handle) { return 0; }
	virtual DActor* getActorData(int handle) { return 0; }
	virtual DBehavior* getBehaviorData(int handle) { return 0; }
	virtual DEffect* getEffectData(int handle) { return 0; }
	virtual DUnit* getUnitData(int handle) { return 0; }
	virtual DValidator* getValidatorData(int handle) { return 0; }
};