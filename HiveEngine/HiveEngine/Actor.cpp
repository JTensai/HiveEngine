#include "Actor.h"

using namespace Hive;

GLuint Actor::actor_shader_handle = -1;

Actor::Actor()
{
	position = glm::vec3(20, 3, 30);
	spin = glm::vec3(0, 1, 0);
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
}

void Actor::postdraw()
{
}

void Actor::update_component(float delta, bool is_a)
{
	world_transform = glm::translate(glm::vec3(position));
	rotation += spin * delta;
	world_transform *= glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	world_transform *= glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	world_transform *= glm::rotate(rotation.z, glm::vec3(0, 0, 1));
}

void Actor::draw_component(const glm::mat4& VP)
{
	DModel* data = DModel::getItem(d_model_handle);
	const Model* model = data->getAsset();

	glm::mat4 WVP = VP * world_transform;

	GLuint shader_matrix_id = glGetUniformLocation(actor_shader_handle, "MVP");
	GLuint shader_world_id = glGetUniformLocation(actor_shader_handle, "M");

	glUniformMatrix4fv(shader_matrix_id, 1, GL_FALSE, &WVP[0][0]);
	glUniformMatrix4fv(shader_world_id, 1, GL_FALSE, &world_transform[0][0]);

	model->draw(actor_shader_handle);
}

Actor::~Actor()
{
}