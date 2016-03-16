#include "Actor.h"

using namespace Hive;

GLuint Actor::actor_shader_handle = -1;

Actor::Actor()
{
	position = glm::vec3(0);
	spin = glm::vec3(0);
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
}

void Actor::postdraw()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Actor::set_position(glm::vec2 pos, float height)
{
	position = glm::vec3(pos.x, height, pos.y);
}

void Actor::set_velocity(glm::vec2 plane)
{
	velocity.x = plane.x;
	velocity.z = plane.y;
}

void Actor::set_rotation(float rotation)
{
	Actor::rotation.y = rotation;
}

void Actor::set_spin(float spin)
{
	Actor::spin.y = spin;
}

void Actor::update_component(float delta)
{
	world_transform = glm::translate(glm::vec3(position));
	world_transform *= glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	world_transform *= glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	world_transform *= glm::rotate(rotation.z, glm::vec3(0, 0, 1));

	// Update state for next frame because if an update loop pushed data to the actor, that data is authoritative. 
	rotation += spin * delta;
	position += velocity * delta;
}

void Actor::draw_component(const glm::mat4& VP)
{
	DModel* data = DModel::getItem(d_model_handle);
	const Model* model = data->getAsset();

	glm::mat4 WVP = VP * world_transform;

	GLuint shader_matrix_id = glGetUniformLocation(actor_shader_handle, "WVP");
	GLuint shader_world_id = glGetUniformLocation(actor_shader_handle, "W");

	glUniformMatrix4fv(shader_matrix_id, 1, GL_FALSE, &WVP[0][0]);
	glUniformMatrix4fv(shader_world_id, 1, GL_FALSE, &world_transform[0][0]);

	model->draw(actor_shader_handle);
}

Actor::~Actor()
{
}