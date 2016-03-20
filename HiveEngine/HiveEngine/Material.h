#pragma once

#include <GL\glew.h>

#include "Texture.h"
#include "DataCollection.h"

namespace Hive
{
	class DMaterial : public DataCollection<DMaterial>
	{
	public:
		int diffuse_tex;

		DMaterial();
		void bind() const;
		~DMaterial();
	};
}