#pragma once

#include <string>
#include <functional>

#include <tinyxml2/tinyxml2.h>

#include "IDataManager.h"
#include "DataCollection.h"
#include "XMLInterface.h"
#include "Material.h"

namespace Hive
{

	class DataManager : public IDataManager
	{
	private:
#pragma region XML Functions
		void xmlFirstPass(XMLInterface& xmlif);

		void xmlFirstPassAbilities(XMLIterator xmliter);
		void xmlFirstPassActors(XMLIterator xmliter);
		void xmlFirstPassBehaviors(XMLIterator xmliter);

		void xmlFirstPassEffect(XMLIterator xmliter);

		void xmlFirstPassTextures(XMLIterator xmliter);
		void xmlFirstPassMaterials(XMLIterator xmliter);
		void xmlFirstPassModels(XMLIterator xmliter);
		void xmlFirstPassUnits(XMLIterator xmliter);

		void xmlFirstPassValidator(XMLIterator xmliter);

		void xmlFirstPassParticleSystem(XMLIterator xmliter);
		void xmlFirstPassParticleEmitter(XMLIterator xmliter);
		void xmlFirstPassModuleSizeOverLife(XMLIterator xmliter);
		void xmlFirstPassModuleColorOverLife(XMLIterator xmliter);
		void xmlFirstPassModuleInitialRotation(XMLIterator xmliter);
		void xmlFirstPassModuleInitialRotationRate(XMLIterator xmliter);
		void xmlFirstPassModuleSubImageIndexOverLife(XMLIterator xmliter);
		void xmlFirstPassModuleSubImageIndexRandom(XMLIterator xmliter);

		void xmlSecondPass(XMLInterface& xmlif);

		void xmlSecondPassAbilities(XMLIterator xmliter);
		void xmlSecondPassActors(XMLIterator xmliter);
		void xmlSecondPassBehaviors(XMLIterator xmliter);

		void xmlSecondPassEffectModifyUnit(XMLIterator xmliter);
		void xmlSecondPassEffectSearch(XMLIterator xmliter);
		void xmlSecondPassEffectSet(XMLIterator xmliter);
		void xmlSecondPassEffectSetBehavior(XMLIterator xmliter);
		void xmlSecondPassEffectSpawnUnit(XMLIterator xmliter);
		void xmlSecondPassEffectSwitch(XMLIterator xmliter);

		void xmlSecondPassTextures(XMLIterator xmliter);
		void xmlSecondPassMaterials(XMLIterator xmliter);
		void xmlSecondPassModels(XMLIterator xmliter);
		void xmlSecondPassUnits(XMLIterator xmliter);

		void xmlSecondPassValidatorBehaviorCount(XMLIterator xmliter);
		void xmlSecondPassValidatorCombine(XMLIterator xmliter);
		void xmlSecondPassValidatorCompareVital(XMLIterator xmliter);
		void xmlSecondPassValidatorCondition(XMLIterator xmliter);
		void xmlSecondPassValidatorLocationRange(XMLIterator xmliter);
		void xmlSecondPassValidatorLocationPathable(XMLIterator xmliter);
		void xmlSecondPassValidatorFilterUnit(XMLIterator xmliter);
		void xmlSecondPassValidatorPlayer(XMLIterator xmliter);

		void xmlSecondPassParticleSystem(XMLIterator xmliter);
		void xmlSecondPassParticleEmitter(XMLIterator xmliter);
		void xmlSecondPassModuleSizeOverLife(XMLIterator xmliter);
		void xmlSecondPassModuleColorOverLife(XMLIterator xmliter);
		void xmlSecondPassModuleInitialRotation(XMLIterator xmliter);
		void xmlSecondPassModuleInitialRotationRate(XMLIterator xmliter);
		void xmlSecondPassModuleSubImageIndexOverLife(XMLIterator xmliter);
		void xmlSecondPassModuleSubImageIndexRandom(XMLIterator xmliter);

		void xmlParseVitals(XMLIterator iter, Vitals* vitals);
		void xmlParseCharges(XMLIterator iter, Charges* charges);
		void xmlParseCost(XMLIterator iter, Cost* cost);
		void xmlParseEffectList(XMLIterator iter, EffectList* effects);
		void xmlParseFilter(XMLIterator iter, Filter* filter);
		void xmlParseUnitFilter(XMLIterator iter, UnitFilter* filter);
		void xmlParseMeshList(XMLIterator iter, std::vector<int>* mesh_mat_handles);
		void xmlParseMesh(XMLIterator iter, std::vector<int>* mesh_mat_handles);

		template <class T>
		void linkData(XMLIterator iter, int* handle);

		template <class T>
		void copyParent(XMLIterator iter, T** t);

#pragma endregion

	public:
		DataManager();

		int loadCoreData();
		int loadXMLData(char* filename);

		~DataManager();
	};

	template <class T>
	void DataManager::linkData(XMLIterator iter, int* handle)
	{
		if (iter.isValid())
		{
			std::string id = iter.getValue();
			if (!id.empty())
			{
				if (T::hasKey(id))
				{
					*handle = T::getIndex(id);
				}
				else
				{
					throw DataErrorException("Could not link to id: " + id);
				}
			}
		}
	}

	template <class T>
	void DataManager::copyParent(XMLIterator iter, T** t)
	{
		std::string id = iter.getID();
		if (!T::hasKey(id)) throw DataErrorException("ID missing during second pass: " + id);

		*t = T::getItem(T::getIndex(id));

		std::string parentId = iter.getParentID();

		if (!parentId.empty())
		{
			if (T::hasKey(parentId))
			{
				int index = T::getIndex(parentId);
				**t = *(T::getItem(index));
			}
			else
			{
				throw DataErrorException("Model parent specified but not found: " + parentId);
			}
		}
	}
}