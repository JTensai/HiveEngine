#pragma once

#include "IInputManager.h"

class ServiceLocator {
private:
	static ServiceLocator* _instance;
	IInputManager* _inputManager;

	ServiceLocator();

public:
	static ServiceLocator* getInstance();
	void registerInputManager(IInputManager* inputManager);
	IInputManager* getInputManager();
};
