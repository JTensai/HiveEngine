#include "Material.h"

using namespace Hive;

DMaterial::DMaterial()
{
}

void DMaterial::bind() const
{
	const Texture* tex = (DTexture::getItem(diffuse_tex))->getAsset();
	glBindTexture(GL_TEXTURE_2D, tex->get_handle());
}

DMaterial::~DMaterial()
{
}
