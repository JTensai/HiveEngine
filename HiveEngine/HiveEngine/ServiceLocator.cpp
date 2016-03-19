#include "ServiceLocator.h"

namespace Hive
{

	ServiceLocator* ServiceLocator::instance = NULL;
	ServiceLocator::ServiceLocator() {
		input_manager = NULL;
	}

	ServiceLocator* ServiceLocator::getInstance() {
		if (!instance) {
			instance = new ServiceLocator();
		}
		return instance;
	}

	void ServiceLocator::registerInputManager(IInputManager* inputManager) {
		getInstance()->input_manager = inputManager;
	}
	IInputManager* ServiceLocator::getInputManager() {
		return getInstance()->input_manager;
	}

	void ServiceLocator::registerDataManager(IDataManager* dataManager) {
		getInstance()->data_manager = dataManager;
	}
	IDataManager* ServiceLocator::getDataManager() {
		return getInstance()->data_manager;
	}

	void ServiceLocator::registerComponentManager(IComponentManager* componentManager) {
		getInstance()->component_manager = componentManager;
	}
	IComponentManager* ServiceLocator::getComponentManager() {
		return getInstance()->component_manager;
	}

	void ServiceLocator::registerUIManager(IUIManager* uiManager) {
		getInstance()->ui_manager = uiManager;
	}
	IUIManager* ServiceLocator::getUIManager() {
		return getInstance()->ui_manager;
	}

	void ServiceLocator::registerGameWorld(IGameWorld* gameWorld)
	{
		getInstance()->game_world = gameWorld;
	}

	IGameWorld* ServiceLocator::getGameWorld()
	{
		return getInstance()->game_world;
	}
}