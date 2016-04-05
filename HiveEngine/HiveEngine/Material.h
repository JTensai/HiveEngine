#pragma once

#include <GL\glew.h>

#include "DataCollection.h"
#include "Data.h"
#include "Texture.h"

namespace Hive
{
	class DMaterial : public DataCollection<DMaterial>
	{
	public:
		DTextureHandle diffuse_tex;

		DMaterial();
		void bind() const;
		~DMaterial();
	};
}