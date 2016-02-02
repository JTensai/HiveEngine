#pragma once

#include "IInputManager.h"
#include "IDataManager.h"

class ServiceLocator {
private:
	static ServiceLocator* _instance;
	IInputManager* _inputManager;
	IDataManager* _dataManager;

	ServiceLocator();

public:
	static ServiceLocator* getInstance();

	void registerInputManager(IInputManager* inputManager);
	IInputManager* getInputManager();

	void registerDataManager(IDataManager* dataManager);
	IDataManager* getDataManager();
};
