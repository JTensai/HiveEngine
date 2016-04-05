#pragma once

#include <vector>
#include <algorithm>

#include <glm\glm.hpp>

#include "IGraphics.h"
#include "Mesh.h"

namespace Hive
{
	class Graphics : public IGraphics
	{
	private:
		GLuint shader;

		struct NormalDrawCall
		{
			MeshHandle mesh;
			DMaterialHandle material;
			glm::mat4 transform;
		};
		struct AlphaDrawCall
		{
			float depth;
			MeshHandle mesh;
			DMaterialHandle material;
			glm::mat4 transform;
		};

		std::vector<NormalDrawCall> normal_draws;
		std::vector<AlphaDrawCall> alpha_draws;

		glm::mat4 view_projection_matrix;

	public:
		Graphics(int shader) : shader(shader)
		{
			normal_draws = std::vector<NormalDrawCall>();
			alpha_draws = std::vector<AlphaDrawCall>();
		}

		void update_view_projection_matrix(glm::mat4 view_projection_matrix);
		void queue_draw(DrawShader shader, glm::mat4 transform, MeshHandle mesh, DMaterialHandle material);
		void draw_all();

		~Graphics();
	};
}