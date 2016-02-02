#include "ServiceLocator.h"

ServiceLocator* ServiceLocator::_instance = NULL;
ServiceLocator::ServiceLocator() {
	_inputManager = NULL;
}

ServiceLocator* ServiceLocator::getInstance() {
	if (!_instance) {
		_instance = new ServiceLocator();
	}
	return _instance;
}

void ServiceLocator::registerInputManager(IInputManager* inputManager) {
	_inputManager = inputManager;
}
IInputManager* ServiceLocator::getInputManager() {
	return _inputManager;
}

void ServiceLocator::registerDataManager(IDataManager* dataManager) {
	_dataManager = dataManager;
}
IDataManager* ServiceLocator::getDataManager() {
	return _dataManager;
}