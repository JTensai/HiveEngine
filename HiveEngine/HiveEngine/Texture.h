#pragma once

#include <string>
#include <stdexcept>
#include <vector>

#include <GL\glew.h>
#include <IL\il.h>

#include "Asset.h"

namespace Hive
{
	class Texture
	{
	private:
		int width;
		int height;
		std::vector<unsigned char> tex_data;
		GLuint gl_handle;

	public:
		Texture(std::string filepath);
		GLuint get_handle() const;
		~Texture();
	};

}