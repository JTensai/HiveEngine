#pragma once

#include "IInputManager.h"
#include "IDataManager.h"
#include "IComponentManager.h"
#include "IUIManager.h"
#include "IGraphics.h"

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
		IGraphics* graphics;

		ServiceLocator();

	public:
		static ServiceLocator* get_instance();

		static void register_input_manager(IInputManager* input_manager);
		static IInputManager* get_input_manager();

		static void register_data_manager(IDataManager* data_manager);
		static IDataManager* get_data_manager();

		static void register_component_manager(IComponentManager* component_manager);
		static IComponentManager* get_component_manager();

		static void register_ui_manager(IUIManager* ui_manager);
		static IUIManager* get_ui_manager();

		static void register_game_world(IGameWorld* game_world);
		static IGameWorld* get_game_world();

		static void register_graphics(IGraphics* graphics);
		static IGraphics* get_graphics();
	};

}