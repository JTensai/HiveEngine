#include "model.h"

Model::Model() {}

Model::Model(const char* objFilename) {
	_iNumVerts = 0;
	_iNumIndices = 0;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(shapes, materials, err, objFilename);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	if (!ret) {
		return;
	}

	for (int i = 0; i < shapes.size(); i++) {
		_iNumVerts += shapes[i].mesh.positions.size() / 3;
		_iNumIndices += shapes[i].mesh.indices.size();
	}
	_fVertData = new float[_iNumVerts * 3];
	_fNormalData = new float[_iNumVerts * 3];
	_iIndexData = new unsigned short[_iNumIndices];
	int vertOffset = 0;
	int indOffset = 0;
	for (int i = 0; i < shapes.size(); i++) {
		for (int j = 0; j < shapes[i].mesh.positions.size(); j++) {
			_fVertData[j + vertOffset] = shapes[i].mesh.positions[j];
			_fNormalData[j + vertOffset] = shapes[i].mesh.normals[j];
		}
		for (int j = 0; j < shapes[i].mesh.indices.size(); j++) {
			_iIndexData[j + indOffset] = shapes[i].mesh.indices[j] + vertOffset;
		}
		vertOffset += shapes[i].mesh.positions.size();
		indOffset += shapes[i].mesh.indices.size();
	}

	glGenBuffers(1, &_iVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _iVBO);
	glBufferData(GL_ARRAY_BUFFER, _iNumVerts * 3 * sizeof(float), _fVertData, GL_STATIC_DRAW);

	glGenBuffers(1, &_iNBO);
	glBindBuffer(GL_ARRAY_BUFFER, _iNBO);
	glBufferData(GL_ARRAY_BUFFER, _iNumVerts * 3 * sizeof(float), _fNormalData, GL_STATIC_DRAW);

	glGenBuffers(1, &_iIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _iNumIndices * sizeof(unsigned short), _iIndexData, GL_STATIC_DRAW);
}

Model::~Model() {
	if (_iVBO) {
		//Release vertex buffer
		glDeleteBuffers(1, &_iVBO);
	}
	if (_iNBO) {
		//Release normal buffer
		glDeleteBuffers(1, &_iNBO);
	}
	if (_iIBO) {
		//Release index buffer
		glDeleteBuffers(1, &_iIBO);
	}
	if (_fVertData) {
		delete[] _fVertData;
	}
	if (_fNormalData) {
		delete[] _fNormalData;
	}
	if (_iIndexData) {
		delete[] _iIndexData;
	}
}

void Model::draw() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _iVBO);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _iNBO);
	glVertexAttribPointer(
		1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _iIBO);

	glDrawElements(GL_TRIANGLES, _iNumIndices, GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
