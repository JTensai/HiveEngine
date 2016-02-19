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

	class ServiceLocator {
	private:
		static ServiceLocator* _instance;
		IInputManager* _inputManager;
		IDataManager* _dataManager;
		IComponentManager* _componentManager;
		IUIManager* _uiManager;

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
	};

}