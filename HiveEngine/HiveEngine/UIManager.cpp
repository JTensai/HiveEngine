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
		verts = new float [20]
		{
			0,0,0,1,1,
			1,0,0,1,0,
			1,1,0,0,0,
			0,1,0,0,1,
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
		glBufferData(GL_ARRAY_BUFFER, 4 * 5 * sizeof(float), verts, GL_STATIC_DRAW);

		// sends the indices array to the praphics card to it knows how to draw them
		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned short), indices, GL_STATIC_DRAW);


		// temp test stuff
		// UIElement(bottom_left(vec2), width (0-1), height (0-1))

		/* Screen layout
		   1|
			|
			|
		Y	|
			|
			|
		   0|________________
			 0		X		1		
		*/
		//DTexture* data = new DTexture();
		//Texture texture = Texture("resources/texture.jpg", data);
		
		UIElement action_bar = UIElement(glm::vec2(.25, 0), 0.5f, 0.1f , DTexture::getIndex("HEART"));
		elements.push_back(action_bar);


		/*UIElement center_test = UIElement(glm::vec2(.4625, .45), .075, .1, Texture("resources/texture.jpg", data));
		elements.push_back(center_test);*/




	/*	UIElement rotate_test = UIElement(glm::vec2(.45, .45), .1, .1);
		rotate_test.rotation = 90;
		elements.push_back(rotate_test);

		UIElement rotate_test2 = UIElement(glm::vec2(.0, .0), .2, .2);
		rotate_test.rotation = 90;
		elements.push_back(rotate_test2);

		UIElement rotate_test3 = UIElement(glm::vec2(.7, .7), .1, .1);
		rotate_test.rotation = 90;
		elements.push_back(rotate_test3);*/



		//elements.push_back(UIElement(glm::vec2(50, 50), 30.0f, 10.0f, 0));
	}

	void UIManager::update(float delta) {
		//elements[1].rotation += 1 * delta;
		//elements[2].rotation += 1 * delta;
		//elements[3].rotation += 1 * delta;
	}

	void UIManager::draw()
	{
		// tells the graphics card which shader it should currently be using
		glUseProgram(ui_shader_program_id);


		// in the currently assigned shader on the graphics card, set its "0" variable
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			5 * sizeof(float),  // stride
			(void*)0            // array buffer offset
			);
		glVertexAttribPointer(
			1,								// attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,								// size
			GL_FLOAT,						// type
			GL_FALSE,						// normalized?
			5 * sizeof(float),				// stride
			(void*)(3 * sizeof(float))      // array buffer offset
			);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

		for(UIElement element : elements)
		{
			glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f);

			// Rotation is not working correctly. If the object is centered on screen this works. if not, then it starts rotating strangely
			glm::mat4 untrans_for_rot = glm::translate(glm::mat4(), glm::vec3(-element.bottom_left.x - (element.width / 2), -element.bottom_left.y - (element.height) / 2, 0));
			glm::mat4 rotate = glm::rotate(glm::mat4(), element.rotation, glm::vec3(0, 0, 1));
			glm::mat4 retrans_after_rot = glm::translate(glm::mat4(), glm::vec3(element.bottom_left.x + (element.width / 2), element.bottom_left.y + (element.height) / 2, 0));

			glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(element.width, element.height, 1.0f));
			glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3(element.bottom_left.x, element.bottom_left.y, 0.0f));

			glm::mat4 combined = projection * translate * scale * retrans_after_rot * rotate * untrans_for_rot;

			// tell the graphics card about the current matrix being used
			glUniformMatrix4fv(ui_shader_matrix_id, 1, GL_FALSE, &combined[0][0]);

			const Texture* tex = (DTexture::getItem(element.texture_handle))->getAsset();
			glBindTexture(GL_TEXTURE_2D, tex->get_handle());




			//for (NormalDrawCall draw_call : normal_draws)
			//{
			/*	int material_handle = -1;
				const DMaterial* material = nullptr;

					material_handle = 0;
					material = DMaterial::getItem(material_handle);
					material->bind();*/
				
			//}



			// draw the element
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)0);
		}

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
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