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
		static ServiceLocator* instance;
		IInputManager* input_manager;
		IDataManager* data_manager;
		IComponentManager* component_manager;
		IUIManager* ui_manager;
		IGameWorld* game_world;

		ServiceLocator();

	public:
		static ServiceLocator* getInstance();

		static void registerInputManager(IInputManager* inputManager);
		static IInputManager* getInputManager();

		static void registerDataManager(IDataManager* dataManager);
		static IDataManager* getDataManager();

		static void registerComponentManager(IComponentManager* componentManager);
		static IComponentManager* getComponentManager();

		static void registerUIManager(IUIManager* uiManager);
		static IUIManager* getUIManager();

		static void registerGameWorld(IGameWorld* gameWorld);
		static IGameWorld* getGameWorld();
	};

}