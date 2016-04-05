#include "ServiceLocator.h"

namespace Hive
{

	ServiceLocator* ServiceLocator::instance = nullptr;
	ServiceLocator::ServiceLocator() {
		input_manager = nullptr;
	}

	ServiceLocator* ServiceLocator::get_instance() {
		if (!instance) {
			instance = new ServiceLocator();
		}
		return instance;
	}

	void ServiceLocator::register_input_manager(IInputManager* input_manager) {
		get_instance()->input_manager = input_manager;
	}
	IInputManager* ServiceLocator::get_input_manager() {
		return get_instance()->input_manager;
	}

	void ServiceLocator::register_data_manager(IDataManager* data_manager) {
		get_instance()->data_manager = data_manager;
	}
	IDataManager* ServiceLocator::get_data_manager() {
		return get_instance()->data_manager;
	}

	void ServiceLocator::register_component_manager(IComponentManager* component_manager) {
		get_instance()->component_manager = component_manager;
	}
	IComponentManager* ServiceLocator::get_component_manager() {
		return get_instance()->component_manager;
	}

	void ServiceLocator::register_ui_manager(IUIManager* ui_manager) {
		get_instance()->ui_manager = ui_manager;
	}
	IUIManager* ServiceLocator::get_ui_manager() {
		return get_instance()->ui_manager;
	}

	void ServiceLocator::register_game_world(IGameWorld* game_world)
	{
		get_instance()->game_world = game_world;
	}
	IGameWorld* ServiceLocator::get_game_world()
	{
		return get_instance()->game_world;
	}

	void ServiceLocator::register_graphics(IGraphics* graphics)
	{
		get_instance()->graphics = graphics;
	}
	IGraphics* ServiceLocator::get_graphics()
	{
		return get_instance()->graphics;
	}
}