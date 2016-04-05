#pragma once
#include "IUIManager.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <vector>
#include "UIElement.h"
#include "Material.h"
#include "Unit.h"

namespace Hive
{
	class UIManager : public IUIManager
	{
	private:
		std::vector<UIElement> elements;
		UnitHandle player_unit_handle;
		Unit* player_unit;
		float temp_float = 100;
		UIElement temp_base_bar;
		UIElement temp_hp_bar;

		GLuint ui_shader_program_id;
		GLuint ui_shader_matrix_id;
		GLuint ui_vertex_array_id;

		glm::mat4 projection_matrix;

		float* verts;
		unsigned short* indices;
		GLuint VBO;
		GLuint IBO;

	public:
		UIManager();
		~UIManager();
		void load(GLuint shader, UnitHandle player_unit_handle);
		void update(float delta);
		void draw();
		//const glm::mat4& getProjectionMatrix();
	};
}

