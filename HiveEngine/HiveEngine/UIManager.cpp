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

	void UIManager::update(float delta) {

	}

	void UIManager::draw() {
		// std::cout << "Drawing UI" << std::endl;
		// set up camera just for ui
		// billboard mesh, 
		// a shader that grabs a texture and puts it on screen
		// look at temp model for rendering
		// will need a different shader (texture2d sampler into shader)
		
		// tell opengl to use my shader
		// opengl.use...(in temp model)
		// 
		// foreach ui element
			// make translation matrix
			// make scale matrix
			// put that matrix into the shader
			// bind the correct texture
			// Billboard.Draw()
		// end 
	}
}