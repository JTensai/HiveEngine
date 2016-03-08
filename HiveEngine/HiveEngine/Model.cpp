#include "Model.h"

namespace Hive
{

	Model::Model()
	{
	}

	void Model::draw(const glm::mat4& WVP)
	{
		IDataManager* dm = ServiceLocator::getInstance()->getDataManager();
		for (int i = 0; i < _meshHandles.size(); ++i)
		{
			//draw
		}
	}

	Model::~Model()
	{
	}

}