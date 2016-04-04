#include "Graphics.h"

using namespace Hive;

void Graphics::update_view_projection_matrix(glm::mat4 view_projection_matrix)
{
	Graphics::view_projection_matrix = view_projection_matrix;
}

void Graphics::queue_draw(DrawShader shader, glm::mat4 transform, MeshHandle mesh, DMaterialHandle material)
{
	switch (shader)
	{
	case DrawShader::NORMAL:
		normal_draws.push_back(NormalDrawCall{ mesh, material, transform });
		break;
	case DrawShader::ALPHA:
		glm::vec4 clip_position = view_projection_matrix * transform * glm::vec4(0, 0, 0, 1);
		alpha_draws.push_back(AlphaDrawCall{ clip_position.z, mesh, material, transform });
		break;
	}
}

void Graphics::draw_all()
{	
	std::sort(
		normal_draws.begin(),
		normal_draws.end(),
		[](NormalDrawCall a, NormalDrawCall b)
		{
			return (a.mesh != b.mesh) ? a.mesh < b.mesh : a.material < b.material;
		}
	);
	std::sort(
		alpha_draws.begin(),
		alpha_draws.end(),
		[](AlphaDrawCall a, AlphaDrawCall b)
		{
			return (a.depth == b.depth) ?
				(a.mesh != b.mesh) ? a.mesh < b.mesh : a.material < b.material :
				a.depth < b.depth;
		}
	);

	GLuint shader_matrix_id = glGetUniformLocation(shader, "WVP");
	GLuint shader_world_id = glGetUniformLocation(shader, "W");

	glEnableVertexAttribArray(0); //Position
	glEnableVertexAttribArray(1); //Normal
	glEnableVertexAttribArray(2); //UV

	glm::mat4 wvp;

	int mesh_handle = -1;
	Mesh* mesh = nullptr;
	int material_handle = -1;
	const DMaterial* material = nullptr;

	for (NormalDrawCall draw_call : normal_draws)
	{
		if (draw_call.mesh != mesh_handle)
		{
			mesh_handle = draw_call.mesh;
			mesh = Mesh::get_mesh(mesh_handle);
			mesh->bind();
			Mesh::set_vertex_attributes();
		}

		if (draw_call.material != material_handle)
		{
			material_handle = draw_call.material;
			material = DMaterial::getItem(material_handle);
			material->bind();
		}

		wvp = view_projection_matrix * draw_call.transform;
		glUniformMatrix4fv(shader_matrix_id, 1, GL_FALSE, &wvp[0][0]);
		glUniformMatrix4fv(shader_world_id, 1, GL_FALSE, &draw_call.transform[0][0]);
		mesh->draw();
	}
	normal_draws.clear();

	for (AlphaDrawCall draw_call : alpha_draws)
	{
		if (draw_call.mesh != mesh_handle)
		{
			mesh_handle = draw_call.mesh;
			mesh = Mesh::get_mesh(mesh_handle);
			mesh->bind();
			Mesh::set_vertex_attributes();
		}

		if (draw_call.material != material_handle)
		{
			material_handle = draw_call.material;
			material = DMaterial::getItem(material_handle);
			material->bind();
		}

		wvp = view_projection_matrix * draw_call.transform;
		glUniformMatrix4fv(shader_matrix_id, 1, GL_FALSE, &wvp[0][0]);
		glUniformMatrix4fv(shader_world_id, 1, GL_FALSE, &draw_call.transform[0][0]);
		mesh->draw();
	}
	alpha_draws.clear();

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

Graphics::~Graphics()
{
}
