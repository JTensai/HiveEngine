#include "Actor.h"

using namespace Hive;

GLuint Actor::actor_shader_handle = -1;

Actor::Actor()
{
	scale = glm::vec3(1);
	rotation = glm::vec3(0);
	position = glm::vec3(0);
	spin = glm::vec3(0);
	world_transform = glm::mat4();
	d_model_handle = -1;
	d_material_handle = -1;
}

void Actor::loadFromData(DActorHandle handle)
{
	DActor* data = DActor::getItem(handle);
	d_model_handle = data->dModelHandle;
	d_material_handle = data->dMaterialHandle;
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

void Actor::set_scale(glm::vec3 scale)
{
	Actor::scale = scale;
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
void Actor::set_rotation(glm::vec3 rotation)
{
	Actor::rotation = rotation;
}

void Actor::set_spin(float spin)
{
	Actor::spin.y = spin;
}
void Actor::set_spin(glm::vec3 spin)
{
	Actor::spin = spin;
}

void Actor::update_component(float delta)
{
	world_transform = glm::translate(glm::vec3(position));
	world_transform *= glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	world_transform *= glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	world_transform *= glm::rotate(rotation.z, glm::vec3(0, 0, 1));
	world_transform *= glm::scale(scale);

	// Update state for next frame because if an update loop pushed data to the actor, that data is authoritative. 
	rotation += spin * delta;
	position += velocity * delta;
}

void Actor::draw_component(const glm::mat4& VP)
{
	DModel* data = DModel::getItem(d_model_handle);
	const Model* model = data->getAsset();

	int meshes = model->get_num_meshes();
	for (int i = 0; i < meshes; i++)
	{
		ServiceLocator::get_graphics()->queue_draw(DrawShader::NORMAL, world_transform, model->get_mesh(i), d_material_handle);
	}
}

Actor::~Actor()
{
}