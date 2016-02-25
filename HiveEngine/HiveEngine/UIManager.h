#pragma once
#include "IUIManager.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <vector>
#include "UIElement.h"

namespace Hive
{
	class UIManager : public IUIManager
	{
	private:
		std::vector<UIElement> elements;

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
		void load(GLuint shader);
		void update(float delta);
		void draw();
		//const glm::mat4& getProjectionMatrix();
	};
}

