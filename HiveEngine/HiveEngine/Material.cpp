#include "Material.h"

using namespace Hive;

Material::Material()
{
}

void Material::bind()
{
	const Texture* tex = (DTexture::getItem(diffuse_tex))->getAsset();
	glBindTexture(GL_TEXTURE_2D, tex->get_handle());
}

Material::~Material()
{
}
