#include "UIManager.h"
#include <iostream>

namespace Hive
{
	UIManager::UIManager()
	{
	}


	UIManager::~UIManager()
	{
	}

	void UIManager::load(GLuint shader)
	{
		ui_shader_program_id = shader;
		ui_shader_matrix_id = glGetUniformLocation(ui_shader_program_id, "MVP");
		projection_matrix = glm::ortho(0,1,1,0);

		// sets up the verticies of our custom square mesh with 4 corners
		verts = new float [12]
		{
			0,0,0,
			1,0,0,
			1,1,0,
			0,1,0
		};
		// All polygons in a mesh need to be tris, this is where we define the tris of our square mesh. These are the indices of the verts in the above array
		indices = new unsigned short [6]
		{
			0,1,3,
			1,2,3
		};

		// sends the verts array to the graphics card so it knows how to draw them
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), verts, GL_STATIC_DRAW);

		// sends the indices array to the praphics card to it knows how to draw them
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);


		// temp test stuff
		elements.push_back(UIElement(glm::vec2(0.5, 0.5), 0.5f, 0.5f, 0));
		//elements.push_back(UIElement(glm::vec2(50, 50), 30.0f, 10.0f, 0));
	}

	void UIManager::update(float delta) {

	}

	void UIManager::draw()
	{
		// tells the graphics card which shader it should currently be using
		glUseProgram(ui_shader_program_id);


		// in the currently assigned shader on the graphics card, set its "0" variable
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);


		glm::mat4 element_matrix;
		for(UIElement element : elements)
		{
			// set up the scale and translate matrix for the element to be drawn
			glm::scale(element_matrix, glm::vec3(element.width, element.height, 0));
			glm::translate(element_matrix, glm::vec3(element.top_left.x, -element.top_left.y, 0));

			// tell the graphics card about the current matrix being used
			glUniformMatrix4fv(ui_shader_matrix_id, 1, GL_FALSE, &element_matrix[0][0]);

			// draw the element
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
			//element.draw();
		}

		glDisableVertexAttribArray(0);
		// foreach ui element
			// make translation matrix
			// make scale matrix
			// put that matrix into the shader
			// bind the correct texture
			// Billboard.Draw()
		// end 
	}

	//const glm::mat4& getProjectionMatrix() 
	//{
	//	return projection_matrix;
	//}
}