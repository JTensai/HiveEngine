#pragma once

#include <GL\glew.h>

#include "Texture.h"
#include "DataCollection.h"

namespace Hive
{
	class Material : public DataCollection<Material>
	{
	public:
		int diffuse_tex;

		Material();
		void bind();
		~Material();
	};
}