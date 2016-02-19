#pragma once

namespace Hive 
{
	class IUIManager
	{
	public:
		virtual void update(float delta) = 0;
		virtual void draw() = 0;
	};
}


