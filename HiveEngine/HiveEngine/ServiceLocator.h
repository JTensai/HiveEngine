#pragma once

#include "IInputManager.h"
#include "IDataManager.h"
#include "IComponentManager.h"

class ServiceLocator {
private:
	static ServiceLocator* _instance;
	IInputManager* _inputManager;
	IDataManager* _dataManager;
	IComponentManager* _componentManager;

	ServiceLocator();

public:
	static ServiceLocator* getInstance();

	void registerInputManager(IInputManager* inputManager);
	IInputManager* getInputManager();

	void registerDataManager(IDataManager* dataManager);
	IDataManager* getDataManager();

	void registerComponentManager(IComponentManager* componentManager);
	IComponentManager* getComponentManager();
};
