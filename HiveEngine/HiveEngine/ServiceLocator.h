#pragma once

#include "IInputManager.h"
#include "IDataManager.h"
#include "IComponentManager.h"
#include "IUIManager.h"

namespace Hive
{
	//Forward declarations
	class IInputManager;
	class IDataManager;
	class IComponentManager;
	class IUIManager;
	class IGameWorld;

	class ServiceLocator {
	private:
		static ServiceLocator* _instance;
		IInputManager* _inputManager;
		IDataManager* _dataManager;
		IComponentManager* _componentManager;
		IUIManager* _uiManager;
		IGameWorld* game_world;

		ServiceLocator();

	public:
		static ServiceLocator* getInstance();

		void registerInputManager(IInputManager* inputManager);
		IInputManager* getInputManager();

		void registerDataManager(IDataManager* dataManager);
		IDataManager* getDataManager();

		void registerComponentManager(IComponentManager* componentManager);
		IComponentManager* getComponentManager();

		void registerUIManager(IUIManager* uiManager);
		IUIManager* getUIManager();

		void registerGameWorld(IGameWorld* gameWorld);
		IGameWorld* getGameWorld();
	};

}