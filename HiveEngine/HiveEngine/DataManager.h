#pragma once

#include <string>
#include <functional>

#include <tinyxml2/tinyxml2.h>

#include "IDataManager.h"
#include "DataCollection.h"
#include "XMLInterface.h"

namespace Hive
{

	class DataManager : public IDataManager
	{
	private:
#pragma region XML Functions
		void xmlFirstPass(XMLInterface& xmlif);

		void xmlFirstPassAbilities(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassActors(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassBehaviors(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassEffect(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassTextures(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModels(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassUnits(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassValidator(XMLInterface::XMLIterator xmliter);

		void xmlFirstPassParticleSystem(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassParticleEmitter(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModuleSizeOverLife(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModuleColorOverLife(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModuleInitialRotation(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModuleInitialRotationRate(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModuleSubImageIndexOverLife(XMLInterface::XMLIterator xmliter);
		void xmlFirstPassModuleSubImageIndexRandom(XMLInterface::XMLIterator xmliter);

		void xmlSecondPass(XMLInterface& xmlif);

		void xmlSecondPassAbilities(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassActors(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassBehaviors(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassEffectModifyUnit(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSearch(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSet(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSetBehavior(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSpawnUnit(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassEffectSwitch(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassTextures(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModels(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassUnits(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassValidatorBehaviorCount(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorCombine(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorCompareVital(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorCondition(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorLocationRange(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorLocationPathable(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorFilterUnit(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassValidatorPlayer(XMLInterface::XMLIterator xmliter);

		void xmlSecondPassParticleSystem(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassParticleEmitter(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModuleSizeOverLife(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModuleColorOverLife(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModuleInitialRotation(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModuleInitialRotationRate(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModuleSubImageIndexOverLife(XMLInterface::XMLIterator xmliter);
		void xmlSecondPassModuleSubImageIndexRandom(XMLInterface::XMLIterator xmliter);

		void xmlParseVitals(XMLInterface::XMLIterator iter, Vitals* vitals);
		void xmlParseCharges(XMLInterface::XMLIterator iter, Charges* charges);
		void xmlParseCost(XMLInterface::XMLIterator iter, Cost* cost);
		void xmlParseEffectList(XMLInterface::XMLIterator iter, EffectList* effects);
		void xmlParseFilter(XMLInterface::XMLIterator iter, Filter* filter);
		void xmlParseUnitFilter(XMLInterface::XMLIterator iter, UnitFilter* filter);

		void xmlParseTexture(XMLInterface::XMLIterator iter, int* textureHandle);
		void xmlParseModel(XMLInterface::XMLIterator iter, int* modelHandle);
#pragma endregion

	public:
		DataManager();

		int loadCoreData();
		int loadXMLData(char* filename);

		~DataManager();
	};

}