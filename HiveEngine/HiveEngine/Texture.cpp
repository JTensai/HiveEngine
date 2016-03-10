#include "Texture.h"

using namespace Hive;

Texture::Texture(std::string filepath, DTexture* data)
{
	ILuint handle;
	ilGenImages(1, &handle);
	ilBindImage(handle);

	//std::wstring wFilepath = std::wstring(filepath.begin(), filepath.end());
	if (!ilLoadImage((const wchar_t*)filepath.c_str()))
	{
		throw AssetLoadException("Unable to load image: " + filepath + "; Err: " + std::to_string(ilGetError()));
	}

	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);

	tex_data = std::vector<unsigned char>(width * height * 4);

	ilCopyPixels(
		0,					// X Offset
		0,					// Y Offset
		0,					// Z Offset
		width,				// Width
		height,				// Height
		1,					// Depth
		IL_RGBA,			// Format
		IL_UNSIGNED_BYTE,	// Type
		tex_data.data()			// Data
		);

	ilDeleteImages(1, &handle);

	glGenTextures(1, &gl_handle);
	glBindTexture(GL_TEXTURE_2D, gl_handle);
	glTexImage2D(
		GL_TEXTURE_2D,		// Target
		0,					// LOD
		GL_RGBA,			// Internal Format (e.g. does it even have alpha?)
		width,				// Width
		height,				// Height
		0,					// Border, always 0
		GL_RGBA,			// Format (i.e. what is the ordering of the components)
		GL_UNSIGNED_BYTE,	// Type
		tex_data.data()			// Data
		);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

GLuint Texture::get_handle() const
{
	return gl_handle;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, gl_handle);
	glTexImage2D(
		GL_TEXTURE_2D,		// Target
		0,					// LOD
		GL_RGBA,			// Internal Format (e.g. does it even have alpha?)
		width,				// Width
		height,				// Height
		0,					// Border, always 0
		GL_RGBA,			// Format (i.e. what is the ordering of the components)
		GL_UNSIGNED_BYTE,	// Type
		tex_data.data()			// Data
		);
}

Texture::~Texture()
{
	glDeleteTextures(1, &gl_handle);
}