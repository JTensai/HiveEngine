#pragma once

#include "Model.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class IAssetManager {
public:
	virtual int getShaderHandle(const char* vertexShader, const char* fragmentShader) { return -1; }
	virtual Shader* getShader(int handle) { return 0; }

	virtual int getModelHandle(const char* filename) { return -1; }
	virtual Model* getModel(int handle) { return 0; }

	virtual Mesh* getMesh(int handle) { return 0; }

	virtual int getTextureHandle(const char* filename) { return -1; }
	virtual Texture* getTexture(int handle) { return 0; }
};