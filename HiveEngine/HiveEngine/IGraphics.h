#pragma once

namespace Hive
{
	enum class DrawShader
	{
		NORMAL,
		ALPHA
	};

	class IGraphics
	{
	public:
		virtual void update_view_projection_matrix(glm::mat4 view_projection_matrix) = 0;
		virtual void queue_draw(DrawShader shader, glm::mat4 transform, int mesh, int material) = 0;
		virtual void draw_all() = 0;

		virtual ~IGraphics() {}
	};
}