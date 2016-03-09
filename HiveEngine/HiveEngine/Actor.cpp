#include "Actor.h"

using namespace Hive;

GLuint Actor::actor_shader_handle = -1;

Actor::Actor()
{
	position = glm::vec2(0);
	world_transform = glm::mat4();
	d_model_handle = -1;
}

void Actor::loadFromData(int handle)
{
	DActor* data = DActor::getItem(handle);
	d_model_handle = data->dModelHandle;
}

void Actor::setShader(GLuint shader)
{
	actor_shader_handle = shader;
}

void Actor::predraw()
{
	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Normal
	glEnableVertexAttribArray(2); //UV
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
		);
	glVertexAttribPointer(
		1,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)(3 * sizeof(float))            // array buffer offset
		);
	glVertexAttribPointer(
		2,                  // attribute
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		8 * sizeof(float),                  // stride
		(void*)(6 * sizeof(float))            // array buffer offset
		);
}

void Actor::postdraw()
{
	glDisableVertexAttribArray(0); //Position
	glDisableVertexAttribArray(1); //Normal
	glDisableVertexAttribArray(2); //UV
}

void Actor::update_component(float delta, bool is_a)
{
	world_transform = glm::translate(glm::mat4(), glm::vec3(position, 0));
}

void Actor::draw_component(const glm::mat4& VP)
{
	DModel* data = DModel::getItem(d_model_handle);
	const Model* model = data->getAsset();

	model->draw(world_transform, VP, actor_shader_handle);
}

Actor::~Actor()
{
}