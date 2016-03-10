#include "ServiceLocator.h"

namespace Hive
{

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

	void ServiceLocator::registerComponentManager(IComponentManager* componentManager) {
		_componentManager = componentManager;
	}
	IComponentManager* ServiceLocator::getComponentManager() {
		return _componentManager;
	}

	void ServiceLocator::registerUIManager(IUIManager* uiManager) {
		_uiManager = uiManager;
	}
	IUIManager* ServiceLocator::getUIManager() {
		return _uiManager;
	}

	void ServiceLocator::registerGameWorld(IGameWorld* gameWorld)
	{
		game_world = gameWorld;
	}

	IGameWorld* ServiceLocator::getGameWorld()
	{
		return game_world;
	}
}