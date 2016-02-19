#pragma once
#include "IUIManager.h"

namespace Hive
{
	class UIManager : public IUIManager
	{
	public:
		UIManager();
		~UIManager();
		void update(float delta);
		void draw();
	};
}

